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
    ClassGen(cstr _n,const std::vector<Variable>& _v,bool _m){
        this->name = _n;
        this->vars = _v;
        this->minify = _m;
    }

    string gen(bool h = true){
        std::stringstream ss;

        ss << "#ifndef " << cap(name) << "_H\n";
        ss << "#define " << cap(name) << "_H\n\n";
        ss << "class " << name << "{\n";
        ss << "private:\n";
        for(Variable _v : vars){
            ss << "\t" << _v.getType() << " " << _v.getName() << ";\n";
        }
        ss << "public:\n\n";
        auto c = new Constructor(vars, minify,name);
        for(int a = 0;a < 3;a++){
            ss << c->make(a) << "\n";
        }

        for(const Variable& v : vars){
            FunGenerator f(v);
            ss << f.setter();
            ss << f.getter(false);
            ss << f.getter(true) << "\n";
        }
        ss << "};\n\n";
        ss << "#endif\n";
        return ss.str();
    }

private:
    string cap(cstr _n){
        string tmp;
        for(char a : _n){
            tmp += (char)std::toupper((int)a);
        }
        return tmp;
    }
};

#endif
