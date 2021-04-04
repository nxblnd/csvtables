#include <iostream>
#include <fstream>
#include <string>
#include "Table.h"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "No filename provided" << std::endl;
        return 1;
    }
    std::ifstream input(argv[1]);

    Table t(input);
    t.calculate_formulas();

    std::cout << t << std::endl;

    return 0;
}
