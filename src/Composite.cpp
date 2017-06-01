#include "Composite.h"

//used to always print out the command prompt
void Composite::print_prompt() {
    cout << "$ ";
}

//prints out the prompt for the unfinsihed mod telling the user that there is a 
//logical connection object that needs a right child
void Composite::print_prompt2(){
    cout << "> ";
}
//will check if the user want to leave the shell
//it will set the protected cont to false
//in the function activate, the cont will be called to continue
bool Composite::check_exit(string line) {
    if (line == leave){
        cont = false;
        return false;
    }
    else if (line == (" " + leave)){
        cont = false;
        return false;
    }
    else if (line == (leave + " ")){
        cont = false;
        return false;
    }
    else if (line == (" " + leave + " ")){
        cont = false;
        return false;
    }
    return true;
}

//is used to re print out the second commmand prompt so there are no unfinshed 
//logical connections
string Composite::unfinished_mod() {
    string hold;
    print_prompt2();
    getline(cin,hold);
    return hold;
}

//iterates throught the logical break classes and calls run on each one
void Composite::run() {
    //cout << baseContainer.size() << endl;
    for (unsigned int i = 0; i < baseContainer.size(); ++i) {
        baseContainer.at(i)->run();
    }
    baseContainer.clear();
    //clears out vector for a second run
}

//the only real public function
//this will call the user interface and will take in the commands
void Composite::activate() {
    string hold;
    while (cont) {//while cont is true loop for more commands
        print_prompt();//prints out $
        getline(cin, hold);//gets the whole line of commands
        check_exit(hold);//checks if the exit command was called
        hold = remove_comment(hold);
        //cout << hold;
        if(cont) {//if exit command wasn't called parse and build queue
            parse(hold);
        }
        run();//runs all the currently held commands
    }
}

//removes all chars after a comment command
//can be changed later to use the commented char
string Composite::remove_comment(string str) {
    string::size_type pos = str.find('#');
    if (pos != std::string::npos) return str.substr(0, pos);
    else return str;
}


//checks if the parsed string is supposed to be a logical break
//return 0 is AndOj
//return 1 is OrObj
//return 2 is Par
//retun -1 means no logical break in the command
int Composite::check_break(string& str) {
    if (str.empty()) return -1;
    if(str == "&&") return 0;
    else if(str == "||") return 1;
    // else if(str1 == "(") {
    //     str.erase(0,1);
    //     return 2;
    // }
    //ping();
    return -1;
}

bool Composite::check_Close_par(string& com) {
    if (com.empty()) return false;
    string str = com.substr(com.size() - 1,1);
    if(str == ")") {
        com.erase(com.size() - 1,1);
        return true;
    }
    return false;
}

bool Composite::check_Open_par(string& com) {
    if (com.empty()) return false;
    string str = com.substr(1,1);
    //cout << str << endl;
    if(str == "(") {
        //ping();
        com.erase(0,2);
        return true;
    }
    return false;
}

bool Composite::check_test(string& com) {
    if (com.empty()) return false;
    if (check_bracket(com)) return true;
    else if (check_path(com)){
        return true;
        //cout << "path" << endl;
    }
    return false;
}

bool Composite::check_bracket(string& com) {
    if (com.empty()) return false;
    string str = com.substr(1,1);
    if (str == "["){
        str = com.substr(2,1);
        if (str == " ") com.erase(0,3);
        else com.erase(0,2);
        str = com.substr(com.size() - 1,1);
        if(str == "]") {
            com.erase(com.size() - 1, 1);
        }
        return true;
    }
    return false;
}

bool Composite::check_path(string& com) {
    if (com.empty()) return false;
    string str = com.substr(1,4);
    //cout << str << endl;
    if (str == "test") {
        str = com.substr(5,1);
        if (str == " ") com.erase(0,6);
        else com.erase(0,5);
        return true;
    }
    return false;
}

bool Composite::check_semi(string& com) {
    if (com.empty()) return false;
    string str = com.substr(com.size() - 1, 1);
    if(str == ";") {
        com.erase(com.size() - 1,1);
        return true;
    }
    return false;
}

void Composite::ping() {
    cout << "ping" << endl;
}

////11
void Composite::parse(string pr) {
    string i, com;
    int next_num;
    stringstream tran (pr);
    shared_ptr<Base> next_com = nullptr;
    
    //loops until there is no more commands to loop
    while (tran >> i) {
        //cout << "1" << endl;
        //checks if this is a string for a break object, -1 is comamnd string
        next_num = check_break(i);
        //cout << next_num << endl;
        if (next_num < 0) {
            com += " ";
            com += i;
            //cout << com << endl;
            //ping();
            if(check_Open_par(com)) {
                next_com = parenthesis(com,tran);
                // bool te = next_com->run();
                // cout << te << endl;
                com.clear();
            }
        }
        else {
            //if the com is not an empty string this is the primary start for
            //recursion
            if(!com.empty() || next_com != nullptr) {
                //creates the new pointer 
                if(check_semi(com)){
                    next_com = create_command(com);
                    baseContainer.push_back(next_com);
                    return;
                }
                else {
                    if(next_com == nullptr) next_com = create_command(com);
                    shared_ptr<Base> B = create_break(next_com,next_num);
                    //B->run();
                    build(B, tran);
                    //ping();
                    return;
                }
            }
        }
    }
    if (!com.empty()){
        auto next_com = create_command(com);
        //ping();
        baseContainer.push_back(next_com);
        return;
    }
    else {
        baseContainer.push_back(next_com);
    }
}

///22
void Composite::build(shared_ptr<Base> A, stringstream& tran) {
    string i,com;
    int next_num;
    bool stay = false;
    shared_ptr<Base> next_com = nullptr;
    
    //loop until there is no string parts to parse through
    while (tran >> i) {
        //cout << "2" << endl;
        //checks if the current iteration of the command is a break
        //b1 checking
        next_num = check_break(i);
        //still making the command
        if (next_num < 0) {
            com += " ";
            com += i;
            if(check_Open_par(com)) {
                next_com = parenthesis(com,tran);
                stay = true;
                com.clear();
            }
            //cout << com << endl;
            //b2 checking
        }
        else {
            //makes sure there is a command to imput
            if(!com.empty()) {
                //creates the new pointer 
                if(check_semi(com)){
                    auto next_com = create_command(com);
                    A->set_right(next_com);
                    baseContainer.push_back(A);
                    return;
                }
                else {
                    if(next_com == nullptr) next_com = create_command(com);
                    A->set_right(next_com);
                    shared_ptr<Base> B = create_break(A,next_num);
                    build(B, tran);
                    return;
                }
                
            }
        }
    }
    ///STOPS RECURSIVE CALLING
    //there are no more string to read in and so caps it off as if there was a 
    //semi-colon
    if (!com.empty()){
        //cout << com << endl;
         if(next_com == nullptr) next_com = create_command(com);
        A->set_right(next_com);
        baseContainer.push_back(A);
        return;
    }
    ///RECURSIVE CALLS AGIAN
    //makes sure that linking logical objects are never without two children
    else if(stay) {
        A->set_right(next_com);
        baseContainer.push_back(A);
    }
    else {
        stringstream tra(unfinished_mod());
        build(A, tra);
        return;
    }
    return;
}


//33
shared_ptr<Base> Composite::parenthesis(string com, stringstream& tran) {
    string i;
    int next_num;
    shared_ptr<Base> next_com = nullptr;
    bool cont = check_Close_par(com);
    //cout << com << endl;
    //loops until there is no more commands to loop
    while (tran >> i && !cont) {
        //checks if this is a string for a break object, -1 is comamnd string
        //cout << "3" << endl;
        next_num = check_break(i);
        //cout << next_num << endl;
        //still making the command, or there is no comment code
        if (next_num < 0) {
            com += " ";
            com += i;
            if(check_Open_par(com)) {
                next_com = parenthesis(com,tran);
                com.clear();
            }
            else {
                cont = check_Close_par(com);
                break;
            }
            //b2 checking
        }
        else {
            //if the com is not an empty string this is the primary start for
            //recursion
            if(!com.empty()) {
                //creates the new pointer 
               if(check_semi(com)){
                    if(next_com == nullptr) next_com = create_command(com);
                    baseContainer.push_back(next_com);
                }
                else {
                    if(next_com == nullptr) next_com = create_command(com);
                    shared_ptr<Base> B = create_break(next_com,next_num);
                    return build_par(B, tran);
                }
            }
        }
    }
    if (!com.empty()){
        if(cont){
            //cout << com << endl;
            if(next_com == nullptr) next_com = create_command(com);
            return next_com;
        }
        else {
            exit(1);
        }
    }
    return nullptr;
}

//44
shared_ptr<Base> Composite::build_par(shared_ptr<Base> A, stringstream& tran) {
    string i,com;
    int next_num;
    bool cont = false;
    shared_ptr<Base> next_com = nullptr;
    
    //loop until there is no string parts to parse through
    while (tran >> i && !cont) {
        //cout << "4" << endl;
        //checks if the current iteration of the command is a break
        //b1 checking
        next_num = check_break(i);
        //still making the command
        if (next_num < 0) {
            com += " ";
            com += i;
            if(check_Open_par(com)) {
                next_com = parenthesis(com,tran);
                com.clear();
            }
            else {
                cont = check_Close_par(com);
                break;
            }
            //b2 checking
        }
        else {
            //makes sure there is a command to imput
            if(!com.empty()) {
                //creates the new pointer 
                if(check_semi(com)){
                     if(next_com == nullptr) next_com = create_command(com);
                    return next_com;
                }
                else {
                     if(next_com == nullptr) next_com = create_command(com);
                    A->set_right(next_com);
                    shared_ptr<Base> B = create_break(A,next_num);
                    return build_par(B, tran);
                }
                
            }
        }
    }
    ///STOPS RECURSIVE CALLING
    //there are no more string to read in and so caps it off as if there was a 
    //semi-colon
    if (!com.empty()){
        if(cont) {
            if(next_com == nullptr) next_com = create_command(com);
            A->set_right(next_com);
            return A;
        }
        else {
            exit(1);
        }
    }
    ///RECURSIVE CALLS AGIAN
    //makes sure that linking logical objects are never without two children
    else {
        stringstream tra(unfinished_mod());
        return build_par(A, tra);
        
    }
    return nullptr;
}

//should only run if i is 1 0r 2
shared_ptr<Base> Composite::create_break(shared_ptr<Base> prior, int i) {
    shared_ptr<Base> ret = nullptr;
    if (i == 0) ret = make_shared<AndObj> (prior);
    else if (i == 1) ret = make_shared<OrObj> (prior);
    return ret;
}

shared_ptr<Base> Composite::create_command(string com) {
    shared_ptr<Base> ret = nullptr;
    // if (check_Open_par(com)) {
    //     //ping();
    //     ret = parenthesis(com, tran);
    // }
    if(check_test(com)) ret = make_shared<TestObj>(com);
    else {
        ret = make_shared<Command>(com);
        //cout << "command" << endl;
    }
    return ret;
}


//is called by activate and calls the builkd function which recurses
//sets up one command and tells build the first logical break object to create

//construtor that allows activate to be ran
Composite::Composite() {
    cont = true;
}

//construtor that allows activate to be ran
//also allows user to set their own "quit" command
Composite::Composite(string out) {
    cont = true;
    leave = out;
}