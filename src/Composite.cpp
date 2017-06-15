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


shared_ptr<Base> Composite::create_red(string base, int i) {
    shared_ptr<Base> ret = nullptr;
    if(i == 2) ret = make_shared<InRed> (base);
    else if(i == 1) ret = make_shared<OutRed> (base, i);
    else if(i == 0) ret = make_shared<OutRed> (base, i);
    return ret;
}

//checks if the parsed string is supposed to be a logical break
//return 3 is AndOj
//return 2 is OrObj
//return 1 is input red
//return 0 is output red
//retun -1 means no logical break in the command
int Composite::check_break(string& str) {
    if (str.empty()) return -2;
    if(str == "|") return 5;
    else if(str == "&&") return 4;
    else if(str == "||") return 3;
    else if( str == "<") return 2;
    else if( str == ">") return 1;
    else if(str == ">>") return 0;
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

//edit
bool Composite::check_Open_par(string& com) {
    if (com.empty()) return false;
    string str = com.substr(0,1);
    //cout << str << endl;
    if(str == "(") {
        //ping();
        com.erase(0,1);
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
    tran.clear();
    //cout << pr << endl;
    tran.str(pr);
    shared_ptr<Base> next_com = nullptr;
    shared_ptr<Base> red = nullptr;
    
    //loops until there is no more commands to loop
    while (tran >> i) {
        //checks if i is a break object
        next_num = check_break(i);
        //cout << next_num << endl;
        //if it isn't a break object the add the string to the full string of 
        //the command
        if (next_num < 0) {
            if(!com.empty()) com += " ";
            com += i;
            //checks if the first char of the com string is a (, 
            //com is never a space for the first character.
            // if(check_Open_par(com)) {
            //     //if there is a par as the first char, then run the string and 
            //     //stringstream through the par loop and have it return the top
            //     //pointer in the string. clear the string so it doesn't conflict
            //     //with the loop
            //     next_com = parenthesis(com,tran);
            //     com.clear();
            // }
        }
        else if(next_num < 3) {
            tran >> i;
            //cout << next_num << endl;
            red = create_red(i, next_num);
        }
        else if(next_num == 5) {
            //cout << "pipe creation_1" << endl;
            next_com = build_pipe(create_break(create_command(com,red), next_num));
            com.clear();
        }
        //the rest only happens if i is a break object
        else{
            //checks if com is empty and that there has been no par
            //next_com points to something for the rest
            if(next_com != nullptr) {
                //recurses down in the build function until the end of the 
                //stringstream tran
                build(create_break(next_com,next_num));
                return;
            }
            else if(next_com == nullptr && !com.empty()) {
                //creates a command based on com, then creates a break and then 
                //recurses it
                build(create_break(create_command(com,red), next_num));
                return;
            }
            else {
                perror("unexpected logical statement");
                exit(1);
            }
        }
    }
    if (!com.empty()){
        baseContainer.push_back(create_command(com,red));
        //if(red != nullptr) cout << "ping" << endl;
        return;
    }
    else {
        baseContainer.push_back(next_com);
    }
    //cout << tran.str() << endl;
    // else {
    //     baseContainer.push_back(next_com);
    // }
}

///22
void Composite::build(shared_ptr<Base> A) {
    string i,com;
    int next_num;
    bool stay = false;
    shared_ptr<Base> next_com = nullptr;
    shared_ptr<Base> red = nullptr;
    
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
            // if(check_Open_par(com)) {
            //     next_com = parenthesis(com,tran);
            //     stay = true;
            //     com.clear();
            // }
            //cout << com << endl;
            //b2 checking
        }
        else if(next_num < 2) {
            tran >> i;
            //cout << next_num << endl;
            red = create_red(i, next_num);
        }
        else if(next_num == 5) {
            //cout << "pipe creation_2" << endl;
            next_com = build_pipe(create_break(create_command(com,red), next_num));
        }
        else {
            //makes sure there is a command to imput
            if(!com.empty()) {
                //creates the new pointer 
                if(check_semi(com)){
                    auto next_com = create_command(com,red);
                    A->set_right(next_com);
                    baseContainer.push_back(A);
                    return;
                }
                else {
                    if(next_com == nullptr) next_com = create_command(com,red);
                    A->set_right(next_com);
                    shared_ptr<Base> B = create_break(A,next_num);
                    build(B);
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
         if(next_com == nullptr) next_com = create_command(com,red);
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
        tran.clear();
        tran.str(unfinished_mod());
        build(A);
        return;
    }
    return;
}


shared_ptr<Base> Composite::build_pipe(shared_ptr<Base> A) {
    //A is a Pipe object
    //cout << "pipe part 2" << endl;
    string i, com;
    int next_num;
    shared_ptr<Base> next_com = nullptr;
    shared_ptr<Base> red = nullptr;
    
    //loops until there is no more commands to loop
    while (tran >> i) {
        //checks if i is a break object
        next_num = check_break(i);
        //cout << next_num << endl;
        //if it isn't a break object the add the string to the full string of 
        //the command
        if (next_num < 0) {
            if(!com.empty()) com += " ";
            com += i;
        }
        else if(next_num < 2) {
            tran >> i;
            //cout << next_num << endl;
            red = create_red(i, next_num);
        }
        else if(next_num == 5) {
            //cout << "ping" << endl;
            next_com = create_command(com,red);
            A->set_right(next_com);
            return build_pipe(A);
        }
        else{
            //else I need to put back
            //can only be " &&", or " ||"
            tran.putback(' ');
            if( next_num == 3) {
                tran.putback('|');
                tran.putback('|');
            }
            else if(next_num == 4) {
                tran.putback('&');
                tran.putback('&');
            }
            if(!com.empty()) {
                A->set_right(create_command(com,red));
                return A;
            }
            else {
                exit(1);
                perror("unexpected element next to the '|'");
            }
        }
    }
    if (!com.empty()){
        //cout << com << endl;
        if(next_com == nullptr) next_com = create_command(com,red);
        A->set_right(next_com);
        //baseContainer.push_back(A);
        return A;
    }
    ///RECURSIVE CALLS AGIAN
    //makes sure that linking logical objects are never without two children
    
    else {
        tran.clear();
        tran.str(unfinished_mod());
        return build_pipe(A);
    }
    return A;
}


///somewhere in the below line there is a make error///
//33
shared_ptr<Base> Composite::parenthesis(string com, stringstream& tran) {
    string i;
    int next_num;
    shared_ptr<Base> next_com = nullptr;
    bool close = check_Close_par(com);
    
    //the last char of com is not a ), and there are more char in tran
    while (!close && tran >> i) {
        //check if i is a break object
        next_num = check_break(i);
        if (next_num < 0) {
            if(!com.empty()) com += " ";
            com += i;
            //check if the first char is (
            if(check_Open_par(com)) {
                next_com = parenthesis(com,tran);
                com.clear();
            }
            //check if the final character is )
            close = check_Close_par(com);
        }
        //the rest only happens if i is a break object
        else {
            //checks if com is empty and that there has been no par
            //next_com points to something for the rest
            if(next_com != nullptr) {
                //recurses down in the build function until the end of the 
                //stringstream
                return build_par(create_break(next_com, next_num), tran);
            }
            else if(next_com == nullptr && !com.empty()) {
                //creates a command based on com, then creates a break and then 
                //recurses it
                return build_par(create_break(create_command(com), next_num), tran);
            }
            //next_com == nullptr and com is empty
            //which means that there is a break object without a command
            else {
                perror("unexpected logical statement");
                exit(1);
            }
        }
    }
    //if com isn't empty, and tran is empty or close is true
    //so the while loop is done and there is a command left
    //need to check if there is a close par
    //if not error
    if (!com.empty() && close){
        if(cont){
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
    
    while (tran >> i && !cont) {
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
    if(i == 5) ret = make_shared<Pipe> (prior);
    else if (i == 4) ret = make_shared<AndObj> (prior);
    else if (i == 3) ret = make_shared<OrObj> (prior);
    return ret;
}

shared_ptr<Base> Composite::create_command(string com, shared_ptr<Base> hold) {
    shared_ptr<Base> ret = nullptr;
    if(check_test(com)) ret = make_shared<TestObj>(com);
    else ret = make_shared<Command>(com);
    if(hold == nullptr) return ret;
    else {
        hold->set_right(ret);
        //ping();
        return hold;
    }
}

shared_ptr<Base> Composite::create_command(string com) {
    shared_ptr<Base> ret = nullptr;
    if(check_test(com)) ret = make_shared<TestObj>(com);
    else ret = make_shared<Command>(com);
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