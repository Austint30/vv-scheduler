#include <iostream>
#include <queue>
#include "./task.hpp"
#include "./reader.hpp"
#include "./simulator.hpp"
#include "./scheduler/sts.hpp"

int main(int argc, char const *argv[])
{

    std::queue<Task*> queue;
    std::vector<float> voltages;
    inputToQueue(queue, voltages);

    auto sim = new Simulator(queue);
    auto sts = new STSScheduler();

    if (voltages.size() > 0){
        sts->SetDescreteVoltages(voltages);
    }

    sim->UseSchedImpl(sts);
    sim->SetCycleDelay(0);

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
