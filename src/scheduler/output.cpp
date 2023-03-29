#include <iostream>
#include "output.hpp"
#include "../vendor/variatic_table.hpp"

void ScheduleOutput::AppendTask(Task* task){
    m_scheduledTasks.push(task);
}

void ScheduleOutput::AppendCtxSwitch(){
    m_scheduledTasks.push(nullptr);
}

void ScheduleOutput::PrintTable(){

    VariadicTable<int, int> vt({"Time", "Task #"});

    int time = 0;
    while (!m_scheduledTasks.empty()){
        time++;
        auto task = m_scheduledTasks.front();
        vt.addRow(time, task->getInfo().taskNum);
        m_scheduledTasks.pop();
    }

    vt.print(std::cout);
}