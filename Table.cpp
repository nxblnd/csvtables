#include <fstream>
#include <sstream>
#include <iostream>
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
}

void Table::read_body(std::ifstream &input) {
    std::string row;
    while (std::getline(input, row)) {
        body.push_back(split(row, ','));
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
    for (const auto& row: body) {
        for (auto cell: row) {
            if (is_formula(cell))
                formula_queue.push(Formula(cell));
        }
    }
}

void Table::calculate_formulas() {
    while (!formula_queue.empty()) {
        ;
    }
}
