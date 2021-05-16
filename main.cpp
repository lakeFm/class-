#include <iostream>
#include "ClassBuilder.h"

bool header(char h){
    if(h == 'h') return true;
    else return false;
}
bool file(char f){
    if(f == 'f') return true;
    else return false;
}
void usage(){
    printf("Usage : ./class++ -h/s -c/f filename classData \n");
    printf("\t -h/s      \t header only (-h) or header with source (-s) \n");
    printf("\t -c/f      \t print in console or in file \n");
    printf("\t filename  \t name of file to print \n");
    printf("\t classData \t class data Ex: position(float x,float y,float z) \n");
    printf("Example : class++ -h -c 'pos2f(float a,float b)'\n");
}

int main(int a,char **b){
    if(a < 2){
        usage();
    }else{
        char* tmp;
        tmp = b[1];
        bool h = header(tmp[1]);
        tmp = b[2];
        bool f = file(tmp[1]);
        int r = 4;
        if(f){ tmp = b[3]; r = 3;}
        std::string data;
        for(int i = r; i < a;i++){
            data += b[i];
        }

        ClassBuilder builder(data,h);
        if(f){
            builder.toFile(tmp);
        } else{
            builder.print();
        }
    }
    return 0;
}
