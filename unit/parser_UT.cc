#include "../src/parser.cc"

int main(){
    char regex[]="(asd|fns*daj)*|fsj(dav)*f(fs|da)";
    int length = strlen(regex);
    AST ast(regex, length);
    ast.traverse();
    return 0;
}