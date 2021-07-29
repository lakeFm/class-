#ifndef CLASS_CLASSGEN_H
#define CLASS_CLASSGEN_H

#include "Variable.h"
#include "FunGenerator.h"
#include "Constructor.h"

class ClassGen {
private:
    string name;
    std::vector<Variable> vars;
    bool minify = false;
public:
    ClassGen() = default;
    ClassGen(cstr _n,const std::vector<Variable>& _v,bool _m);
    string header(bool);
    string source();
    void toFile(cstr,bool);

    void setName(cstr _n);
    void setVars(const std::vector<Variable>& _v);
    void setMinify(bool);
private:
    string cap(cstr _n);
};

#endif
