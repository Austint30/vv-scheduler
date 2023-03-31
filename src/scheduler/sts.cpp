#include <algorithm>
#include "sts.hpp"

float STSScheduler::CalcUj(int j, int time, TASK_PRIORITY_QUEUE activeTasksCopy){
    int remainingSum = 0;
    int origSize = activeTasksCopy.size();
    Task* taskAtJ = nullptr;

    Task* currTop = m_activeTasks.size() > 0 ? m_activeTasks.top() : nullptr;

    // Take context switch time into account
    if (activeTasksCopy.top() != currTop){
        remainingSum += activeTasksCopy.top()->getInfo().ctxswitch;
        if (currTop != nullptr){
            remainingSum += currTop->getInfo().ctxswitch;
        }
    }

    for (int i = 0; i <= j; i++)
    {
        remainingSum += activeTasksCopy.top()->GetRemainCompute();

        // Take context switches into account when task finishes
        // *2 is used b/c ctxswitch is applied both before and after the task
        remainingSum += activeTasksCopy.top()->getInfo().ctxswitch*2;
        
        if (i == j){
            taskAtJ = activeTasksCopy.top();
        }
        activeTasksCopy.pop();
    }

    int divisor = static_cast<float>(taskAtJ->getInfo().deadline - time);
    float u = static_cast<float>(remainingSum) / divisor;
    
    return u;
}

float STSScheduler::CalcMaxU(int time, TASK_PRIORITY_QUEUE& activeTasks){

    float maxU = 0;

    for (int j = 0; j < activeTasks.size(); j++)
    {
        float uAtJ = CalcUj(j, time, activeTasks);
        maxU = std::max(maxU, uAtJ);
    }
    
    return maxU;
}

void STSScheduler::HandleArrivedTask(Task* task, int time){

    // Create a copy of m_activeTasks and add this newly
    // arrived task to it. Then perform an acceptance test.
    auto activeTasksCopy = m_activeTasks;
    auto acceptedTasksCopy = m_acceptedTasks;
    
    while (acceptedTasksCopy.size() > 0){
        activeTasksCopy.push(acceptedTasksCopy.front());
        acceptedTasksCopy.pop();
    }

    activeTasksCopy.push(task);

    float utilization = CalcMaxU(time, activeTasksCopy);

    if (utilization > 1){
        // Cannot be scheduled. Reject task.
        DispatchRejectTaskEvent(task, utilization);
    }
    else
    {
        // Can be scheduled. Push to m_accptedTasks queue
        m_acceptedTasks.push(task);
        DispatchAcceptTaskEvent(task, utilization);
    }
}

void STSScheduler::Tick(int time){

    if (m_acceptedTasks.size() > 0){
        // New tasks were accepted

        while (m_acceptedTasks.size() > 0){
            PutArrivedTask(m_acceptedTasks.front());
            m_acceptedTasks.pop();
        }
        float u = CalcMaxU(time, m_activeTasks);
        float newVoltage = CalcVoltage(u);
        if (m_currentVoltage != newVoltage)
            m_currentVoltage = newVoltage;
    }

    if (m_activeTasks.size() == 0) return;

    // Advance the computation of the top of the priority queue.
    Task* earliestTask = m_activeTasks.top();

    // Detect context switch
    if (earliestTask != m_lastTask){
        DispatchContextSwitch(m_lastTask, earliestTask);
        m_lastTask = earliestTask;
        return;
    }

    if (m_activeTasks.size() > 0){

        earliestTask = m_activeTasks.top();
        earliestTask->SetVoltage(m_currentVoltage);
        earliestTask->AdvanceCompute();
        DispatchProcessTaskEvent(earliestTask);
    }

    if (earliestTask->IsComplete()){
        // This task is complete. Remove from m_activeTasks and
        // let simulator know.
        m_activeTasks.pop();
        DispatchCompleteTaskEvent(earliestTask);
    }

    m_lastTask = earliestTask;
}

float STSScheduler::CalcVoltage(float utilization){
    if (m_descreteVoltages.size() > 0){
        // Pick from list of voltages (rounding up)
        for (int i = 0; i < m_descreteVoltages.size(); i++)
        {
            if (m_descreteVoltages[i] > utilization){
                return m_descreteVoltages[i];
            }
        }
        
    }
    return utilization;
}

/*
auto currTask = m_activeTasks.size() > 0 ? m_activeTasks.top() : nullptr;

if (currTask != nullptr && m_activeTasks.top() != currTask){
    // Preemption detected!
    DispatchContextSwitch(currTask, m_activeTasks.top());
}

*/