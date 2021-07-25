#ifndef CLASS_CLASSGEN_H
#define CLASS_CLASSGEN_H

#include "Variable.h"
#include "FunGenerator.h"
#include "Constructor.h"

class ClassGen {
private:
    string name;
    std::vector<Variable> vars;
    bool minify;
public:
    ClassGen(cstr _n,const std::vector<Variable>& _v,bool _m);
    string gen(bool h = true);
private:
    string cap(cstr _n);
};

#endif
