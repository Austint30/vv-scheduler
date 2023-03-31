#pragma once

#include <cmath>

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
    float m_currCompute = 0.0;
    float m_currVoltage = 1.0;
    
    TaskInfo m_info;

public:
    Task(TaskInfo info){
        m_info = info;
    }
    ~Task(){};
    TaskInfo getInfo(){ return m_info; };

    bool HasArrived(int time){ return m_info.arrive <= time; };
    bool IsComplete(){ return m_currCompute >= m_info.compute; };
    int GetRemainDeadline(int time){ return m_info.deadline - time; };
    float GetRemainCompute(){ return std::max(0.0f, static_cast<float>(m_info.compute) - m_currCompute); };

    float GetProgress(){ return m_currCompute / static_cast<float>(m_info.compute); };

    void AdvanceCompute(){
        if (m_currCompute < m_info.compute){
            m_currCompute += m_currVoltage;
        }
    };

    void SetVoltage(float voltage){
        m_currVoltage = voltage;
    }

    float GetVoltage(){ return m_currVoltage; };
};

