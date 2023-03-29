#pragma once

#include <queue>
#include "../task.hpp"

class ScheduleOutput
{
private:
    std::queue<Task*> m_scheduledTasks;
public:

    void AppendTask(Task* task);
    void AppendCtxSwitch();

    void PrintTable();
};
