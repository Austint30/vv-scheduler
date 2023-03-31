#pragma once
#include <queue>
#include <vector>
#include "scheduler.hpp"

// STS algorithm scheduler without voltage consideration

class STSScheduler: public BaseScheduler
{

private:

    Task* m_lastTask;

    std::vector<float> m_descreteVoltages;
    float m_currentVoltage = 1.0;

    std::queue<Task*> m_acceptedTasks;

    float CalcVoltage(float utilization);

    float CalcUj(int j, int time, TASK_PRIORITY_QUEUE activeTasksCopy);
    float CalcMaxU(int time, TASK_PRIORITY_QUEUE& activeTasks);

public:
    void HandleArrivedTask(Task* task, int time);
    void Tick(int time);

    void SetDescreteVoltages(std::vector<float> voltages){ m_descreteVoltages = voltages; };
};
