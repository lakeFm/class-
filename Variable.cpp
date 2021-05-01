#include "Variable.h"

#include <utility>

Variable::Variable(){
    this->type = "NULL";
    this->name = "NULL";
}

Variable::Variable(std::string t,std::string n){
    this->type = std::move(t);
    this->name = std::move(n);
}
std::string Variable::getType() const{
    return type;
}
std::string Variable::getType(){
    return type;
}
void Variable::setType(std::string mType){
    this->type = mType;
}
std::string Variable::getName() const{
    return name;
}
std::string Variable::getName(){
    return name;
}
void Variable::setName(std::string mName){
    this->name = mName;
}
std::string Variable::up(const std::string& str){
    std::string tmp = str;
    if(tmp[0] > 'a' && tmp[0] < 'z')
        tmp[0] -= 32;
    return tmp;
}
std::string Variable::fun(funType f){
    if(f == GET)
        return  "get" + up(name);
    else
        return  "set" + up(name);
}

std::string Variable::getter(bool isConst){
    std::stringstream ss;
    ss << "\t" << type << " get"<< up(name);
    if(isConst) ss << "() const{\n";
    else ss << "(){\n";
    ss << "\t\t" << " return " << name <<";\n";
    ss << "\t" <<"}\n";
    return ss.str();
}
std::string Variable::getter(const std::string& classname,bool isConst){
    std::stringstream ss;
    ss << "\t" << type << " " << classname  << "::get"<< up(name);
    if(isConst) ss << "() const{\n";
    else ss << "(){\n";
    ss << "\t\t" << " return " << name <<";\n";
    ss << "\t" <<"}\n";
    return ss.str();
}
std::string Variable::getterH(bool isConst){
    std::stringstream ss;
    ss << "\t" << type << " get"<< up(name);
    if(isConst) ss << "() const;\n";
    else ss << "();\n";
    return ss.str();
}

std::string Variable::setter(){
    std::stringstream ss;
    ss << "\t" << "void set"<< up(name) << "(" << type << " m" << up(name) << "){\n";
    ss << "\t\t" << " this->" << name <<" = m" << up(name) <<  ";\n";
    ss << "\t" <<"}\n";
    return ss.str();
}
std::string Variable::setter(const std::string& classname){
    std::stringstream ss;
    ss << "\t" << "void " << classname <<"::set"<< up(name) << "(" << type << " m" << up(name) << "){\n";
    ss << "\t\t" << " this->" << name <<" = m" << up(name) <<  ";\n";
    ss << "\t" <<"}\n";
    return ss.str();
}
std::string Variable::setterH(){
    std::stringstream ss;
    ss << "\t" << "void set"<< up(name) << "(" << type << " m" << up(name) << ");\n";
    return ss.str();
}

std::string Variable::null(){
    if(type == "int" || type == "long" || type == "short") return "0";
    else if(type == "float") return "0.0f";
    else if(type == "double") return "0.0";
    else if(type == "char") return "\'\'";
    else if(type == "string") return "\"\"";
    else return "NULL";
}

std::string Variable::mod(bool full){
    if(full)
        return type + " m" + up(name);
    else
        return "m" + up(name);
}