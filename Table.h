#ifndef CSVTABLES_TABLE_H
#define CSVTABLES_TABLE_H


#include <map>
#include <string>
#include <vector>

class Table {
private:
    std::map<std::string, int> header;
    std::vector<std::vector<std::string>> body;

    void read_header(std::ifstream &input);
    void read_body(std::ifstream &input);
public:
    explicit Table(std::ifstream &input);
};


#endif //CSVTABLES_TABLE_H
