#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "OrObj.h"
#include "AndObj.h"
#include "SemiObj.h"
#include <boost/tokenizer.hpp>

class Composite {
    protected:
        string leave = "exit";
        bool cont;
        vector<shared_ptr<Base>> baseContainer;
        void print_prompt();
        void print_prompt2();
        string unfinished_mod();
        bool check_exit(string);
        int check_break(string);
        void parse(string);
        void run();
        void build(shared_ptr<Command> A, int num, stringstream& tran);
        bool check_semi(string);
        string remove_comment(string);
    public:
        Composite();
        Composite(string);
        void activate();
        
    
    
};
#endif