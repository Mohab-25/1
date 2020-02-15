#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H
#include "Lexer.h"
#include "Node.h"

class Parser {
private:
    Lexer *lex;
    Node *root;
    enum { DO_SYM, ELSE_SYM, IF_SYM, WHILE_SYM, LBRA, RBRA, LPAR, RPAR,
        PLUS, MINUS, LESS, SEMI, EQUAL, INT, ID, EOI, Mul };

    enum { VAR, CST, ADD, SUB, LT, SET,
        IF1, IF2, WHILE, DO, EMPTY, SEQ, EXPR, PROG };
public:
    Parser(Lexer *lex);
    Node *new_node(int k);
    Node *paren_expr();
    Node *term();
    Node *sum();
    Node *test();
    Node *expr();
    Node *statement();
    Node *program();
    Node* getRoot();
    void Run();
};
#endif //COMPILER_PARSER_H



