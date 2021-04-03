#ifndef CSVTABLES_TABLE_H
#define CSVTABLES_TABLE_H


#include <map>
#include <string>
#include <vector>

class Table {
private:
    std::vector<std::string> header;
    std::vector<std::vector<std::string>> body;

    void read_header(std::ifstream &input);
    void read_body(std::ifstream &input);
public:
    explicit Table(std::ifstream &input);

    void print();
};


#endif //CSVTABLES_TABLE_H
