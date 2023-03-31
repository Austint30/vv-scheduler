#pragma once

#include <functional>
#include <vector>
#include <queue>
#include "../task.hpp"

#define TASK_PRIORITY_QUEUE std::priority_queue<Task*, std::vector<Task*>, TaskComparator>

struct SchedInfo {
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
    SchedInfo m_info;
    bool m_hasStarted = false;

    // This value is set when a context switch occurs
    int ctxSwitchTime = 0;

    void Init(SchedInfo info){
        m_info = info;
    }

    void PutArrivedTask(Task* task){
        if (!m_hasStarted){ m_hasStarted = true; }
        m_activeTasks.push(task);
    };

    void DispatchRejectTaskEvent(Task* task, float utilization){
        m_info.onTaskRejected(task, utilization);
    }

    void DispatchAcceptTaskEvent(Task* task, float utilization){
        m_info.onTaskAccepted(task, utilization);
    }

    void DispatchCompleteTaskEvent(Task* task){
        m_info.onTaskCompleted(task);
    }

    void DispatchProcessTaskEvent(Task* task){
        m_info.onTaskProcessing(task);
    }

    void DispatchContextSwitch(Task* oldTask, Task* newTask){
        int ctxTime = 0;
        if (oldTask != nullptr)
            ctxTime += oldTask->getInfo().ctxswitch;
        if (newTask != nullptr)
            ctxTime += newTask->getInfo().ctxswitch;
            
        m_info.onContextSwitch(oldTask, newTask, ctxTime);
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
