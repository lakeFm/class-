#include "Constructor.h"

Constructor::Constructor(const std::vector<Variable>& _v,bool _h,cstr _n){
    this->cname = _n;
    this->h = _h;
    this->vars = _v;
}

string Constructor::make(int t){
    std::stringstream ss;
    switch (t) {
        case 0:
            ss << classC(h) << cname << "(){\n";
            for(Variable v : vars){
                ss << "\tthis->" << v.getName()  << " = " << null(v.getType()) << ";\n";
            }
            ss << "}\n";
            break;
        case 1:
            ss << classC(h) << cname << "(";
            for(int a = 0;a < vars.size();a++){
                ss << vars[a].getType()  << " _" << vars[a].getName();
                if (a < vars.size() - 1)
                    ss << ", ";
            }
            ss << "){\n";
            for(Variable v : vars){
                ss << "\tthis->" << v.getName()  << " = _" << v.getName() << ";\n";
            }
            ss << "}\n";
            break;
        case 2:
            ss << classC(h) << cname << "(const " << cname << "& _v" << "){\n";
            for(Variable v : vars){
                ss << "\tthis->" << v.getName()  << " = " << "_v.get" << v.capitalize() << "();\n";
            }
            ss << "}\n";
            break;
        default: break;

    }
    return ss.str();
}
int Constructor::type(cstr _t){
    if(_t == "int") return 0;
    if(_t == "long") return 1;
    if(_t == "float") return 2;
    if(_t == "double") return 3;
    if(_t == "char") return 4;
    return -1;
}
string Constructor::null(cstr t){
    switch(type(t)){
        case 0: case 1:  return "0";
        case 2: return "0.0f";
        case 3: return "0.0";
        case 4: return "' '";
    }
    return "null";
}
string Constructor::classC(bool a){
    if(a)
        return  cname + "::";
    else
        return "";
}