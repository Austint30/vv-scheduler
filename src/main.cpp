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

    auto sim = new Simulator(queue);
    sim->UseSchedImpl(new STSScheduler());
    sim->SetCycleDelay(1);
    sim->RunLoop();

    std::cout << "Finished." << std::endl;
    return 0;
}
