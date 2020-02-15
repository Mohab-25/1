#include "Lexer.h"
#include <cassert>

Lexer::Lexer(string fname, bool log) {
    logging = log;
    try{
        source.open(fname);
    }
    catch (exception &e){
        cout << e.what()
             << endl;
        exit(1);
    }
}

Lexer::~Lexer(){
    source.close();
    assert(!source.fail( ));
}

int Lexer::getSym(){
    return sym;
}

string Lexer::getIdName(){
    return id_name;
}

int Lexer::getIntVal(){
    return int_val;
}

void Lexer::syntax_error() {
    cerr << "syntax error\n";
    exit(1);
}

bool Lexer::next_ch() {
    bool flag = false;
    if (!source.fail()){
        source.get(ch);
        flag = true;
    }
    return flag;
}

void Lexer::next_sym(){

    if (source.fail()){
        sym=EOI;
        Log("EOI", "$");
        eofreached = true;
    }

    if (!eofreached){
    if (ch == '\n' || ch == ' ') {
            while (ch == '\n' || ch == ' ') {
                next_ch();
            }
    }

    if (punc.count(ch)>0) {
        if (ch == '{') {
            Log("LBRA",ch);
            sym = LBRA;
        }
        if (ch == '}') {
            Log("RBRA",ch);
            sym = RBRA;
        }
        if (ch == '(') {
            Log("LPAR",ch);
            sym = LPAR;
        }
        if (ch == ')') {
            Log("RPAR",ch);
            sym = RPAR;
        }
        if (ch == '+') {
            Log("PLUS",ch);
            sym = PLUS;
        }
        if (ch == '-') {
            Log("MINUS",ch);
            sym = MINUS;
        }
        if (ch == '<') {
            Log("LESS",ch);
            sym = LESS;
        }
        if (ch == ';') {
            Log("SEMI",ch);
            sym = SEMI;
        }
        if (ch == '=') {
            Log("EQUAL",ch);
            sym = EQUAL;
        }
        if (ch == '*') {
            Log("Multiply",ch);
            sym = Mul;
        }
        next_ch();
    }
    else
      if (ch >= '0' && ch <= '9')
      {
          int_val = 0;
          while (ch >= '0' && ch <= '9') {
              int_val = int_val * 10 + (ch - '0');
              next_ch();
          }
          sym = INT;
          Log("INT",int_val);
      }
      else
          if (ch >= 'a' && ch <= 'z')
          {
              id_name = "";
              while ((ch >= 'a' && ch <= 'z') || ch == '_') {
                  id_name += ch;
                  next_ch();
              }
              string kw="";
              if (words.count(id_name) > 0) {
                  if (id_name.compare("while") == 0) {
                      sym = WHILE_SYM;
                      kw = "WHILE_SYM";
                  } else if (id_name.compare("do") == 0) {
                      sym = DO_SYM;
                      kw = "DO_SYM";
                  } else if (id_name.compare("if") == 0) {
                      sym = IF_SYM;
                      kw = "IF_SYM";
                  } else if (id_name.compare("else") == 0) {
                      sym = ELSE_SYM;
                      kw = "ELSE_SYM";
                  }
                  Log(kw, id_name);
                  next_ch();
              }
              else
                  {
                    sym = ID;
                    Log("ID", id_name);
                  }
          }
          else
           syntax_error();
      }
}

template<class TOKEN, class LEXIME>
void Lexer::Log(TOKEN token, LEXIME lexime){
    if (logging)
        cout << " < " << token << " , " << lexime << " > " << endl;
}
