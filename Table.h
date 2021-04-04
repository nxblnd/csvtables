#ifndef CSVTABLES_TABLE_H
#define CSVTABLES_TABLE_H


#include <map>
#include <string>
#include <vector>
#include <numeric>
#include <queue>
#include "Formula.h"

class Table {
private:
    std::vector<std::string> header;
    std::map<std::string, int> header_index;
    std::vector<std::vector<std::string>> body;
    std::map<std::string, int> body_index;
    std::queue<Formula> formula_queue;

    void read_header(std::ifstream &input);
    void read_body(std::ifstream &input);
    void find_formulas();
public:
    explicit Table(std::ifstream &input);
    friend std::ostream& operator<<(std::ostream &os, const Table &table);

    void calculate_formulas();
};

#endif //CSVTABLES_TABLE_H
