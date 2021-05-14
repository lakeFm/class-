#include <fstream>
#include "ClassBuilder.h"

ClassBuilder::ClassBuilder(const std::string& classData,bool onlyH){
    this->build(classData,onlyH);
}


void ClassBuilder::build(const std::string& classData,bool onlyH){
    this->headerOnly = onlyH;
    std::string tmp = classData;
    int a = (int)tmp.find_first_of('(');
    this->className = tmp.substr(0,a);
    tmp = tmp.substr(a+1,(int)tmp.find_first_of(')'));
    tmp[tmp.size() -1] = ',';
    decode(tmp);
}

std::string ClassBuilder::classData(){
    std::stringstream ss;
    ss << "class " << className << "{\n";
    ss << "private: \n";
    for(Variable v : vars){
        ss << "\t" << v.getType() << " " << v.getName() << ";\n";
    }
    ss << "public: \n";
    ss << constructor(false,1) << "\n";
    ss << constructor(false,2) << "\n";
    ss << constructor(false,3) << "\n";

    for(Variable v : vars){
        ss << v.getter(true) << "\n" << v.getter(false) << "\n" << v.setter() << "\n";
    }
    ss << "};\n";
    return ss.str();
}

std::string ClassBuilder::header(){
    std::stringstream ss;
    ss << comment(className + ".h") << "\n";
    ss << "class " << className << "{\n";
    ss << "private: \n";
    for(Variable v : vars)
        ss << "\t" << v.getType() << " " << v.getName() << ";\n";
    ss << "public: \n";

    ss << constructor(true,1);
    ss << constructor(true,2);
    ss << constructor(true,3);

    for(Variable v : vars){
        ss << v.getterH(true) << v.getterH(false) << v.setterH();
    }
    ss << "};\n";

    return ss.str();
}

std::string ClassBuilder::source(){
    std::stringstream ss;
    ss << comment(className + ".cpp") << "\n";
    ss << includeFile(className) << "\n";
    ss << '\t' << className << "::" <<constructor(false,1);
    ss << '\t' << className << "::" <<constructor(false,2);
    ss << '\t' << className << "::" <<constructor(false,3);

    for(Variable v : vars){
        ss << v.getter(className,true) << v.getter(className, false) << v.setter(className);
    }

    return ss.str();
}

std::string ClassBuilder::includeFile(const std::string& name){
    return "#include <" + name + ".h>\n";
}

std::string ClassBuilder::comment(const std::string& filename){
    std::stringstream ss;
    ss << "// ---------------------------" << "\n" ;
    ss << "// " << filename << "\n" ;
    ss << "// ---------------------------" << "\n" ;
    return ss.str();
}

void ClassBuilder::print(){
    if(headerOnly)
        printf("%s\n",classData().c_str());
    else
        printf("%s\n",(header()+"\n\n\n"+source()).c_str());
}

void ClassBuilder::decode(std::string s){
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(',')) != std::string::npos) {
        token = s.substr(0, pos);
        vars.push_back(toVar(token));
        s.erase(0, pos + 1);
    }
}

Variable ClassBuilder::toVar(const std::string& s){
    int q = (int)s.find(' ');
    return Variable(s.substr(0,q),s.substr(q+1,s.size()));
}

std::string ClassBuilder::constructor(bool h,int type){
    std::stringstream ss;
    if(!h) {
        switch (type) {
            case 1:
                ss << className << "(){\n";
                for (Variable v : vars) {
                    ss << "\t\tthis->" << v.getName() << " = " << v.null() << ";\n";
                }
                ss << "\t}\n";
                break;
            case 2:
                ss << className << "(";
                for (int a = 0; a < vars.size(); a++) {
                    if (a == vars.size() - 1)ss << vars[a].mod(true);
                    else ss << vars[a].mod(true) << ",";
                }
                ss << "){\n";
                for (Variable v : vars) {
                    ss << "\t\tthis->" << v.getName() << " = " << v.mod(false) << ";\n";
                }
                ss << "\t}\n";
                break;
            case 3:
                ss << className << "(" << className << " &oth){\n";
                for (Variable v : vars) {
                    ss << "\t\tthis->" << v.getName() << " = oth." << v.fun(GET) << "();\n";
                }
                ss << "\t}\n";

                break;
        }
    }else{
        switch (type) {
            case 1:
                ss << '\t' << className << "();\n";
                break;
            case 2:
                ss << '\t' << className << "(";
                for (int a = 0; a < vars.size(); a++) {
                    if (a == vars.size() - 1)ss << vars[a].mod(true);
                    else ss << vars[a].mod(true) << ",";
                }
                ss << ");\n";
                break;
            case 3:
                ss << '\t' << className << "(" << className << " &oth);\n";
                break;
        }
    }
    return ss.str();
}


void ClassBuilder::toFile(const std::string& filename){
    if(headerOnly) {
        std::ofstream f(filename + ".h");
        f << classData() << "\n";
        f.close();
    }else{
        std::ofstream f;
        f.open(filename + ".h");
        f << header() << "\n";
        f.close();
        f.open(filename + ".cpp");
        f << source() << "\n";
        f.close();

    }
}