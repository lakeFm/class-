#ifndef CLASS_VARIABLE_H
#define CLASS_VARIABLE_H

#include <string>

using std::string;
typedef const string& cstr;

class Variable {
private:
    string type,name;
public:
    Variable() = default;
    Variable(cstr _t,cstr _n);

    void setType(cstr t);
    void setName(cstr n);

    string getType();
    string getName();

    string getType() const;
    string getName() const;

    string capitalize();

};

#endif