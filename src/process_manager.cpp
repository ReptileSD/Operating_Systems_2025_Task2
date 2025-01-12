#include "process_manager.h"
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#endif

namespace ProcessManager {

    Process startProcess(const std::string& command) {
        Process process;

#ifdef _WIN32
        STARTUPINFOA si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        PROCESS_INFORMATION pi;
        ZeroMemory(&pi, sizeof(pi));

        if (CreateProcessA(
            nullptr,
            const_cast<char*>(command.c_str()), 
            nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {

            process.handle = pi.hProcess;
        } else {
            throw std::runtime_error("Unable to create process.");
        }

#else
        pid_t pid = fork();
        if (pid == 0) {
            execlp(command.c_str(), command.c_str(), nullptr);
            _exit(1);
        } else if (pid > 0) {
            process.pid = pid;
        } else {
            throw std::runtime_error("Unable to create process.");
        }
#endif

        return process;
    }

    int waitForProcess(const Process& process) {
        int exitCode = -1;

#ifdef _WIN32
        if (WaitForSingleObject(process.handle, INFINITE) == WAIT_OBJECT_0) {
            GetExitCodeProcess(process.handle, (LPDWORD)&exitCode);
        }
#else
        int status;
        waitpid(process.pid, &status, 0);
        if (WIFEXITED(status)) {
            exitCode = WEXITSTATUS(status);
        }
#endif

        return exitCode;
    }
}
