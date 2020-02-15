#include "ObjectCode.h"

ObjectCode::ObjectCode(){
    index = 0;
    for (int i=0;i<1000;i++)
        object[i] = -1;
}

void ObjectCode::insertInstruction(int code){
    object[index] = code;
    codeSize++;
}

int ObjectCode::getInstruction(){
    return object[index];
}

int ObjectCode::currentLocation() {
    return index;
}

void ObjectCode::nextLocation() {
    index++;
}

void ObjectCode::jumpLocation(int p){
    index += p;
}

int ObjectCode::getCodeSize(){
    return codeSize;
}

void ObjectCode::rewind(){
    index = 0;
}

void ObjectCode::insertInstructionAt (int src,int val){
    object[src] = val;
}