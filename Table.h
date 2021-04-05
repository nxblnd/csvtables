#ifndef CSVTABLES_TABLE_H
#define CSVTABLES_TABLE_H


#include <map>
#include <string>
#include <vector>
#include <numeric>
#include <queue>
#include "Formula.h"

struct cell {
    std::string row;
    std::string column;
};

class Table {
private:
    std::vector<std::string> header;
    std::map<std::string, int> header_index;
    std::vector<std::vector<std::string>> body;
    std::map<std::string, int> body_index;
    std::queue<Formula> formula_queue;

    void read_header(std::ifstream &input);
    void read_body(std::ifstream &input);

    int get_column_from_address(const std::string &address);
    int get_row_from_address(const std::string &address);
    std::string get_cell_value(const std::string &cell);
    int eval_argument(std::string &argument);
    int calculate_formula(Formula &formula);
public:
    explicit Table(std::ifstream &input);
    friend std::ostream& operator<<(std::ostream &os, const Table &table);

    void apply_formulas();
};

#endif //CSVTABLES_TABLE_H
