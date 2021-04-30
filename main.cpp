#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

enum funType{
    GET,SET
};

class Variable{
private:
    std::string type;
    std::string name;
public:
    Variable(){
        this->name = "NULL";
        this->type = "NULL";
    }
    Variable(const std::string& t,const std::string& n){
        this->name = n;
        this->type = t;
    }

    std::string getName(){return this->name;}
    std::string getType(){return this->type;}
    std::string fun(funType f){
        if(f == GET)
            return  "get" + up(name);
        else
            return  "set" + up(name);
    }

    std::string getter(bool isConst){
        std::stringstream ss;
        ss << "\t" << type << " get"<< up(name);
        if(isConst) ss << "() const{\n";
        else ss << "(){\n";
        ss << "\t\t" << " return " << name <<";\n";
        ss << "\t" <<"}\n";
        return ss.str();
    }
    std::string getter(const std::string& classname,bool isConst){
        std::stringstream ss;
        ss << "\t" << type << " " << classname  << "::get"<< up(name);
        if(isConst) ss << "() const{\n";
        else ss << "(){\n";
        ss << "\t\t" << " return " << name <<";\n";
        ss << "\t" <<"}\n";
        return ss.str();
    }
    std::string getterH(bool isConst){
        std::stringstream ss;
        ss << "\t" << type << " get"<< up(name);
        if(isConst) ss << "() const;\n";
        else ss << "();\n";
        return ss.str();
    }

    std::string setter(){
        std::stringstream ss;
        ss << "\t" << "void set"<< up(name) << "(" << type << " m" << up(name) << "){\n";
        ss << "\t\t" << " this->" << name <<" = m" << up(name) <<  ";\n";
        ss << "\t" <<"}\n";
        return ss.str();
    }
    std::string setter(const std::string& classname){
        std::stringstream ss;
        ss << "\t" << "void " << classname <<"::set"<< up(name) << "(" << type << " m" << up(name) << "){\n";
        ss << "\t\t" << " this->" << name <<" = m" << up(name) <<  ";\n";
        ss << "\t" <<"}\n";
        return ss.str();
    }
    std::string setterH(){
        std::stringstream ss;
        ss << "\t" << "void set"<< up(name) << "(" << type << " m" << up(name) << ");\n";
        return ss.str();
    }

    std::string null(){
        if(type == "int" || type == "long" || type == "short") return "0";
        else if(type == "float") return "0.0f";
        else if(type == "double") return "0.0";
        else if(type == "char") return "\'\'";
        else if(type == "string") return "\"\"";
        else return "NULL";
    }

    std::string mod(bool full){
        if(full)
            return type + " m" + up(name);
        else
            return "m" + up(name);
    }

private:
    static std::string up(const std::string& str){
        std::string tmp = str;
        if(tmp[0] > 'a' && tmp[0] < 'z')
            tmp[0] -= 32;
        return tmp;
    }
};

class ClassBuilder{
private:
    std::string className;
    std::vector<Variable> vars;
    bool headerOnly;
public:
    ClassBuilder(const std::string& classData,bool onlyH){
        this->headerOnly = onlyH;
        std::string tmp = classData;
        int a = (int)tmp.find_first_of('(');
        this->className = tmp.substr(0,a);
        tmp = tmp.substr(a+1,(int)tmp.find_first_of(')'));
        tmp[tmp.size() -1] = ',';
        decode(tmp);
    }

    std::string classData(){
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
        ss << "}\n";
        return ss.str();
    }

    std::string header(){
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
        ss << "}\n";

        return ss.str();
    }

    std::string source(){
        std::stringstream ss;
        ss << comment(className + ".cpp") << "\n";
        ss << includeFile(className) << "\n";
        ss << '\t' << className << "::" <<constructor(false,1);
        ss << '\t' << className << "::" <<constructor(false,2);
        ss << '\t' << className << "::" <<constructor(false,3);

        for(Variable v : vars){
            ss << v.getter(className,true) << v.getter(className, false) << v.setter(className);
        }
        ss << "}\n";

        return ss.str();
    }



    static std::string includeFile(const std::string& name){
        return "#include <" + name + ".h>\n";
    }

    static std::string comment(const std::string& filename){
        std::stringstream ss;
        ss << "// ---------------------------" << "\n" ;
        ss << "// " << filename << "\n" ;
        ss << "// ---------------------------" << "\n" ;
        return ss.str();
    }

    void print(){
        if(headerOnly)
            printf("%s\n",classData().c_str());
        else
            printf("%s\n",(header()+"\n\n\n"+source()).c_str());
    }

private:
    void decode(std::string s){
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(',')) != std::string::npos) {
            token = s.substr(0, pos);
            vars.push_back(toVar(token));
            s.erase(0, pos + 1);
        }
    }

    static Variable toVar(const std::string& s){
        int q = (int)s.find(' ');
        return Variable(s.substr(0,q),s.substr(q+1,s.size()));
    }

    std::string constructor(bool h,int type){
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

};

int main(){
    // player(vec3f position,int id,long socket,array<Item> inventory)
    char data[100]; std::cin.getline(data,100);
    ClassBuilder builder((std::string(data)), true);
    builder.print();
    return 0;
}
