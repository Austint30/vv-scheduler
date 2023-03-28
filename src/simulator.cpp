#include <functional>
#include <iostream>
#include "simulator.hpp"

using namespace std::placeholders;

Simulator::Simulator(std::queue<Task*>& taskQueue){
    m_taskQueue = taskQueue;
};

void Simulator::RunLoop(){

    SchedEventInfo eventInfo;
    eventInfo.onTaskCompleted = std::bind(&Simulator::HandleTaskCompleteEvent, this, _1);
    eventInfo.onTaskRejected = std::bind(&Simulator::HandleTaskRejectEvent, this, _1, _2);
    eventInfo.onTaskAccepted = std::bind(&Simulator::HandleTaskAcceptEvent, this, _1, _2);

    m_schedImpl->Init(eventInfo);

    while (m_taskQueue.size() > 0 || m_schedImpl->IsProcessing()){
        if (m_taskQueue.size() > 0){
            auto nextTask = m_taskQueue.front();
            if (nextTask->HasArrived(m_time)){
                // Task has arrived. Remove from tasks queue and place on active tasks vector.
                std::cout << "Task " << nextTask->getInfo().taskNum << " has arrived at time " << m_time << std::endl;
                m_schedImpl->HandleArrivedTask(nextTask, m_time);
                m_taskQueue.pop();
                continue;
            }
        }

        m_schedImpl->Tick(m_time);

        sleep(m_cycleDelay);
        m_time++;
    }
}

void Simulator::HandleTaskCompleteEvent(Task* task){
    std::cout << "🏁 Task " << task->getInfo().taskNum << " has been completed at time " << m_time << std::endl;
}

void Simulator::HandleTaskRejectEvent(Task* task, float utilization){
    std::cout << "❌ Task " << task->getInfo().taskNum << " has been rejected at time " << m_time <<
    " with calculated utilization " << utilization << std::endl;
}

void Simulator::HandleTaskAcceptEvent(Task* task, float utilization){
    std::cout << "✅ Task " << task->getInfo().taskNum << " has been accepted at time " << m_time <<
    " with calculated utilization " << utilization << std::endl;
}