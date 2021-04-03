#include <fstream>
#include <sstream>
#include "Table.h"

Table::Table(std::ifstream &input) {
    read_header(input);
    read_body(input);
}

std::vector<std::string> split(std::string &string, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(string);
    std::string tmp;
    while (std::getline(ss, tmp, delimiter)) {
        result.push_back(tmp);
    }
    return result;
}

void Table::read_header(std::ifstream &input) {
    std::string header_string;
    std::getline(input, header_string);

    int index = 0;
    for (const std::string& title: split(header_string, ',')) {
        header.insert(std::make_pair(title, index++));
    }
}

void Table::read_body(std::ifstream &input) {
    std::string row;
    while (std::getline(input, row)) {
        body.push_back(split(row, ','));
    }
}