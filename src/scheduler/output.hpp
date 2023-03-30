#pragma once

#include <map>
#include <set>
#include <cmath>
#include "../task.hpp"

struct TaskImage {
    int taskNum;
    int remainCompute;
};

class ScheduleOutput
{
private:
    int m_maxTime = 0;
    std::map<int, TaskImage> m_taskTimes;
    std::map<int, float> m_voltageTimes;
    std::set<int> m_csTimes;

    void RecordTime(int time){
        m_maxTime = std::max(m_maxTime, time);
    }
public:

    void RecordTask(int time, Task* task, float voltage=1.0);
    void RecordCtxSwitch(int time, float voltage=1.0);

    void PrintTable();
};
