#include "../src/compiler.cc"

int main(){
    char regex[]="(asd|fns*daj)*|fsj(dav)*f(fs|da)";
    int length = strlen(regex);
    AST ast(regex, length);
    //ast.traverse();
    GlushKov_NFA NFA(&ast);
    NFA.traverse();
    return 0;
}