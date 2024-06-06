#include <iostream>

#include "CFG.h"

using std::cout, std::endl;

int main() {

    CFG cfg = CFG();
    
    cfg.add_terminal("a");
    cfg.add_terminal("b");
    cfg.add_terminal("c");

    cfg.add_rule("A", std::vector<std::string>({"a"}));
    cfg.add_rule("B", std::vector<std::string>({"b"}));
    cfg.add_rule("C", std::vector<std::string>({"c"}));

    cfg.add_rule("term", std::vector<std::string>({"A", "B", "C"}));
    cfg.add_rule("ABC", std::vector<std::string>({"term", "term", "|", "none"}));

    cout << cfg << endl;
    return 0;
}