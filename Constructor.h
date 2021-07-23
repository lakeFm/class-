#ifndef CLASS_CONSTRUCTOR_H
#define CLASS_CONSTRUCTOR_H

#include <vector>
#include <sstream>
#include "Variable.h"

class Constructor {
private:
    std::vector<Variable> vars;
    string cname;
public:
    explicit Constructor(const std::vector<Variable>& _v,cstr _n = ""){
        this->cname = _n;
        this->vars = _v;
    }

    string make(int t){
        std::stringstream ss;
        //TODO constructor make(type)
        return ss.str();
    }

private:
    string classC(){
        if(cname.length() > 0)
            return  cname + "::";
        else
            return "";
    }
};


#endif
