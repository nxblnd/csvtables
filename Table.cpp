#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include "Table.h"

Table::Table(std::ifstream &input) {
    read_header(input);
    read_body(input);
    find_formulas();
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

bool is_formula(std::string &string) {
    return string[0] == '=';
}

void Table::find_formulas() {
    for (int row = 0; row < body.size(); row++) {
        for (int column = 0; column < body[row].size(); column++) {
            if (is_formula(body[row][column]))
                formula_queue.push(Formula(body[row][column], row, column));
        }
    }
}

std::string Table::get_cell_value(const std::string &cell) {
    std::smatch match;

    std::regex column_pattern("[A-Za-z]+");
    std::regex_search(cell, match, column_pattern);
    int column_id = header_index[match[0]];

    std::regex row_pattern("[0-9]+");
    std::regex_search(cell, match, row_pattern);
    int row_id = body_index[match[0]];

    return body[row_id][column_id];
}

void Table::calculate_formulas() {
    while (!formula_queue.empty()) {
        Formula current = formula_queue.front();
        int arg1, arg2;
        try {
            arg1 = std::stoi(get_cell_value(current.getArg1()));
            arg2 = std::stoi(get_cell_value(current.getArg2()));
        } catch (const std::invalid_argument &e) {
            formula_queue.push(current);
            formula_queue.pop();
            continue;
        }
        int row = current.getRow();
        int column = current.getColumn();
        switch (current.getOp()) {
            case '+':
                body[row][column] = std::to_string(arg1 + arg2);
                break;
            case '-':
                body[row][column] = std::to_string(arg1 - arg2);
                break;
            case '*':
                body[row][column] = std::to_string(arg1 * arg2);
                break;
            case '/':
                body[row][column] = std::to_string(arg1 / arg2);
                break;
            default:
                break;
        }
        formula_queue.pop();
    }
}
