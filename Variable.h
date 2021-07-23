#ifndef CLASS_VARIABLE_H
#define CLASS_VARIABLE_H

#include <string>

using std::string;
typedef const string& cstr;

class Variable {
private:
    string type,name;
    bool minify;
public:
    Variable() = default;
    Variable(cstr _t,cstr _n);
    Variable(cstr _t,cstr _n,bool _m);

    void setType(cstr t);
    void setName(cstr n);
    void setMinify(bool m);

    string getType();
    string getName();
    bool   getMinify();

    string getType() const;
    string getName() const;
    bool   getMinify() const;

};

#endif