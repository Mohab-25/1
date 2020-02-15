#ifndef COMPILER_GENERATOR_H
#define COMPILER_GENERATOR_H
#include "Node.h"
#include "Parser.h"
#include "ObjectCode.h"

class Generator {
    enum { IFETCH, ISTORE, IPUSH, IPOP, IADD,
            ISUB, ILT, JZ, JNZ, JMP, HALT };

    enum { VAR, CST, ADD, SUB, LT, SET,
        IF1, IF2, WHILE, DO, EMPTY, SEQ, EXPR, PROG };

    Parser *parser;
    ObjectCode *objCode;

    void g(char c) ;
    int hole();
    void fix(int src, int dst);
    void generate (Node *x);
public:
    char *getObjectCode();
    Generator()=delete;
    Generator(Parser *p, ObjectCode *oc);
    void Run();
};

#endif //COMPILER_GENERATOR_H
