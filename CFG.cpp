#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <sstream>

#include "CFG.h"


//* ---------------- Public Functions ---------------- *//

CFG::CFG() {
    terminals.insert("|");
    terminals.insert("none");
}



bool CFG::add_rule(std::string name, std::vector<std::string> products) {
    
    try {
        rules.at(name);
        return false;
    }
    catch(std::out_of_range& e) {
        rules[name] = products;
        return true;
    }
}



bool CFG::add_terminal(std::string name) {
    
    if(terminals.count(name)) return false;
    
    terminals.insert(name);
    return true;

}



bool CFG::verify(std::string input) {
    return false;
}



std::string CFG::to_string() const{

    std::stringstream ss; 

    ss << "Terminals: ";

    auto itt = terminals.begin();

    while(itt != terminals.end()) {
        ss << *itt << " ";
        itt++;
    }

    ss << "\n\nRules:\n";
    auto itr = rules.begin();
    while(itr != rules.end()) {
        ss << (*itr).first << " -> ";
        for(auto& s: (*itr).second) {
            ss << s << " ";
        }
        ss << "\n";
        itr++;
    }

    return ss.str();
}



std::ostream& operator<<(std::ostream& out, const CFG& data) {
    auto s = data.to_string();
    out << s;
    return out;
}