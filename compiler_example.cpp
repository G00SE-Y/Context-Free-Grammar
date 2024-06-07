#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "CFG.h"

using std::cout, std::endl;


void print_chars(std::string s) {
    for(auto c: s) {
        if(c == '\n') std::cout << "\\n";
        else if (c == EOF) std::cout << "EOF";
        else std::cout << c; 
    }
}

int main() {

    CFG cfg = CFG();
    
    cfg.add_terminal("\n");

    // R-type
    cfg.add_terminal("add");
    cfg.add_terminal("sub");
    cfg.add_terminal("or");

    // I-type
    cfg.add_terminal("addi");
    cfg.add_terminal("ori");

    // registers
    cfg.add_terminal("$rd");
    cfg.add_terminal("$r1");
    cfg.add_terminal("$r2");

    // immediates
    cfg.add_terminal("0123456789");
    cfg.add_terminal("0b01");
    cfg.add_terminal("0x0123456789abcdef");

    // operand type rules
    cfg.add_rule("REG", std::vector<std::string>({"$rd", "|", "$r1", "|", "$r2"}));
    cfg.add_rule("IMM", std::vector<std::string>({"0123456789", "|", "0b01", "|", "0x0123456789abcdef"}));

    // operand type rules
    cfg.add_rule("RTYPE_OPERANDS", std::vector<std::string>({"REG", "REG", "REG"}));
    cfg.add_rule("ITYPE_OPERANDS", std::vector<std::string>({"REG", "REG", "IMM"}));

    // op type rules
    cfg.add_rule("RTYPE_OPS", std::vector<std::string>({"add", "|", "sub", "|", "or"}));
    cfg.add_rule("ITYPE_OPS", std::vector<std::string>({"addi", "|", "ori"}));

    cfg.add_rule("RTYPE", std::vector<std::string>({"RTYPE_OPS", "RTYPE_OPERANDS"}));
    cfg.add_rule("ITYPE", std::vector<std::string>({"ITYPE_OPS", "ITYPE_OPERANDS"}));


    cfg.add_rule("COMMAND", std::vector<std::string>({"RTYPE", "|", "ITYPE", "|", "none"}));
    cfg.add_rule("PROGRAM", std::vector<std::string>({"COMMAND", "\n", "PROGRAM", "|", "none"}));

    cfg.set_start_rule("PROGRAM");

    cout << cfg << endl;


    std::ifstream fp("input.txt");
    
    if(fp.is_open()) {

        std::string line;
        std::vector<std::string> program;
        std::stringstream ss;

        while(getline(fp, line, ' ')) {

            int pos;

            // if((pos = line.find(EOF)) >= 0) {
            //     std::cout << "contains EOF\n";
            //     line[pos] = '\n';
            // }

            while ((pos = line.find('\n')) >= 0) {
                if(pos == 0) {
                    program.push_back("\n");
                    line.erase(0, 1);
                }
                else {
                    program.push_back(line.substr(0, pos));
                    line.erase(0, pos);
                }
            }

            if(line.size() > 0) program.push_back(line);
        }

        if(program.back() != "\n") program.push_back("\n");

        cout << "Token Count: " << program.size() << "\n\n";
        for(auto& s: program) {
            print_chars(s);
            cout << "\n";
        }
        cout << "\n\n";

        cout << "Member of CFG? " << (cfg.verify(program) ? "true" : "false") << endl;
        fp.close();
    }
    


    return 0;
}