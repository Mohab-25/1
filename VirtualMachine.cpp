#include "VirtualMachine.h"

VirtualMachine::VirtualMachine(ObjectCode *oc) {

    instructions.insert(make_pair(0,"IFETCH"));
    instructions.insert(make_pair(1,"ISTORE"));
    instructions.insert(make_pair(2,"IPUSH"));
    instructions.insert(make_pair(3,"IPOP"));
    instructions.insert(make_pair(4,"IADD"));
    instructions.insert(make_pair(5,"ISUB"));
    instructions.insert(make_pair(6,"ILT"));
    instructions.insert(make_pair(7,"JZ"));
    instructions.insert(make_pair(8,"JNZ"));
    instructions.insert(make_pair(9,"JMP"));

    for (int i=0; i<26; i++) globals[i] = 0;
    ocode = oc;
    codeSize = ocode->getCodeSize();
    ocode->rewind();
}

int VirtualMachine::getGlobals(int id) {
    return globals[id];
}

void VirtualMachine::setGlobals(int id, int val) {
    globals[id]=val;
}

void VirtualMachine::showOutput() {
    for (int i=0; i<26; i++)
        if (globals[i] != 0)
            cout << (char)(i+97) << " = "
                 << globals[i] << endl;
}

void VirtualMachine::run()
{
    int i=0;
    while (i<codeSize && ocode->getInstruction()!=HALT)
    {
        int code = ocode->getInstruction();
        ocode->nextLocation();

        if (code == IFETCH){
            st.push(globals[ocode->getInstruction()]);
            ocode->nextLocation();
            continue;
        }

        if (code == ISTORE){
            globals[ocode->getInstruction()] = st.top();
            ocode->nextLocation();
            continue;
        }

        if (code == IPUSH) {
            st.push(ocode->getInstruction());
            ocode->nextLocation();
            continue;
        }

        if (code == IPOP) {
            st.pop();
            continue;
        }

        if (code == IADD) {
            int v1=st.top();
            st.pop();
            int v2=st.top();
            st.pop();
            st.push(v2 + v1);
            continue;
        }

        if (code == ISUB) {
            int v1=st.top();
            st.pop();
            int v2=st.top();
            st.pop();
            st.push(v2 - v1);
            continue;
        }

        if (code == ILT) {
            int v1=st.top();
            st.pop();
            int v2=st.top();
            st.pop();
            st.push(int(v2 < v1));
            continue;
        }

        if (code == JMP) {
            ocode->jumpLocation(ocode->getInstruction());
            continue;
        }

        if (code == JZ) {
            //st.pop();
            if (st.top() == 0)
                ocode->jumpLocation(ocode->getInstruction());
            else
                ocode->nextLocation();
            st.pop();
            continue;
        }

        if (code == JNZ) {
            st.pop();
            if (st.top() != 0)
                ocode->jumpLocation(ocode->getInstruction());
            else
                ocode->nextLocation();
            continue;
        }
        if (code == HALT) {
            continue;
        }
        i++;
    }
}