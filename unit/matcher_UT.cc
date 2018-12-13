#include "../src/matcher.cc"

int main(){
    char regex[]="(asd|fns*daj)*|fsj(dav)*f(fs|da)";
    int length = strlen(regex);
    
    AST ast(regex, length);
    //ast.traverse();
    
    GlushKov_NFA NFA(&ast);
    //NFA.traverse();
    
    NFA_Matcher Matcher(&NFA);

    u8 input_str_0[] = "asfnsssdajsjdavdavffda";
    length = 22;

    vector<int> tmp = Matcher.naive_matcher(input_str_0, length);
    cout<<tmp.size()<<endl;

    u8 input_str_1[] = "fsjdavdavdavdavdavdavdavffffda";
    length = 30;
    
    tmp = Matcher.naive_matcher(input_str_1, length);
    cout<<tmp.size()<<endl;
    
    return 0;
}