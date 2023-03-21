#include <iostream>
#include <queue>
#include "./task.hpp"
#include "./reader.hpp"

int main(int argc, char const *argv[])
{

    std::queue<Task> queue;
    readToQueue(queue);

    while (queue.size() > 0){
        Task task = queue.front();
        queue.pop();
        std::cout << task.arrive << " " << task.compute << " " << task.deadline << " " << task.ctxswitch << std::endl;
    }
    
    return 0;
}
