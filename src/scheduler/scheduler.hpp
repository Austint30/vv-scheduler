#pragma once

#include "vector"
#include "queue"
#include "../task.hpp"

#define TASK_PRIORITY_QUEUE std::priority_queue<Task*, std::vector<Task*>, TaskComparator>

struct SchedEventInfo {
    std::function<void(Task*, float)> onTaskRejected;
    std::function<void(Task*)> onTaskCompleted;
    std::function<void(Task*, float)> onTaskAccepted;
    std::function<void(Task*)> onTaskProcessing;
    std::function<void(Task*, Task*, int)> onContextSwitch;
};

class TaskComparator
{
    public:
    bool operator()(Task* below, Task* above)
    {
        return below->getInfo().deadline > above->getInfo().deadline;
    }
};

class BaseScheduler
{
    friend class Simulator;

protected:
    TASK_PRIORITY_QUEUE m_activeTasks;
    Task* processingTask;
    SchedEventInfo m_eventInfo;
    bool m_hasStarted = false;

    // This value is set when a context switch occurrs
    int ctxSwitchTime = 0;

    void PushTask(Task* task){
        auto lastTask = m_activeTasks.size() > 0 ? m_activeTasks.top() : nullptr;
        m_activeTasks.push(task);

        if (lastTask != nullptr && m_activeTasks.top() != lastTask){
            // Context switch detected!
            DispatchContextSwitch(lastTask, m_activeTasks.top());
        }
        
    }

    void PopTask(){
        if (m_activeTasks.size() == 0) return;

        auto lastTask = m_activeTasks.top();
        m_activeTasks.pop();

        if (m_activeTasks.size() > 0){
            // Context switch always happens when a pop occurs since it
            // always pops from the highest priority.
            DispatchContextSwitch(lastTask, m_activeTasks.top());
        }
    }

    void Init(SchedEventInfo eventInfo){
        m_eventInfo = eventInfo;
    }

    void PutArrivedTask(Task* task){
        if (!m_hasStarted){ m_hasStarted = true; }
        PushTask(task);
    };

    void DispatchRejectTaskEvent(Task* task, float utilization){
        m_eventInfo.onTaskRejected(task, utilization);
    }

    void DispatchAcceptTaskEvent(Task* task, float utilization){
        m_eventInfo.onTaskAccepted(task, utilization);
    }

    void DispatchCompleteTaskEvent(Task* task){
        m_eventInfo.onTaskCompleted(task);
    }

    void DispatchProcessTaskEvent(Task* task){
        m_eventInfo.onTaskProcessing(task);
    }

    void DispatchContextSwitch(Task* oldTask, Task* newTask){
        m_eventInfo.onContextSwitch(
            oldTask, newTask, 
            oldTask->getInfo().ctxswitch + 
            newTask->getInfo().ctxswitch
        );
    }
    
public:
    ~BaseScheduler(){};

    virtual void Tick(int time) = 0;
    virtual void HandleArrivedTask(Task* task, int time) = 0;


    // Flag if tasks are currently active and processing.
    bool IsProcessing(){ return m_activeTasks.size() > 0 && m_hasStarted; }

    std::vector<Task*> GetTaskQueue(){
        auto pqCopy = m_activeTasks;
        std::vector<Task*> queue;
        while (pqCopy.size() > 0){
            queue.push_back(pqCopy.top());
            pqCopy.pop();
        }

        return queue;
    };
};
