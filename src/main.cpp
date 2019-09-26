#include <iostream>
#include <chrono>
#include <thread>

#include <vector>
#include <algorithm>
#include <functional>

#include "MulticastSenderLib.hpp"
#include "LoggingLib.hpp"

using namespace std::literals::chrono_literals;

void sort();

int main(int argc, char *argv[])
{
    Logging::Info("Initializing Service...");

    // auto tsender1 = std::thread(MulticastSenderLib::Run, "/home/hector/MulticastData/Tuesday_Canal_4.bmv", "239.255.0.1", 30001);
    auto tsender2 = std::thread(MulticastSenderLib::Run, "~/MulticastData/Tuesday_Canal_1_Crudo.biva", "239.255.0.2", 30002);

    std::this_thread::sleep_for(1s);

    // tsender1.join();
    tsender2.join();

    Logging::Info("Finalizing Service...");

    return 0;
}
