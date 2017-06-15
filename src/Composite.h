#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "OrObj.h"
#include "AndObj.h"
#include "SemiObj.h"
#include "TestObj.h"
#include "InRed.h"
#include "OutRed.h"
#include "Pipe.h"
#include <boost/tokenizer.hpp>

class Composite {
    protected:
        string leave = "exit";
        vector<shared_ptr<Base>> baseContainer;
        bool cont;
        stringstream tran;
        
        void run();
        void print_prompt();
        void print_prompt2();
        string unfinished_mod();
        
        bool check_path(string&);
        bool check_bracket(string&);
        bool check_exit(string);
        bool check_semi(string&);
        int  check_break(string&);
        bool check_test(string& com);
        bool check_Open_par(string& com);
        bool check_Close_par(string& com);
        
        shared_ptr<Base> create_break(shared_ptr<Base> A, int i);
        shared_ptr<Base> create_command(string com,shared_ptr<Base>);
        shared_ptr<Base> create_command(string com);
        shared_ptr<Base> create_red(string, int);
        shared_ptr<Base> parenthesis(string com, stringstream& tran);
        shared_ptr<Base> build_par(shared_ptr<Base> A, stringstream& tran);
        
        void build(shared_ptr<Base> A);
        shared_ptr<Base> build_pipe(shared_ptr<Base> A);
        void parse(string);
        string remove_comment(string);
        string b2_checking(string start, stringstream& tran);
        
        void ping();
    public:
        Composite();
        Composite(string);
        void activate();
        
    
    
};
#endif