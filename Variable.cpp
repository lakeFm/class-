#include "Variable.h"

Variable::Variable(cstr _t,cstr _n){
    this->setType(_t);
    this->setName(_n);
    this->setMinify(false);
}
Variable::Variable(cstr _t,cstr _n,bool _m){
    this->setType(_t);
    this->setName(_n);
    this->setMinify(_m);
}

void Variable::setType(cstr t)  { this->type = t; }
void Variable::setName(cstr n)  { this->name = n; }
void Variable::setMinify(bool m){ this->minify = m; }

string Variable::getType()  { return this->type; }
string Variable::getName()  { return this->name; }
bool   Variable::getMinify(){ return this->minify; }

string Variable::getType()   const{ return this->type; }
string Variable::getName()   const{ return this->name; }
bool   Variable::getMinify() const{ return this->minify; }
