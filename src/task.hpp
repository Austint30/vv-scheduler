#pragma once

#include "./util.hpp"

// Information about a task from the input
struct TaskInfo {
    int arrive;
    int compute;
    int deadline;
    int ctxswitch;
};

class Task
{
    friend class BaseScheduler;
private:
    Task(TaskInfo info);
    int m_currCompute;
    
    TaskInfo m_info;

    void AdvanceCompute(){
        if (m_currCompute > 0){
            m_currCompute--;
        }
    };

public:
    ~Task(){};
    TaskInfo getInfo(){ return m_info; };
    static Task* ParseLine(std::string taskStr);

    bool HasArrived(int time){ return m_info.arrive <= time; }
    bool IsComplete(){ return m_currCompute <= 0; };
    int GetRemainDeadline(int time){ return m_info.deadline - time; };
};
