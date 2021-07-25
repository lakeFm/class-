#include <ClassGen.h>
#include <iostream>

string parseClass(cstr data){
    return data.substr(0,data.find('('));
}
std::vector<string> split(const char *str, char c = ' '){
    std::vector<string> result;
    do{
        const char *begin = str;
        while(*str != c && *str) str++;
        result.emplace_back(begin, str);
    } while (0 != *str++);
    return result;
}
std::vector<Variable> parseVars(cstr data){
    std::vector<Variable> tmpV;
    int s = (int)data.find('(');
    string tmp = data.substr( s+1,data.size() - s - 2);
    std::vector<string> tokens = split(tmp.c_str(),',');
    for(cstr str : tokens){
        std::vector<string> vTokens = split(str.c_str(),' ');
        Variable tmpVar(vTokens[0],vTokens[1]);
        tmpV.push_back(tmpVar);
    }
    return tmpV;
}
int main(int a,char **b){
    string data;
    if(a < 2){
        char tmp[100];
        printf("Enter class data -> ");
        std::cin.getline(tmp,100);
        data = tmp;
    }else{
        data = b[1];
    }
    string cname = parseClass(data);
    std::vector<Variable> vars = parseVars(data);
    ClassGen cl(cname,vars,true);
    printf("\n");
    printf("%s\n",cl.header().c_str());
    printf("%s\n",cl.source().c_str());
    cl.toFile(cname);
    return 0;
}
