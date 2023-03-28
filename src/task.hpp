#pragma once

#include "./util.hpp"

// Information about a task from the input
struct TaskInfo {
    int taskNum;
    int arrive;
    int compute;
    int deadline;
    int ctxswitch;
};

class Task
{
private:
    int m_currCompute;
    
    TaskInfo m_info;

public:
    Task(TaskInfo info);
    ~Task(){};
    TaskInfo getInfo(){ return m_info; };

    bool HasArrived(int time){ return m_info.arrive <= time; }
    bool IsComplete(){ return m_currCompute <= 0; };
    int GetRemainDeadline(int time){ return m_info.deadline - time; };
    int GetRemainCompute(){ return m_currCompute; };

    void AdvanceCompute(){
        if (m_currCompute > 0){
            m_currCompute--;
        }
    };

    friend bool operator < (const Task& lhs, const Task& rhs){
        return lhs.m_info.deadline < rhs.m_info.deadline;
    }
};

