#include <iostream>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <errno.h>
#include "Parent.hpp"

Parent::Parent(int childPid)
    :_childPid(childPid)
    ,_isEnd(false) 
{
    std::cout << "[P] The child pid is " << _childPid << std::endl;
}

void Parent::Handle(pid_t pid) {
    struct user data{};
    ptrace(PTRACE_GETREGS, pid, 0, &data);
    long opcode = ptrace(PTRACE_PEEKDATA, pid, (void*)data.regs.rip, 0);

    std::cout << "[P] opcode: " << std::hex << opcode << std::endl;
    if(0x0b0f == (opcode & 0xffff)) {
        std::cout << "hacking...\n";
        data.regs.rax = 0x55 + data.regs.rdi;
    }

    data.regs.rip += 2;
    ptrace(PTRACE_SETREGS, pid, 0, &data);
}

void Parent::Debug() {
    while(!_isEnd) {
        int status = 0;
        int ret = waitpid(_childPid, &status, 0);
        std::cout << "[P] ret: " << ret 
            << ", status: " << status 
            << std::endl;

        if(WIFEXITED(status)) {
            std::cout << "[P] The child has exited.\n";
            _isEnd = true;
        } else if(WIFSIGNALED(status)){
            auto s = WTERMSIG(status);
            _isEnd = true;
        } else if (WIFSTOPPED(status)) {
            auto sig = WSTOPSIG(status);
            if(sig == SIGILL){
                Handle(_childPid);
            }
        }
        ptrace(PTRACE_CONT, _childPid, 0, 0);
    }    
    
}
Parent::~Parent() {
    std::cout << "[P] The parent is ending...\n";
}
