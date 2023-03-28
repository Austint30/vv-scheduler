#pragma once

#include "scheduler.hpp"

// STS algorithm scheduler without voltage consideration

class STSScheduler: public BaseScheduler
{

private:

    float CalcUj(int j, int time, std::priority_queue<Task*> activeTasksCopy);
    float CalcMaxU(int time, std::priority_queue<Task*>& activeTasks);

public:
    void HandleArrivedTask(Task* task, int time);
    void Tick(int time);
};
