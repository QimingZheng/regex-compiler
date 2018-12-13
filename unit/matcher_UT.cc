#include "../src/matcher.cc"

int main(){
    char regex[]="(asd|fns*daj)*|fsj(dav)*f(fs|da)";
    int length = strlen(regex);
    
    AST ast(regex, length);
    //ast.traverse();
    
    GlushKov_NFA NFA(&ast);
    //NFA.traverse();
    
    NFA_Matcher Matcher(&NFA);

    char input_str_0[] = "asfnsssdajsjdavdavffda";
    length = strlen(input_str_0);

    vector<int> tmp = Matcher.naive_matcher(input_str_0, length);
    cout<<tmp.size()<<endl;

    char input_str_1[] = "fsjdavdavdavdavdavdavdavffffda";
    length = strlen(input_str_1);
    
    tmp = Matcher.naive_matcher(input_str_1, length);
    cout<<tmp.size()<<endl;
    
    return 0;
}