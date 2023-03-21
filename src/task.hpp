#pragma once

#include "./util.hpp"

class Task
{
private:
    Task(){};
public:
    int arrive;
    int compute;
    int deadline;
    int ctxswitch;
    ~Task(){};
    static Task ParseLine(std::string taskStr)
    {
        Task task = Task();
        auto numberStrs = splitWhitespace(taskStr);
        task.arrive = std::stoi(numberStrs.at(0));
        task.compute = std::stoi(numberStrs.at(1));
        task.deadline = std::stoi(numberStrs.at(2));
        task.ctxswitch = std::stoi(numberStrs.at(3));
        return task;
    }
};

