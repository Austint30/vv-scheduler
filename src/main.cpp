#include <iostream>
#include <queue>
#include "./task.hpp"
#include "./reader.hpp"
#include "./simulator.hpp"
#include "./scheduler/sts.hpp"

int main(int argc, char const *argv[])
{

    std::queue<Task*> queue;
    inputToQueue(queue);

    auto sim = new Simulator<STSScheduler>(queue);
    sim->SetCycleDelay(1);
    sim->RunLoop();

    
    return 0;
}
