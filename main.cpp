#include "FunGenerator.h"

int main(int a,char **b){
    Variable t("int","a",true);
    string c = "vec2";
    printf("%s\n", FunGenerator(t,c).setter().c_str());
    printf("%s\n", FunGenerator(t,c).getter(true).c_str());
    printf("%s\n", FunGenerator(t,c).getter(false).c_str());
    return 0;
}
