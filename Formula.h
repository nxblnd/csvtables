#ifndef CSVTABLES_FORMULA_H
#define CSVTABLES_FORMULA_H


#include <string>

class Formula {
private:
    std::string arg1, arg2;
    char op;
public:
    explicit Formula(std::string &string);
};


#endif //CSVTABLES_FORMULA_H
