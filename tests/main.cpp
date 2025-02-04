#include <iostream>
#include "process_manager.h"

void testProcessManager() {
    std::cout << "Library ProcessManager Tests:\n";

    // Test 1
    #ifdef _WIN32
        auto process = ProcessManager::startProcess("ping google.com");
    #else //execlp needs full path to program
        auto process = ProcessManager::startProcess("/usr/bin/echo");

    #endif
    int exitCode = ProcessManager::waitForProcess(process);

    std::cout << "Proccess returned code: " << exitCode << std::endl;

    // Test 2
    try {
        auto badProcess = ProcessManager::startProcess("blablabla");
        int badExitCode = ProcessManager::waitForProcess(badProcess);
        std::cout << "Unexpected behavior(expected on linux): process returned code: " << badExitCode << std::endl;
        //no file or directory, so process returns 1 on linux
    } catch (const std::exception& e) {
        std::cout << "Error occured while process started: " << e.what() << std::endl;
    }
}

int main() {
    testProcessManager();
    return 0;
}
