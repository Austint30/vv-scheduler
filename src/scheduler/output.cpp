#include <iostream>
#include "output.hpp"
#include "../vendor/variatic_table.hpp"

void ScheduleOutput::RecordTask(int time, Task* task){
    TaskImage image;
    image.taskNum = task->getInfo().taskNum;
    image.remainCompute = task->GetRemainCompute();
    m_taskTimes[time] = image;
    float voltage = task->GetVoltage();
    m_voltageTimes[time] = voltage;
    m_lastVoltage = voltage;
    RecordTime(time);
}

void ScheduleOutput::RecordCtxSwitch(int time){
    m_csTimes.insert(time);
    m_voltageTimes[time] = m_lastVoltage;
    RecordTime(time);
}

void ScheduleOutput::PrintTable(){

    VariadicTable<int, std::string, std::string, float> vt({"Time", "Task #", "C Remain", "Voltage"});

    for (int time = 0; time <= m_maxTime; time++){
        if (m_taskTimes.find(time) != m_taskTimes.end()){
            TaskImage image = m_taskTimes[time];
            vt.addRow(
                time,
                std::to_string(image.taskNum),
                std::to_string(image.remainCompute),
                m_voltageTimes[time]
            );
        }
        else if (m_csTimes.find(time) != m_csTimes.end())
        {
            vt.addRow(time, "CS", "", m_voltageTimes[time]);
        }
    }

    vt.print(std::cout);

    std::cout << "CS = \"Context Switch\"" << std::endl;
}