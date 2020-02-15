#ifndef COMPILER_OBJECTCODE_H
#define COMPILER_OBJECTCODE_H
#include <iostream>
using namespace std;

class ObjectCode {
private:
    int codeSize=0;
    char object[1000];
    char *inLocation;
    int  index;

public:
    ObjectCode();
    void insertInstruction(int);
    int getInstruction();
    int currentLocation();
    void nextLocation();
    void jumpLocation(int);
    void insertInstructionAt (int,int);
    int getCodeSize();
    void rewind();
};

#endif //COMPILER_OBJECTCODE_H
