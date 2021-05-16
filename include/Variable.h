#ifndef CLASS_VARIABLE_H
#define CLASS_VARIABLE_H

#include <string>
#include <sstream>

enum funType{
    GET,SET
};

class Variable{
private:
    std::string type;
    std::string name;
public:
    Variable();
    Variable(std::string t,std::string n);
    std::string getType() const;
    std::string getType();
    void setType(std::string mType);
    std::string getName() const;
    std::string getName();
    void setName(std::string mName);
    static std::string up(const std::string& str);
    std::string fun(funType f);
    std::string getter(bool isConst);
    std::string getter(const std::string& classname,bool isConst);
    std::string getterH(bool isConst);
    std::string setter();
    std::string setter(const std::string& classname);
    std::string setterH();
    std::string null();
    std::string mod(bool full);
};

#endif //CLASS_VARIABLE_H
