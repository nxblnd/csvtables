#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> split(std::string &string, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(string);
    std::string tmp;
    while (std::getline(ss, tmp, delimiter)) {
        result.push_back(tmp);
    }
    return result;
}

std::map<std::string, int> get_header(std::ifstream &input) {
    std::string header;
    std::getline(input, header);

    std::map<std::string, int> result;
    int index = 0;
    for (const std::string& title: split(header, ',')) {
        result.insert(std::make_pair(title, index++));
    }
    return result;
}

std::vector<std::vector<std::string>> get_table(std::ifstream &input) {
    std::string row;
    std::vector<std::vector<std::string>> result;
    while (std::getline(input, row)) {
        result.push_back(split(row, ','));
    }
    return result;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "No filename provided" << std::endl;
        return 1;
    }
    std::ifstream input(argv[1]);

    return 0;
}
