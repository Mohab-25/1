#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <iostream>
#include <set>
#include <fstream>

using namespace std;

enum { DO_SYM, ELSE_SYM, IF_SYM, WHILE_SYM, LBRA, RBRA, LPAR, RPAR,
    PLUS, MINUS, LESS, SEMI, EQUAL, INT, ID, EOI,Mul };

class Lexer {
private:
    ifstream source;
    set<string> words{"do","else","if","while"};
    set<char> punc={'{','}','(',')','+','-','<',';','=','*'};
    char ch = ' ';
    int sym;
    int int_val;
    string id_name;
    bool  eofreached=false;
    bool logging;
public:
    Lexer(string fname, bool l);
    ~Lexer();
    int getSym();
    string getIdName();
    int getIntVal();
    void syntax_error();
    bool next_ch();
    void next_sym();

    template<class TOKEN, class LEXIME>
    void Log(TOKEN token, LEXIME lexime);
};

#endif //COMPILER_LEXER_H
