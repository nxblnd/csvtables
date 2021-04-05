#include <fstream>
#include <iostream>
#include <regex>
#include "Table.h"

Table::Table(std::ifstream &input) {
    read_header(input);
    read_body(input);
}

std::vector<std::string> Table::split(std::string &string, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(string + delimiter); // This allows to handle empty cells in the end of the line
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

    if (!std::all_of(header.begin() + 1, header.end(), [](std::string &title){
        return std::regex_match(title, std::regex("[A-Za-z]+"));
    })) {
        throw std::runtime_error("Malformed header line");
    }

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

        if (!std::regex_match(body.back()[0], std::regex("\\d+"))) {
            throw std::runtime_error("Malformed row number");
        }
    }

    if (!std::all_of(body.begin(), body.end(), [this](std::vector<std::string> &row){
        return row.size() == body[0].size();
    }) || header.size() != body[0].size()) {
        throw std::runtime_error("Not all rows have same size");
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

bool Table::is_formula(const std::string &string) {
    return string[0] == '=';
}

bool Table::is_address(const std::string &string) {
    std::regex address_pattern(R"([A-Za-z]+\d+)");
    return std::regex_match(string, address_pattern);
}

void Table::apply_formulas() {
    for (int row = 0; row < body.size(); row++) {
        for (int column = 0; column < body[row].size(); column++) {
            if (is_formula(body[row][column]))
                calculate_formula(Formula(body[row][column], row, column));
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

bool Table::convertible(const std::string &string) {
    try {
        std::stoi(string);
        return true;
    } catch (const std::invalid_argument &e) {
        return false;
    }
}

int Table::eval_argument(const std::string &argument) {
    if (convertible(argument)) {
        return std::stoi(argument);
    }
    else if (is_formula(argument)) {
        return calculate_formula(Formula(argument,
                                         get_row_from_address(argument),
                                         get_column_from_address(argument)));
    }
    else if (is_address(argument)) {
        return eval_argument(get_cell_value(argument));
    }
    else {
        throw std::runtime_error("Can't understand this argument: \"" + argument + "\"");
    }
}

int Table::calculate_formula(const Formula &formula) {
    std::string address = header[formula.get_column()] + body[formula.get_row()][0];
    if (!current_formulas.insert(address).second) {
        throw std::runtime_error("Cyclic formulas detected");
    }

    int arg1 = eval_argument(formula.get_arg1());
    int arg2 = eval_argument(formula.get_arg2());
    int answer = 0;

    switch (formula.get_op()) {
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
            if (arg2 == 0)
                throw std::runtime_error("Division by zero occurred");
            answer = arg1 / arg2;
            break;
        default:
            break;
    }

    body[formula.get_row()][formula.get_column()] = std::to_string(answer);
    current_formulas.erase(address);
    return answer;
}
