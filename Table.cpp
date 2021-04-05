#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include "Table.h"

Table::Table(std::ifstream &input) {
    read_header(input);
    read_body(input);
}

std::vector<std::string> split(std::string &string, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(string + ","); // This allows to handle empty cells in the end of the line
    std::string tmp;
    while (std::getline(ss, tmp, delimiter)) {
        result.push_back(tmp);
    }
    return result;
}

void Table::read_header(std::ifstream &input) {
    std::string header_string;
    std::getline(input, header_string);

    header = split(header_string, ',');
    int index = 0;
    for (const auto& title: header) {
        header_index.insert(make_pair(title, index++));
    }
}

void Table::read_body(std::ifstream &input) {
    std::string row;
    while (std::getline(input, row)) {
        body.push_back(split(row, ','));
        body_index.insert(make_pair(body.back()[0], body.size() - 1));
    }
}

std::ostream& operator<<(std::ostream &os, const Table &table){
    for (auto column = table.header.cbegin(); column != table.header.cend() - 1; column++) {
        os << *column << ",";
    }
    os << table.header.back();
    os << std::endl;
    for (const auto& row: table.body) {
        for (auto cell = row.cbegin(); cell != row.cend() - 1; cell++) {
            os << *cell << ",";
        }
        os << row.back();
        os << std::endl;
    }
    return os;
}

bool is_formula(const std::string &string) {
    return string[0] == '=';
}

void Table::apply_formulas() {
    for (int row = 0; row < body.size(); row++) {
        for (int column = 0; column < body[row].size(); column++) {
            if (is_formula(body[row][column])) {
                Formula f(body[row][column], row, column);
                calculate_formula(f);
            }
        }
    }
}

int Table::get_column_from_address(const std::string &address) {
    std::smatch match;
    std::regex column_pattern("[A-Za-z]+");
    std::regex_search(address, match, column_pattern);
    return header_index[match[0]];
}

int Table::get_row_from_address(const std::string &address) {
    std::smatch match;
    std::regex row_pattern("[0-9]+");
    std::regex_search(address, match, row_pattern);
    return body_index[match[0]];
}

std::string Table::get_cell_value(const std::string &cell) {
    int column_id = get_column_from_address(cell);
    int row_id = get_row_from_address(cell);

    return body[row_id][column_id];
}

bool convertible(std::string &string) {
    try {
        std::stoi(string);
        return true;
    } catch (const std::invalid_argument &e) {
        return false;
    }
}

int Table::eval_argument(std::string &argument) {

    if (convertible(argument)) {
        return std::stoi(argument);
    }

    std::string next_cell = get_cell_value(argument);
    if (is_formula(next_cell)) {
        auto formula = get_cell_value(argument);
        Formula f(formula, get_row_from_address(argument), get_column_from_address(argument));
        return calculate_formula(f);
    }
    else if (convertible(next_cell)) {
        return std::stoi(next_cell);
    }
    else {
        throw std::runtime_error("Can't understand this argument: " + argument);
    }
}

int Table::calculate_formula(Formula &formula) {
    auto a1 = formula.getArg1(), a2 = formula.getArg2();
    int arg1 = eval_argument(a1), arg2 = eval_argument(a2);

    int row = formula.getRow(), column = formula.getColumn();
    int answer = 0;
    switch (formula.getOp()) {
        case '+':
            answer = arg1 + arg2;
            break;
        case '-':
            answer = arg1 - arg2;
            break;
        case '*':
            answer = arg1 * arg2;
            break;
        case '/':
            answer = arg1 / arg2;
            break;
        default:
            break;
    }
    body[row][column] = std::to_string(answer);
    return answer;
}
