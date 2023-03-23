#pragma once

#include "vector"
#include "../task.hpp"

class BaseScheduler
{
private:
    std::vector<Task*>* m_activeTasks;
public:
    BaseScheduler(std::vector<Task*>* activeTasks){
        m_activeTasks = activeTasks;
    };
    ~BaseScheduler();
};
