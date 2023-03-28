#pragma once

#include <iostream>
#include <queue>
#include "./task.hpp"
#include "./util.hpp"

inline std::string removeLineEndings(std::string str){
    std::string fixed;

    for (int i = 0; i < str.length(); i++)
    {
        char c = str.at(i);

        switch (c)
        {
        case '\n':
        case '\r':
            break;
        default:
            fixed += c;
        }
    }
    
    return fixed;
}

inline int parseNumTasks(std::string str){
    std::string fixed = str.replace(0, 16, "");

    return std::stoi(onlyAlNum(str));
}

inline std::vector<int> parseTask(std::string str){
    if (str.length() == 0)
        return std::vector<int>{};
    
    std::vector<int> values;
    bool inBrackets = false;

    std::string partial;

    for (int i = 0; i < str.length(); i++)
    {
        char c = str.at(i);
        if (c == '['){
            inBrackets = true;
            continue;
        }
        
        if (c == ']'){
            break;
        }

        if (c == ' ' && partial.length() > 0){
            values.push_back(std::stoi(partial));
            partial = "";
            continue;
        }

        if (inBrackets && std::isdigit(c)){
            partial += c;
        }
        else if (std::isdigit(c)){
            // Number outside of brackets? Must be task number.
            partial += c;
            continue;
        }
    }

    if (partial.length() > 0){
        values.push_back(std::stoi(partial));
    }
    
    return values;
}

inline void inputToQueue(std::queue<Task*>& queue){
    int nTasks;
    std::string nTasksStr;

    while (nTasksStr.empty()){
        std::string nTasksStr;
        std::getline(std::cin, nTasksStr);
        nTasks = parseNumTasks(nTasksStr);
        std::cout << std::endl;
        break;
    }
    
    while (queue.size() < nTasks){
        std::string line;
        std::getline(std::cin, line);
        std::cout << std::endl;
        line = removeLineEndings(line);
        if (line.length() == 0) continue;

        auto taskProps = parseTask(line);

        auto info = TaskInfo();
        info.taskNum = taskProps.at(0);
        info.arrive = taskProps.at(1);
        info.compute = taskProps.at(2);
        info.deadline = taskProps.at(3);
        info.ctxswitch = taskProps.at(4);

        Task* task = new Task(info);

        queue.push(task);
    }
}