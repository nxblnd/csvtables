#include <regex>
#include "Formula.h"

Formula::Formula(std::string &string, int row, int column) {
    this->row = row;
    this->column = column;

    std::regex validation_pattern(R"(=\s*([A-Za-z]+\d+|\d+)\s*([\+\-\*\\])\s*([A-Za-z]+\d+|\d+)\s*)");
    if (!std::regex_match(string, validation_pattern)) {
        throw std::runtime_error("Formula \"" + string + "\" is invalid");
    }

    std::regex arg_pattern("[A-Za-z]+[0-9]+");
    std::sregex_iterator args(string.begin(), string.end(), arg_pattern);
    arg1 = args++->str();
    arg2 = args->str();

    std::regex op_pattern(R"([\+\-\*\\])");
    std::smatch operation;
    std::regex_search(string, operation, op_pattern);
    op = std::string(operation[0])[0];
}

const std::string &Formula::getArg1() const {
    return arg1;
}

const std::string &Formula::getArg2() const {
    return arg2;
}

char Formula::getOp() const {
    return op;
}

int Formula::getRow() const {
    return row;
}

int Formula::getColumn() const {
    return column;
}
