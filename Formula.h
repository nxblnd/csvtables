#ifndef CSVTABLES_FORMULA_H
#define CSVTABLES_FORMULA_H


#include <string>

class Formula {
private:
    std::string arg1;
    std::string arg2;
    char op;
    int row;
    int column;
public:
    explicit Formula(const std::string &string, int row, int column);

    const std::string &getArg1() const;
    const std::string &getArg2() const;
    char getOp() const;
    int getRow() const;
    int getColumn() const;
};


#endif //CSVTABLES_FORMULA_H
