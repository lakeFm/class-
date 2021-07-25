#include "FunGenerator.h"

FunGenerator::FunGenerator(const Variable& _v,cstr _c){
    this->var = _v;
    this->className = _c;
}

string FunGenerator::setter(){
    bool m = var.getMinify();
    std::stringstream ss;
    ss << "void " <<  classC() << "set" << var.capitalize() << "(" << var.getType() << " " << "_"<< var.getName() <<  "){ ";
    if(m) ss << "\n\t";
    ss << "this->" << var.getName() << " = _" << var.getName() << ";";
    if(m) ss << "\n";
    ss << "}\n";
    return ss.str();
}

string FunGenerator::getter(bool isConst){
    bool m = var.getMinify();
    std::stringstream ss;
    ss << var.getType() << " " << classC() << "get" << var.capitalize() << "()" << (isConst ? " const" : "" ) << "{ ";
    if(m) ss << "\n\t";
    ss << "return this->" << var.getName() << ";";
    if(m) ss << "\n";
    ss << "}\n";
    return ss.str();
}

string FunGenerator::setterF(){
    std::stringstream ss;
    ss << "void " <<  classC() << "set" << var.capitalize() << "(" << var.getType() <<  ");\n";
    return ss.str();
}
string FunGenerator::getterF(bool isConst){
    std::stringstream ss;
    ss << var.getType() << " " << classC() << "get" << var.capitalize() << "()" << (isConst ? " const" : "" ) << ";\n";
    return ss.str();
}
string FunGenerator::classC(){
    if(className.length() > 0)
        return  className + "::";
    else
        return "";
}