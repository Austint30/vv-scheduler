#include <iostream>
#include <queue>
#include "./task.hpp"

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

inline void readToQueue(std::queue<Task>& queue){
    int nTasks;

    std::cout << "Number of tasks: ";
    std::string nTasksStr;
    std::getline(std::cin, nTasksStr);
    nTasks = std::stoi(nTasksStr);
    std::cout << std::endl;
    int taskNum = 0;
    while (queue.size() < nTasks){
        taskNum++;
        std::string line;
        std::cout << "Task " << taskNum << ": ";
        std::getline(std::cin, line);
        std::cout << std::endl;
        line = removeLineEndings(line);
        if (line.length() == 0) continue;
        queue.push(Task::ParseLine(line));
    }
}