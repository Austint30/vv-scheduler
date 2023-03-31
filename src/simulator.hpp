#pragma once

#include <queue>
#include <iostream>
#include <unistd.h>
#include "task.hpp"
#include "scheduler/scheduler.hpp"
#include "scheduler/sts.hpp"
#include "scheduler/output.hpp"

class Simulator
{
private:
    int m_time = 0;
    int m_cycleDelay = 1; // seconds
    std::queue<Task*> m_taskQueue;
    std::vector<float> m_descVoltages;

    int m_ctxSwitchTime = 0;

    BaseScheduler* m_schedImpl = new STSScheduler();

    ScheduleOutput* m_output = new ScheduleOutput();

    void HandleTaskProcessEvent(Task* task);
    void HandleTaskCompleteEvent(Task* task);
    void HandleTaskRejectEvent(Task* task, float utilization);
    void HandleTaskAcceptEvent(Task* task, float utilization);
    void HandleContextSwitchEvent(Task* oldTask, Task* newTask, int switchTime);
    void HandleVoltageUpdateEvent(float voltage);

    std::string SchedPQToStr();
    std::string GetTimeStr(){ return "[ T=" + std::to_string(m_time) + " ]"; };

    void CheckDeadlines();

public:
    Simulator(std::queue<Task*>& taskQueue);

    void UseSchedImpl(BaseScheduler* schedImpl){ m_schedImpl = schedImpl; }

    ~Simulator(){};

    void SetCycleDelay(int delay){ m_cycleDelay = delay; };

    void RunLoop();

    void PrintSchedule();
};