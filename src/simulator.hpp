#pragma once

#include <queue>
#include <iostream>
#include "task.hpp"
#include "scheduler/scheduler.hpp"
#include "scheduler/sts.hpp"
#include <unistd.h>

class Simulator
{
private:
    int m_time = 0;
    int m_cycleDelay = 1; // seconds
    std::queue<Task*> m_taskQueue;
    std::vector<Task*> m_completedTasks;
    std::vector<Task*> m_rejectedTasks;

    BaseScheduler* m_schedImpl = new STSScheduler();

    void HandleTaskCompleteEvent(Task* task);
    void HandleTaskRejectEvent(Task* task, float utilization);
    void HandleTaskAcceptEvent(Task* task, float utilization);

public:
    Simulator(std::queue<Task*>& taskQueue);

    void UseSchedImpl(BaseScheduler* schedImpl){ m_schedImpl = schedImpl; }

    ~Simulator(){
        delete m_schedImpl;
    };

    void SetCycleDelay(int delay){ m_cycleDelay = delay; };

    void RunLoop();
};