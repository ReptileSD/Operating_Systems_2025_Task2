#pragma once

#include <string>

namespace ProcessManager {

    struct Process {
        int pid;
        void* handle;
    };

    Process startProcess(const std::string& command);

    int waitForProcess(const Process& process);

}
