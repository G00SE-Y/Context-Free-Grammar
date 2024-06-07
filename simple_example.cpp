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
    
    cfg.add_terminal("a");
    cfg.add_terminal("b");
    cfg.add_terminal("c");

    cfg.add_rule("A", std::vector<std::string>({"a"}));
    cfg.add_rule("B", std::vector<std::string>({"b"}));
    cfg.add_rule("C", std::vector<std::string>({"c"}));
    
    cfg.add_rule("ABC", std::vector<std::string>({"A", "B", "C"}));
    cfg.add_rule("[ABC]", std::vector<std::string>({"A", "|", "B", "|", "C"}));
    cfg.add_rule("ABC+", std::vector<std::string>({"ABC", "ABC+", "|", "none"}));

    cfg.add_rule("LANGUAGE", std::vector<std::string>({"[ABC]", "ABC+"}));

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

    cout << "Member of CFG? " << (cfg.verify(input1) ? "true" : "false") << endl;
    cout << "Member of CFG? " << (cfg.verify(input2) ? "true" : "false") << endl;
    cout << "Member of CFG? " << (cfg.verify(input3) ? "true" : "false") << endl;
    cout << "Member of CFG? " << (cfg.verify(input4) ? "true" : "false") << endl;
    


    return 0;
}