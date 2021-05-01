#ifndef CLASS_CLASSBUILDER_H
#define CLASS_CLASSBUILDER_H

#include "Variable.h"
#include <vector>

class ClassBuilder{
private:
    std::string className;
    std::vector<Variable> vars;
    bool headerOnly;
public:
    ClassBuilder(const std::string& classData,bool onlyH);

    std::string classData();
    std::string header();
    std::string source();
    static std::string includeFile(const std::string& name);
    static std::string comment(const std::string& filename);
    void print();

private:
    void decode(std::string s);
    static Variable toVar(const std::string& s);
    std::string constructor(bool h,int type);
};

#endif //CLASS_CLASSBUILDER_H
