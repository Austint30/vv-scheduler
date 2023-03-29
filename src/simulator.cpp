#include <functional>
#include <iostream>
#include "simulator.hpp"
#include "vendor/variatic_table.hpp"

using namespace std::placeholders;

Simulator::Simulator(std::queue<Task*>& taskQueue){
    m_taskQueue = taskQueue;
};

void Simulator::RunLoop(){

    SchedEventInfo eventInfo;
    
    eventInfo.onTaskProcessing = std::bind(&Simulator::HandleTaskProcessEvent, this, _1);
    eventInfo.onTaskCompleted = std::bind(&Simulator::HandleTaskCompleteEvent, this, _1);
    eventInfo.onTaskRejected = std::bind(&Simulator::HandleTaskRejectEvent, this, _1, _2);
    eventInfo.onTaskAccepted = std::bind(&Simulator::HandleTaskAcceptEvent, this, _1, _2);
    eventInfo.onContextSwitch = std::bind(&Simulator::HandleContextSwitchEvent, this, _1, _2, _3);

    m_schedImpl->Init(eventInfo);

    std::cout << "Time: 0" << std::endl;

    while (m_taskQueue.size() > 0 || m_schedImpl->IsProcessing()){
        if (m_taskQueue.size() > 0){
            auto nextTask = m_taskQueue.front();
            if (nextTask->HasArrived(m_time)){
                // Task has arrived. Remove from tasks queue and place on active tasks vector.
                std::cout << "\t🛬 Task " << nextTask->getInfo().taskNum << " has arrived at time " << m_time << std::endl;
                m_schedImpl->HandleArrivedTask(nextTask, m_time);
                m_taskQueue.pop();
                continue;
            }
        }

        m_time++;
        std::cout << "Time: " << m_time << std::endl;

        if (m_ctxSwitchTime > 0){
            m_output->AppendCtxSwitch();
            m_ctxSwitchTime--;
        }
        else{
            m_schedImpl->Tick(m_time);
            CheckDeadlines();
        }

        sleep(m_cycleDelay);
    }
}

void Simulator::CheckDeadlines(){
    auto taskQueue = m_schedImpl->GetTaskQueue();

    for (int i = 0; i < taskQueue.size(); i++)
    {
        auto task = taskQueue.at(i);

        if (task->GetRemainDeadline(m_time) < 0){
            throw std::runtime_error(
                std::string("☠ Task ") + std::to_string(task->getInfo().taskNum) 
                    + " has exceeded its deadline at time "
                    + std::to_string(task->getInfo().deadline)
                    + " (current time: " + std::to_string(m_time) + " )");
        }
    }
}

std::string Simulator::SchedPQToStr(){

    std::string str = "PQ: [ ";

    auto pq = m_schedImpl->GetTaskQueue();

    for (int i = 0; i < pq.size(); i++)
    {
        str += std::to_string(pq.at(i)->getInfo().taskNum) + " ";
    }

    str += "]";
    
    return str;
}

void Simulator::HandleTaskProcessEvent(Task* task){
    std::cout << "\t⚙️  Processing Task " << task->getInfo().taskNum <<
        " with " << task->GetRemainCompute() << " time left   " << SchedPQToStr();

    std::cout << std::endl;

    m_output->AppendTask(task);
}

void Simulator::HandleTaskCompleteEvent(Task* task){
    std::cout << "\t🏁 Task " << task->getInfo().taskNum << " has been completed at time " << m_time << std::endl;
}

void Simulator::HandleTaskRejectEvent(Task* task, float utilization){
    std::cout << "\t❌ Task " << task->getInfo().taskNum << " has been rejected at time " << m_time <<
    " with calculated utilization " << utilization << std::endl;
}

void Simulator::HandleTaskAcceptEvent(Task* task, float utilization){
    std::cout << "\t✅ Task " << task->getInfo().taskNum << " has been accepted at time " << m_time <<
    " with calculated utilization " << utilization << std::endl;
}

void Simulator::HandleContextSwitchEvent(Task* oldTask, Task* newTask, int switchTime){
    std::cout << "\t⏹ Task " << oldTask->getInfo().taskNum << " preempted by Task "
        << newTask->getInfo().taskNum << " at time " << m_time << std::endl;
    
    std::cout << "\tWaiting for context switch to finish. Context switch time: " << switchTime << std::endl;
    
    m_ctxSwitchTime += switchTime;
}

void Simulator::PrintSchedule(){
    m_output->PrintTable();
}