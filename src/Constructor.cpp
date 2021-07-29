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
            ss << "\t" << classC(h) << cname << "(){\n";
            for(Variable v : vars){
                ss << "\t\tthis->" << v.getName()  << " = " << null(v.getType()) << ";\n";
            }
            ss << "\t}\n";
            break;
        case 1:
            ss << "\t" << classC(h) << cname << "(";
            for(int a = 0;a < vars.size();a++){
                ss << vars[a].getType()  << " _" << vars[a].getName();
                if (a < vars.size() - 1)
                    ss << ", ";
            }
            ss << "){\n";
            for(Variable v : vars){
                ss << "\t\tthis->" << v.getName()  << " = _" << v.getName() << ";\n";
            }
            ss << "\t}\n";
            break;
        case 2:
            ss << "\t" << classC(h) << cname << "(const " << cname << "& _v" << "){\n";
            for(Variable v : vars){
                ss << "\t\tthis->" << v.getName()  << " = " << "_v.get" << v.capitalize() << "();\n";
            }
            ss << "\t}\n";
            break;
        default: break;

    }
    return ss.str();
}
string Constructor::makeF(int t){
    std::stringstream ss;
    switch (t) {
        case 0:
            ss << "\t" << classC(h) << cname << "();\n";
            break;
        case 1:
            ss << "\t" << classC(h) << cname << "(";
            for(int a = 0;a < vars.size();a++){
                ss << vars[a].getType()  << " _" << vars[a].getName();
                if (a < vars.size() - 1)
                    ss << ", ";
            }
            ss << ");\n";
            break;
        case 2:
            ss << "\t" << classC(h) << cname << "(const " << cname << "& _v" << ");\n";
            break;
        default: break;

    }
    return ss.str();
}
string Constructor::null(cstr t){
    if(t == "int")      return "0";
    if(t == "long")     return "0";
    if(t == "float")    return "0.0f";
    if(t == "double")   return "0.0";
    if(t == "char")     return "\'0\'";
    if(t == "string")   return "\"\"";
    return "null";
}
string Constructor::classC(bool a){
    if(a)
        return  cname + "::";
    return "";
}