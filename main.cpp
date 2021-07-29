#include <ClassGen.h>
#include <iostream>
#include <cstring>
#include <ClassParser.h>

bool getAns(char a){
    if(a == 'y' || a == 'Y')
        return true;
    else
        return false;
}

void manual(){
    char tmp[100];
    printf("Enter class data -> ");
    std::cin.getline(tmp,100);
    std::string data = tmp;
    ClassParser p(data);
    bool header,file;
    char t;
    printf("Header-only (y/Y/n/N): "); std::cin >> t; header = !getAns(t);
    printf("Print in console (y/Y/n/N): "); std::cin >> t; file = !getAns(t);
    if(file){
        printf("Enter filename : "); std::cin >> data;
    }
    ClassGen cg;
    cg.setName(p.getName());
    cg.setVars(p.getVars());
    if(file){
        cg.toFile(data,header);
    }else{
        printf("\n%s\n",cg.header(header).c_str());
        if(header) printf("%s\n",cg.source().c_str());
    }
}

void argParser(int a,char** b){
    ClassGen cg;
    bool header,file;
    char* tmp = b[1];
    for(int i = 0; i < std::strlen(tmp);i++){
        if(tmp[i] == 'h') header = true;
        if(tmp[i] == 's') header = false;
        if(tmp[i] == 'c') file   = true;
        if(tmp[i] == 'f') file   = false;
    }
    if(file)
        tmp = b[2];
    else
        tmp = b[3];
    ClassParser p(tmp);
    cg.setName(p.getName());
    cg.setVars(p.getVars());
    if(!file){
        tmp = b[2];
        cg.toFile(tmp,!header);
    }else{
        printf("%s\n",cg.header(!header).c_str());
        if(!header) printf("%s\n",cg.source().c_str());
    }
}

int main(int a,char **b){
    a < 2 ? manual() : argParser(a,b);
    return 0;
}
