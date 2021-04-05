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

    const std::string &get_arg1() const;
    const std::string &get_arg2() const;
    char get_op() const;
    int get_row() const;
    int get_column() const;
};


#endif //CSVTABLES_FORMULA_H
