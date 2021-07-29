#ifndef CLASS_CLASSPARSER_H
#define CLASS_CLASSPARSER_H

#include "ClassGen.h"

class ClassParser{
private:
    std::string name;
    std::vector<Variable> vars;
public:
    explicit ClassParser(const std::string& data);
    std::string getName();
    std::vector<Variable> getVars();

private:
    string parseClass(cstr data);
    std::vector<string> split(const char *str, char c = ' ');
    std::vector<Variable> parseVars(cstr data);
};

#endif
