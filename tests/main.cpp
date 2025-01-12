#include <iostream>
#include "process_manager.h"

void testProcessManager() {
    std::cout << "Library ProcessManager Tests:\n";

    // Test 1
    auto process = ProcessManager::startProcess("ping google.com");
    int exitCode = ProcessManager::waitForProcess(process);

    std::cout << "Proccess returned code: " << exitCode << std::endl;

    // Test 2
    try {
        auto badProcess = ProcessManager::startProcess("blablabla");
        int badExitCode = ProcessManager::waitForProcess(badProcess);
        std::cout << "Unexpected behavior: process returned code: " << badExitCode << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error occured while process started: " << e.what() << std::endl;
    }
}

int main() {
    testProcessManager();
    return 0;
}
