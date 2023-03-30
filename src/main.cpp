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
    try {
        sim->RunLoop();
    }
    catch(std::runtime_error e){
        sim->PrintSchedule();
        std::cout << "Schedule incomplete due to error:" << std::endl;
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nSimulation finished. Printing resulting schedule:" << std::endl;
    
    sim->PrintSchedule();

    std::cout << "Finished." << std::endl;
    return 0;
}
