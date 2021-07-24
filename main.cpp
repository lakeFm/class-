#include "ClassGen.h"

int main(int a,char **b){
    Variable a1("int","a");
    Variable a2("float","f");
    Variable a3("rs::type","custom");
    Variable a4("vector<int>","vec_i");
    std::vector<Variable> vars = {a1,a2,a3,a4};
    string n = "CUSTOM";
    ClassGen c(n,vars,false);
    printf("%s\n",c.gen().c_str());
    return 0;
}
