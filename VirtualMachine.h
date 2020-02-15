#ifndef COMPILER_VIRTUALMACHINE_H
#define COMPILER_VIRTUALMACHINE_H

#include "Generator.h"
#include <iostream>
#include <map>
#include <stack>

class VirtualMachine {
private:
    int globals[26];
    ObjectCode *ocode;
    int codeSize;
    map<int,string> instructions;
    stack<int> st;

    enum instructions { IFETCH, ISTORE, IPUSH, IPOP, IADD,
        ISUB, ILT, JZ, JNZ, JMP, HALT};
public:
    VirtualMachine(ObjectCode *g);
    VirtualMachine()=delete;
    void run();
    int getGlobals(int id);
    void setGlobals(int id, int val);
    void showOutput();
};


#endif //COMPILER_VIRTUALMACHINE_H
