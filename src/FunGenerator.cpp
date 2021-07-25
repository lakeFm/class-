#include "FunGenerator.h"

FunGenerator::FunGenerator(const Variable& _v,cstr _c,bool _m,bool _h){
    this->var = _v;
    this->className = _c;
    this->m = _m;
    this->h = _h;
}
string FunGenerator::setter(){
    std::stringstream ss;
    ss << "void " <<  classC() << "set" << var.capitalize() << "(" << var.getType() << " " << "_"<< var.getName() <<  "){ ";
    if(m) ss << "\n\t";
    ss << "this->" << var.getName() << " = _" << var.getName() << ";";
    if(m) ss << "\n";
    ss << "}\n";
    return ss.str();
}
string FunGenerator::getter(bool isConst){
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
    if(h)
        return  className + "::";
    else
        return "";
}