#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

#include "CFG.h"

using std::cout, std::endl;

int main() {

    CFG cfg = CFG();
    
    cfg.add_terminal("a", std::regex("^a$"));
    cfg.add_terminal("b", std::regex("^b$"));
    cfg.add_terminal("c", std::regex("^c$"));

    cfg.add_rule("A", "a");
    cfg.add_rule("B", "b");
    cfg.add_rule("C", "c");

    
    cfg.add_rule("ABC", "A B C");
    cfg.add_rule("[ABC]", "A | B | C");
    cfg.add_rule("ABC+", "ABC ABC+ | none");

    cfg.add_rule("LANGUAGE", "[ABC] ABC+");

    cfg.set_start_rule("LANGUAGE");

    std::vector<std::string> input1 ({
        "c",
        "a",
        "b",
        "c",
        "a",
        "b",
        "c"
    });

    std::vector<std::string> input2 ({
        "a",
        "a",
        "b",
        "c"
    });

    std::vector<std::string> input3 ({
        "b"
    });

    std::vector<std::string> input4({
        "d",
        "a",
        "b",
        "c"
    });

    cout << "cfg: " << cfg << "\n\n";

    cout << "Member of CFG? " << (cfg.verify(input1) ? "true" : "false") << endl;
    cout << "Member of CFG? " << (cfg.verify(input2) ? "true" : "false") << endl;
    cout << "Member of CFG? " << (cfg.verify(input3) ? "true" : "false") << endl;
    cout << "Member of CFG? " << (cfg.verify(input4) ? "true" : "false") << endl;    

    return 0;
}