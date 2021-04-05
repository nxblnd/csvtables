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
    try {
        Table t(input);
        t.apply_formulas();
        std::cout << t << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
