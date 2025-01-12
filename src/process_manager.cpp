#include "process_manager.h"
#include <stdexcept>
#include <iostream>

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
            CloseHandle(pi.hThread); 
        } else {
            throw std::runtime_error("Unable to create process: " + std::to_string(GetLastError()));
        }
#else
        pid_t pid = fork();
        if (pid == 0) {
            std::cout << "Child process executing command: " << command << std::endl;
            execlp(command.c_str(), command.c_str(), nullptr);
            perror("execvp failed");
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
            if (!GetExitCodeProcess(process.handle, (LPDWORD)&exitCode)) {
                throw std::runtime_error("Failed to get exit code: " + std::to_string(GetLastError()));
            }
            CloseHandle(process.handle);
        } else {
            throw std::runtime_error("Failed to wait for process: " + std::to_string(GetLastError()));
        }
#else
        int status;
        if (waitpid(process.pid, &status, 0) == -1) {
            perror("waitpid failed");
            throw std::runtime_error("Failed to wait for process.");
        }
        if (WIFEXITED(status)) {
            exitCode = WEXITSTATUS(status);
        } else {
            std::cerr << "Process did not exit normally." << std::endl;
        }
#endif

        return exitCode;
    }
}
