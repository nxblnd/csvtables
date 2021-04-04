#include <regex>
#include "Formula.h"

Formula::Formula(std::string &string, int row, int column) {
    this->row = row;
    this->column = column;

    std::regex validation_pattern(R"(=\s*([A-Za-z]+[0-9]+)\s*([\+\-\*\\])\s*([A-Za-z]+[0-9]+)\s*)");
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
