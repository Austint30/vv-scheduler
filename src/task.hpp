#pragma once

#include <cmath>
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
    int m_currCompute = 0;
    float m_currVoltage = 1.0;
    int m_scaledComputeTime;
    
    TaskInfo m_info;

public:
    Task(TaskInfo info){
        m_info = info;
        m_scaledComputeTime = info.compute;
    }
    ~Task(){};
    TaskInfo getInfo(){ return m_info; };

    bool HasArrived(int time){ return m_info.arrive <= time; };
    bool IsComplete(){ return m_currCompute >= m_scaledComputeTime; };
    int GetRemainDeadline(int time){ return m_info.deadline - time; };
    int GetRemainCompute(){ return m_scaledComputeTime - m_currCompute; };

    int GetRemainComputeNoVolt(){ return m_info.compute - m_currCompute; }

    void AdvanceCompute(){
        if (m_currCompute < m_scaledComputeTime){
            m_currCompute++;
        }
    };

    void SetVoltage(float voltage){
        m_currVoltage = voltage;
        m_scaledComputeTime = floor(static_cast<float>(m_info.compute) * (1/voltage));
    }

    float GetVoltage(){ return m_currVoltage; };
};

