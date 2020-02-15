#include "Parser.h"

Parser::Parser(Lexer *lex){
    this->lex = lex;
}

Node *Parser::new_node(int k)
{
    Node *x = new Node();
    x->kind = k;
    return x;
}

Node *Parser::term()  /* <term> ::= <id> | <int> | <paren_expr> */
{
    Node *x;
    if (lex->getSym() == ID) {
        x=new_node(VAR);
        x->val=lex->getIdName()[0]-'a';
        lex->next_sym();
    }
    else
    if (lex->getSym() == INT) {
        x=new_node(CST);
        x->val=lex->getIntVal();
        lex->next_sym();
    }
    else
        x = paren_expr();

    return x;
}

Node *Parser::sum()  /* <sum> ::= <term> | <sum> "+" <term> | <sum> "-" <term> */
{
    Node *t, *x = term();
    while (lex->getSym() == PLUS || lex->getSym() == MINUS||lex->getSym()== Mul)
    {
        t=x; x=new_node(lex->getSym()==PLUS?ADD:SUB);
        lex->next_sym();
        x->o1=t;
        x->o2=term();
    }
    return x;
}

Node *Parser::test()  /* <test> ::= <sum> | <sum> "<" <sum> */
{
    Node *t, *x;
    x = sum();
    if (lex->getSym() == LESS)
    {
        t=x;
        x=new_node(LT);
        lex->next_sym();
        x->o1=t;
        x->o2=sum();
    }
    return x;
}

Node *Parser::expr()  /* <expr> ::= <test> | <id> "=" <expr> */
{
    Node *t, *x;
    if (lex->getSym() != ID)
        return test();
    x = test();
    if (x->kind == VAR && lex->getSym() == EQUAL)
    {
        t=x;
        x=new_node(SET);
        lex->next_sym();
        x->o1=t;
        x->o2=expr();
    }
    return x;
}

Node *Parser::paren_expr()  /* <paren_expr> ::= "(" <expr> ")" */
{
    Node *x;
    if (lex->getSym() == LPAR)
        lex->next_sym();
    else
        lex->syntax_error();

    x = expr();
    if (lex->getSym() == RPAR)
        lex->next_sym();
    else
        lex->syntax_error();
    return x;
}

Node *Parser::statement()
{
    Node *t, *x;
    if (lex->getSym() == IF_SYM)  /* "if" <paren_expr> <statement> */
    {
        x = new_node(IF1);
        lex->next_sym();
        x->o1 = paren_expr();
        x->o2 = statement();
        if (lex->getSym() == ELSE_SYM)  /* ... "else" <statement> */
        {
            x->kind = IF2;
            lex->next_sym();
            x->o3 = statement();
        }
    }
    else
    if (lex->getSym() == WHILE_SYM)  /* "while" <paren_expr> <statement> */
    {
        x = new_node(WHILE);
        lex->next_sym();
        x->o1 = paren_expr();
        x->o2 = statement();
    }
    else
    if (lex->getSym() == DO_SYM)  /* "do" <statement> "while" <paren_expr> ";" */
    {
        x = new_node(DO);
        lex->next_sym();
        x->o1 = statement();
        if (lex->getSym() == WHILE_SYM)
            lex->next_sym();
        else
            lex->syntax_error();
        x->o2 = paren_expr();
        if (lex->getSym() == SEMI)
            lex->next_sym();
        else
            lex->syntax_error();
    }
    else
    if (lex->getSym() == SEMI)  /* ";" */
    {
        x = new_node(EMPTY);
        lex->next_sym();
    }
    else
    if (lex->getSym() == LBRA)  /* "{" { <statement> } "}" */
    {
        x = new_node(EMPTY);
        lex->next_sym();
        while (lex->getSym() != RBRA)
        {
            t=x;
            x=new_node(SEQ);
            x->o1=t;
            x->o2=statement();
        }
        lex->next_sym();
    }
    else  /* <expr> ";" */
    {
        x = new_node(EXPR);
        x->o1 = expr();
        if (lex->getSym() == SEMI)
            lex->next_sym();
        else
            lex->syntax_error();
    }
    return x;
}

Node *Parser::program()  /* <program> ::= <statement> */
{
    Node *x = new_node(PROG);
    lex->next_sym();
    x->o1 = statement();
    if (lex->getSym() != EOI)
        lex->syntax_error();

    root = x;
    return x;
}

void Parser::Run(){
    program();
}

Node* Parser::getRoot(){
    return root;
}