#include "./task.hpp"

Task::Task(TaskInfo info){
    m_info = info;
    m_currCompute = info.compute;
}