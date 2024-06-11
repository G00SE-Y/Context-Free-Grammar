#ifndef CFG_H
#define CFG_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <regex>

class CFG {

    public:

    CFG();

    bool add_rule(std::string name, std::vector<std::string> products);
    bool add_rule(std::string name, std::string products, std::string delimiter = " ");
    bool set_start_rule(std::string name);
    bool add_terminal(std::string name, std::regex expr);
    bool verify(std::vector<std::string> input);
    std::string to_string() const;


    private:

    enum type_name {
        TERM,
        RULE
    };

    std::string start_rule;

    // the set of rules
    std::unordered_map<std::string, std::vector<std::string>> rules;

    // the set of terminals
    std::unordered_map<std::string, std::regex> terminals;

    // the set of all names of rules or terminals
    std::unordered_map<std::string, int> names;


    typedef struct match_return {
        bool match;
        std::vector<std::string> remainder;
    }match_return;

    std::vector<std::string> parse_rule_string(std::string rule, std::string delimiter);
    match_return verify(std::vector<std::string> input, std::string rule_name); // internal use verify() for recursive validation
    match_return check_match(std::vector<std::string> input, std::vector<std::string> c); // checks if a string matches a rule case
};


std::ostream& operator<<(std::ostream& out, const CFG& data);

#endif