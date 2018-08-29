#include <iostream>
#include <memory>
#include <sys/types.h>
#include <unistd.h>

#include "Parent.hpp"
#include "Child.hpp"

int main(int argc, char* argv[]) {
    std::cout << "[M] Start app...\n";
    int pid = fork();
    if(0 != pid) {
        auto parentProc = std::make_unique<Parent>(pid);
        parentProc->Debug();
    } else {
        auto childProc = std::make_unique<Child>();
        int val = childProc->Run();
        std::cout << "[C] The child counted: " 
            << val << std::endl;
    }
    
    return 0;
}
