#include "Generator.h"

Generator::Generator(Parser *p, ObjectCode *oc){
    objCode = oc;
    parser = p;
}

void Generator::Run(){
     generate(parser->getRoot());
     objCode->rewind();
}

void Generator::g(char c) {
    objCode->insertInstruction((int)c);
    objCode->nextLocation();
}

int Generator::hole() {
    int ptr = objCode->currentLocation();
    objCode->nextLocation();
    return ptr;
}

void Generator::fix(int src, int dst) {
    objCode->insertInstructionAt(src, dst-src);
}

void Generator::generate (Node *x)
{
    int p1, p2;
    switch (x->kind)
    {
        case VAR  :
            g(IFETCH);
            g(x->val);
            break;
        case CST  :
            g(IPUSH);
            g(x->val);
            break;
        case ADD  :
            generate(x->o1);
            generate(x->o2);
            g(IADD);
            break;
        case SUB  :
            generate(x->o1);
            generate(x->o2);
            g(ISUB);
            break;
        case LT   :
            generate(x->o1);
            generate(x->o2);
            g(ILT);
            break;
        case SET  :
            generate(x->o2);
            g(ISTORE);
            g(x->o1->val);
            break;
        case IF1  :
            generate(x->o1);
            g(JZ);
            p1=hole();
            generate(x->o2);
            fix(p1,objCode->currentLocation());
            break;
        case IF2  :
            generate(x->o1);
            g(JZ);
            p1=hole();
            generate(x->o2);
            g(JMP);
            p2=hole();
            fix(p1,objCode->currentLocation());
            generate(x->o3);
            fix(p2,objCode->currentLocation());
            break;
        case WHILE:
            p1=objCode->currentLocation();
            generate(x->o1);
            g(JZ);
            p2=hole();
            generate(x->o2);
            g(JMP);
            fix(hole(),p1);
            fix(p2,objCode->currentLocation());
            break;
        case DO   :
            p1=objCode->currentLocation();
            generate(x->o1);
            generate(x->o2);
            g(JNZ);
            fix(hole(),p1);
            break;
        case EMPTY: break;
        case SEQ  :
            generate(x->o1);
            generate(x->o2);
            break;
        case EXPR :
            generate(x->o1);
            g(IPOP);
            break;
        case PROG :
            generate(x->o1);
            g(HALT);
            break;
    }
}