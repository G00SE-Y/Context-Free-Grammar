#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <regex>

#include "CFG.h"


//* ---------------- Public Functions ---------------- *//

bool CFG::verify(std::vector<std::string> input) {
    
    if(names.count(start_rule) == 0) {
        std::cout << "No start rule given\n";
        return false;
    }
    

    match_return ret = verify(input, start_rule);

    if(ret.match && ret.remainder.size() == 0) return true;

    return false;
}



CFG::CFG() {
    terminals.insert({"|", std::regex("[|]")});
    names["|"] = CFG::TERM;

    terminals.insert({"none", std::regex("none")});
    names["none"] = CFG::TERM;
}



bool CFG::add_rule(std::string name, std::vector<std::string> products) {
    
    if(names.count(name)) return false;

    names[name] = CFG::RULE;
    rules[name] = products;
    return true;

}



bool CFG::add_terminal(std::string name, std::regex expr) {
    
    if(names.count(name)) return false;

    names[name] = CFG::TERM;    
    terminals.insert({name, expr});

    return true;

}



bool CFG::set_start_rule(std::string name) {

    if(rules.size() && rules.count(name)) start_rule = name;
    else return false;

    return true;
}



std::string CFG::to_string() const{

    std::stringstream ss; 

    ss << "Terminals:\n";

    auto itt = terminals.begin();

    while(itt != terminals.end()) {
        if((*itt).first == "\n") ss << "\\n\n";
        else ss << (*itt).first << "\n";
        itt++;
    }

    ss << "\nRules:\n";
    auto itr = rules.begin();
    while(itr != rules.end()) {
        ss << (*itr).first << " -> ";
        for(auto& s: (*itr).second) {
            if(s == "\n") ss << "\\n ";
            else ss << s << " ";
        }
        ss << "\n";
        itr++;
    }

    ss << "\nStart Rule: \"" << start_rule << "\"\n";

    return ss.str();
}



std::ostream& operator<<(std::ostream& out, const CFG& data) {
    auto s = data.to_string();
    out << s;
    return out;
}



//* ---------------- Private Functions ---------------- *//

CFG::match_return CFG::verify(std::vector<std::string> input, std::string rule_name) {

    std::vector<std::vector<std::string>> cases;

    if(std::find(rules[rule_name].begin(), rules[rule_name].end(), "|") != rules[rule_name].end()) {
        // spearate out different cases by "|"
        auto input_it = rules[rule_name].begin();
        std::vector<std::string> current_case;
        
        while(input_it != rules[rule_name].end()) {

            if(*input_it == "|") { 
                cases.push_back(current_case);
                current_case.clear();
            }
            else {
                current_case.push_back(*input_it);
            }

            input_it++;
        }
        if(current_case.size()) cases.push_back(current_case);
    }
    else {
        // insert whole rule as a case
        cases.push_back(rules[rule_name]);
    }

    match_return ret;

    for(auto& c: cases) {
        
        ret = check_match(input, c);
        
        if(ret.match) return ret;
    }

    ret.match = false;
    return ret;
}



CFG::match_return CFG::check_match(std::vector<std::string> input, std::vector<std::string> c) {

    match_return ret;

    if(c.size() == 1 && c[0] == "none") { // if matching for nothing, always match
        ret.match = true;
        ret.remainder = input;
        return ret;
    }
    else if(input.size() == 0) { // if the input token vector is empty, and the case isn't 'none', return a non-match
        ret.match = false;
        return ret;
    }

    for(auto elem: c) {
        
        if(names[elem] == CFG::TERM) {

            if(input.size() > 0 && std::regex_match(input[0], terminals[elem])) { // matched a terminal, consume that terminal from the input 

                input.erase(input.begin());
            }
            else { // failed to match, return

                ret.match = false;
                return ret;
            }
        }
        else {
            
            match_return m = verify(input, elem);
            
            if(!m.match) {

                ret.match = false;
                return ret;
            }

            input = m.remainder;
        }
    }

    ret.match = true;
    ret.remainder = input;

    return ret;
}