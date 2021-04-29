#include <cstdio>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

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
    std::string getterFun(){
        return  "get" + up(name);
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

    std::string setter(){
        std::stringstream ss;
        ss << "\t" << "void set"<< up(name) << "(" << type << " m" << up(name) << "){\n";
        ss << "\t\t" << " this->" << name <<" = m" << up(name) <<  ";\n";
        ss << "\t" <<"}\n";
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
        std::string tmp = name;
        if(tmp[0] > 'a' && tmp[0] < 'z')
            tmp[0] -= 32;
        if(full)
            return type + " m" +tmp;
        else
            return "m" + tmp;
    }

private:
    std::string up(const std::string& str){
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
public:
    ClassBuilder(const std::string& classData){
        std::string tmp = classData;
        int a = (int)tmp.find_first_of('(');
        this->className = tmp.substr(0,a);
        tmp = tmp.substr(a+1,tmp.size()-1);
        tmp += ',';
        decode(tmp);
    }

    std::string classData(){
        std::stringstream ss;
        ss << "class " << className << "{\n";
        ss << "private: \n";
        for(Variable v : vars){
            ss << v.getType() << " " << v.getName() << ";\n";
        }
        ss << "public: \n";
        ss << constructor(1) << "\n";
        ss << constructor(2) << "\n";
        ss << constructor(3) << "\n";

        for(Variable v : vars){
            ss << v.getter(true) << "\n" << v.getter(false) << "\n" << v.setter() << "\n";
        }
        ss << "}\n";
        return ss.str();
    }

    void print(){
        printf("%s\n",classData().c_str());
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

    std::string constructor(int type){
        std::stringstream ss;

        switch (type) {
            case 1: //default
                ss << '\t' << className <<"(){\n";
                for(Variable v : vars){
                    ss << "\t\tthis->" << v.getName() << " = " << v.null() <<";\n";
                }
                ss << "\t}\n";
                break;
            case 2:
                ss << '\t' << className <<"(";
                for(int a = 0;a < vars.size();a++){
                    if(a == vars.size() -1 )ss << vars[a].mod(true);
                    else ss << vars[a].mod(true) << ",";
                }
                ss << "){\n";
                for(Variable v : vars){
                    ss << "\t\tthis->" << v.getName() << " = " << v.mod(false) <<";\n";
                }
                ss << "\t}\n";
                break;
            case 3:
                ss << '\t' << className <<"("<< className <<" &oth){\n";
                for(Variable v : vars){
                    ss << "\t\tthis->" << v.getName() << " = oth." << v.getterFun() <<"();\n";
                }
                ss << "\t}\n";

                break;
            default: break;
        }
        return ss.str();
    }

};

int main(){
    char data[100]; std::cin.getline(data,100);
    ClassBuilder builder((std::string(data)));
    builder.print();
    return 0;
}