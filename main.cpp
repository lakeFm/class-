#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/*
 * struct for variable
 */
struct var{
    string name,type;
};

void print(const string& data){
    printf("%s\n",data.c_str());
}

vector<var> tokenize(string data);
string constructor(string data,vector<var> vars, int t);
string destructor(string data,vector<var> vars);
string getter(var v,bool isConst);
string setter(var v);

void usage(){
    printf("Usage:\n./class++ [-h/-s] [-c] [class info] [filename]\n");
    printf("\t -h -- header only\n");
    printf("\t -s -- header and source\n");
    printf("\t -c -- print in console\n");
    printf("\t class info -- \'hello(bool var1, ...)\'\n");
    printf("\t filename -- file for save code (without extension)\n");
}
/*
 * example
 * ./class++ -h -c "Ex(int a, char b,string c)"  ex
 *
 * create header only class Ex in file ex.h and print into console
 */

int main(int argc, char **argv ){
   if(argc < 2){
       usage();
   }

    return 0;
}