#pragma once

#include <queue>
#include "./task.hpp"
#include "./scheduler/scheduler.hpp"

#define SCHED_IMPL_TEMPLATE template<class SchedImpl>

SCHED_IMPL_TEMPLATE
class Simulator
{
private:
    int m_time = 0;
    int m_cycleDelay = 1; // seconds
    std::queue<Task*> m_taskQueue;
    std::vector<Task*> m_activeTasks;
    SchedImpl* m_schedImpl;

public:
    Simulator(std::queue<Task*>& taskQueue){
        m_taskQueue = taskQueue;
    };
    ~Simulator();

    void SetCycleDelay(int delay){ m_cycleDelay = delay; };
    void RunLoop(){
        while (!m_taskQueue.empty()){

            auto nextTask = m_taskQueue.back();
            if (nextTask->HasArrived(m_time)){

                // Task has arrived. Remove from tasks queue and place on active tasks vector.
                m_activeTasks.push_back(nextTask);
                m_taskQueue.pop();
            }




            m_time++;
        }
    }
};