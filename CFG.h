#ifndef CFG_H
#define CFG_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>

class CFG {

    public:

    CFG();

    bool add_rule(std::string name, std::vector<std::string> products);
    bool add_terminal(std::string name);
    bool verify(std::string input);
    std::string to_string() const;


    private:

    // the set of rules
    std::unordered_map<std::string, std::vector<std::string>> rules;
    std::unordered_set<std::string> terminals;
};


std::ostream& operator<<(std::ostream& out, const CFG& data);

#endif