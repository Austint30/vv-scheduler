#pragma once

#include "vector"
#include "queue"
#include "../task.hpp"

struct SchedEventInfo {
    std::function<void(Task*, float)> onTaskRejected;
    std::function<void(Task*)> onTaskCompleted;
    std::function<void(Task*, float)> onTaskAccepted;
};

class BaseScheduler
{
    friend class Simulator;
protected:
    std::priority_queue<Task*> m_activeTasks;
    Task* processingTask;
    SchedEventInfo m_eventInfo;
    bool m_hasStarted = false;

    void Init(SchedEventInfo eventInfo){
        m_eventInfo = eventInfo;
    }

    void PutArrivedTask(Task* task){
        if (!m_hasStarted){ m_hasStarted = true; }
        m_activeTasks.push(task);
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
    
public:
    ~BaseScheduler(){};

    virtual void Tick(int time) = 0;
    virtual void HandleArrivedTask(Task* task, int time) = 0;


    // Flag if tasks are currently active and processing.
    bool IsProcessing(){ return m_activeTasks.size() > 0 && m_hasStarted; }
};
