#include <fstream>
#include "ClassGen.h"

ClassGen::ClassGen(cstr _n,const std::vector<Variable>& _v,bool _m){
    this->name = _n;
    this->vars = _v;
    this->minify = _m;
}

string ClassGen::header(bool h){
    std::stringstream ss;
    ss << "#ifndef " << cap(name) << "_H\n";
    ss << "#define " << cap(name) << "_H\n\n";
    ss << "class " << name << "{\n";
    ss << "private:\n";
    for(Variable _v : vars){
        ss << "\t" << _v.getType() << " " << _v.getName() << ";\n";
    }
    ss << "public:\n\n";
    auto c = new Constructor(vars, false,name);
    for(int a = 0;a < 3;a++){
        h ? ss << c->makeF(a) : ss << c->make(a);
    }
    ss << "\n";

    for(const Variable& v : vars){
        FunGenerator f(v, name,minify,h);
        if(h){
            ss << "\t" << f.setterF();
            ss << "\t" << f.getterF(false);
            ss << "\t" << f.getterF(true) << "\n";
        }else{
            ss << "\t" << f.setter();
            ss << "\t" << f.getter(false);
            ss << "\t" << f.getter(true) << "\n";
        }
    }
    ss << "};\n\n";
    ss << "#endif\n";
    return ss.str();
}


string ClassGen::source(){
    std::stringstream ss;
    ss << "#include <" << name << ".h>\n\n";
    auto c = new Constructor(vars, minify,name);
    for(int a = 0;a < 3;a++){
        ss << c->make(a);
    }
    for(const Variable& v : vars){
        FunGenerator f(v,name,minify,true);
        ss << f.setter();
        ss << f.getter(false);
        ss << f.getter(true) << "\n";
    }
    return ss.str();
}

void ClassGen::toFile(cstr fname,bool h){
    std::ofstream tmp(fname + ".h");
    tmp.clear();
    tmp << header(h) << std::endl;
    tmp.close();
    tmp.open(fname + ".cpp");
    tmp.clear();
    tmp << source() << std::endl;
    tmp.close();
}

string ClassGen::cap(cstr _n){
    string tmp;
    for(char a : _n){
        tmp += (char)std::toupper((int)a);
    }
    return tmp;
}
void ClassGen::setName(cstr _n){
    this->name = _n;
}
void ClassGen::setVars(const std::vector<Variable>& _v){
    this->vars = _v;
}
void ClassGen::setMinify(bool _m){
    this->minify = _m;
}