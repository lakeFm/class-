#ifndef CLASS_FUNGENERATOR_H
#define CLASS_FUNGENERATOR_H

#include "Variable.h"
#include <sstream>
#include <cctype>

class FunGenerator {
private:
    Variable var;
    string className;
public:
    explicit FunGenerator(const Variable& _v,cstr _c = ""){
        this->var = _v;
        this->className = _c;
    }

    string setter(){
        bool m = var.getMinify();
        std::stringstream ss;
        ss << "void " <<  classC() << "set" << capitalizeName() << "(" << var.getType() << " " << "_"<< var.getName() <<  "){ ";
        if(m) ss << "\n\t";
        ss << "this->" << var.getName() << " = _" << var.getName() << ";";
        if(m) ss << "\n";
        ss << "}\n";
        return ss.str();
    }

    string getter(bool isConst){
        bool m = var.getMinify();
        std::stringstream ss;
        ss << var.getType() << " " << classC() << "get" << capitalizeName() << "()" << (isConst ? " const" : "" ) << "{ ";
        if(m) ss << "\n\t";
        ss << "return this->" << var.getName() << ";";
        if(m) ss << "\n";
        ss << "}\n";
        return ss.str();

    }

private:
    string capitalizeName(){
        string tmp = var.getName();
        tmp[0] = (char)std::toupper((int)tmp[0]);
        return tmp;
    }
    string classC(){
        if(className.length() > 0)
            return  className + "::";
        else
            return "";
    }
};


#endif
