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

    VariadicTable<int, std::string> vt({"Time", "Task #"});

    int time = 0;
    while (!m_scheduledTasks.empty()){
        time++;
        auto task = m_scheduledTasks.size() > 0 ? m_scheduledTasks.front() : nullptr;
        if (task == nullptr)
            vt.addRow(time, "CS");
        else
            vt.addRow(time, std::to_string(task->getInfo().taskNum));
        m_scheduledTasks.pop();
    }

    vt.print(std::cout);

    std::cout << "CS = \"Context Switch\"" << std::endl;
}