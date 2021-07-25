#include "Variable.h"

Variable::Variable(cstr _t,cstr _n){
    this->setType(_t);
    this->setName(_n);
}

void Variable::setType(cstr t)  { this->type = t; }
void Variable::setName(cstr n)  { this->name = n; }

string Variable::getType()  { return this->type; }
string Variable::getName()  { return this->name; }

string Variable::getType()   const{ return this->type; }
string Variable::getName()   const{ return this->name; }

string Variable::capitalize(){
    string tmp = this->getName();
    tmp[0] = (char)std::toupper((int)tmp[0]);
    return tmp;
}
