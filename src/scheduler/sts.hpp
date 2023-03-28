#pragma once

#include "scheduler.hpp"

// STS algorithm scheduler without voltage consideration

class STSScheduler: public BaseScheduler
{

private:

    float CalcUj(int j, int time, TASK_PRIORITY_QUEUE activeTasksCopy);
    float CalcMaxU(int time, TASK_PRIORITY_QUEUE& activeTasks);

public:
    void HandleArrivedTask(Task* task, int time);
    void Tick(int time);
};
