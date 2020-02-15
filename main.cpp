#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "VirtualMachine.h"
#include "Generator.h"
#include "ObjectCode.h"

using namespace std;

void display(string source){
    ifstream ifile;
    char ch;
    ifile.open(source);
    while (!ifile.eof()){
        ifile.get(ch);
        cout << ch;
    }
}

int main()
{
    string souurcename = "t1.c";

    display(souurcename);
    ObjectCode *objectCode = new ObjectCode();

    bool log = false;
    Lexer  *lex = new Lexer(souurcename,log);

    Parser *parser = new Parser(lex);
    parser->Run();

    Generator *generator = new Generator(parser, objectCode);
    generator->Run();

    VirtualMachine *vm = new VirtualMachine(objectCode);
    vm->run();

    cout << "\n\n\nRun :\n";
    vm->showOutput();

    return 0;
}