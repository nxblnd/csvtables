#ifndef CSVTABLES_TABLE_H
#define CSVTABLES_TABLE_H


#include <map>
#include <string>
#include <vector>
#include <numeric>
#include <queue>

struct formula {
    int row;
    int column;
    std::string formula;
};

class Table {
private:
    std::vector<std::string> header;
    std::vector<std::vector<std::string>> body;
    std::queue<formula> formula_queue;

    void read_header(std::ifstream &input);
    void read_body(std::ifstream &input);
    void find_formulas();
public:
    explicit Table(std::ifstream &input);
    friend std::ostream& operator<<(std::ostream &os, const Table &table);
};

#endif //CSVTABLES_TABLE_H
