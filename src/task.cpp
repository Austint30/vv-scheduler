#include "./task.hpp"

Task::Task(TaskInfo info){
    m_info = info;
    m_currCompute = info.compute;
}

Task* Task::ParseLine(std::string taskStr){
    TaskInfo info = TaskInfo();
    auto numberStrs = splitWhitespace(taskStr);
    info.arrive = std::stoi(numberStrs.at(0));
    info.compute = std::stoi(numberStrs.at(1));
    info.deadline = std::stoi(numberStrs.at(2));
    info.ctxswitch = std::stoi(numberStrs.at(3));
    return new Task(info);
}