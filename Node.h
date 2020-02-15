#ifndef COMPILER_NODE_H
#define COMPILER_NODE_H

class Node {
public:
    int kind;
    Node *o1=nullptr, *o2=nullptr, *o3=nullptr;
    int val;
};

#endif //COMPILER_NODE_H

