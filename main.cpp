#include <ClassGen.h>

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
    //printf("Data -> %s\n",tmp.c_str());
    std::vector<string> tokens = split(tmp.c_str(),',');
    for(cstr str : tokens){
        std::vector<string> vTokens = split(str.c_str(),' ');
        Variable tmpVar(vTokens[0],vTokens[1]);
        tmpV.push_back(tmpVar);
    }
    return tmpV;
}
int main(int a,char **b){
    string data = "vec2f(int x,int y,int tmp)";
    string cname = parseClass(data);
    std::vector<Variable> vars = parseVars(data);
    printf("%s",ClassGen(cname,vars,false).gen().c_str());
    return 0;
}
