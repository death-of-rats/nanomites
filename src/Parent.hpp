#pragma once
#include <sys/types.h>

#include "Child.hpp"

class Parent {
private:
    pid_t _childPid;
    bool _isEnd;
    
    void Handle(pid_t pid);
public:
    Parent(int childPid);
    ~Parent();
    void Debug();
};
