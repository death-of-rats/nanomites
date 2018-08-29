#include "Child.hpp"
#include <iostream>
#include <sys/ptrace.h>

Child::Child() {
    ptrace(PTRACE_TRACEME, 0, 0, 0);
}

__attribute__((naked)) int Decode(int, int) {
    __asm("xor rdi,rsi");
    __asm("ud2");
    __asm("ret");
}

/* 10011001b - init res
 * 
 */
int Child::Run(int pin) {
    int val = pin, res = 0x99;
    for(int index = 0; index < 4; ++index){
        res = Decode(val & 0xff, res);
        val >>= 8;
    }
    return res;
}

Child::~Child() {
    std::cout << "[C] The child is ending...\n";
}
