#include <algorithm>
#include "sts.hpp"

float STSScheduler::CalcUj(int j, int time, TASK_PRIORITY_QUEUE activeTasksCopy){
    int remainingSum = 0;
    int origSize = activeTasksCopy.size();
    Task* taskAtJ = nullptr;

    for (int i = 0; i <= j; i++)
    {
        remainingSum += activeTasksCopy.top()->GetRemainCompute();
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
        maxU = std::max(maxU, CalcUj(j, time, activeTasks));
    }
    
    return maxU;
}

void STSScheduler::HandleArrivedTask(Task* task, int time){
    if (m_activeTasks.size() == 0){
        // Nothing in priority queue. Just insert it.
        PutArrivedTask(task);
        return;
    }

    // Create a copy of m_activeTasks and add this newly
    // arrived task to it. Then perform an acceptance test.
    auto activeTasksCopy = m_activeTasks;
    activeTasksCopy.push(task);

    float utilization = CalcMaxU(time, activeTasksCopy);

    if (utilization > 1){
        // Cannot be scheduled. Reject task.
        DispatchRejectTaskEvent(task, utilization);
    }
    else
    {
        // Can be scheduled. Dispatch event to let simulator know
        // and push to m_activeTasks
        PutArrivedTask(task);
        DispatchAcceptTaskEvent(task, utilization);
    }
}

void STSScheduler::Tick(int time){
    if (m_activeTasks.size() == 0) return;

    // Advance the computation of the top of the priority queue.
    Task* earliestTask = m_activeTasks.top();

    DispatchProcessTaskEvent(earliestTask);

    if (earliestTask->IsComplete()){
        // This task is complete. Remove from m_activeTasks and
        // let simulator know.
        PopTask();
        DispatchCompleteTaskEvent(earliestTask);
        return;
    }

    earliestTask->AdvanceCompute();
}

/*
auto currTask = m_activeTasks.size() > 0 ? m_activeTasks.top() : nullptr;

if (currTask != nullptr && m_activeTasks.top() != currTask){
    // Preemption detected!
    DispatchContextSwitch(currTask, m_activeTasks.top());
}

*/