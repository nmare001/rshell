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
    check_exit(hold);
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
//return 2 is SemiObj
//retun -1 means no logical break in the command
int Composite::check_break(string str) {
    if(str == "&&") return 0;
    else if(str == "||") return 1;
    else if(str == ";") return 2;
    return -1;
}

//removes all the char that come after the comment
bool Composite::check_semi(string str) {
    if(str.at(str.size() - 1) == ';') return true;
    else return false;
}

//is called by activate and calls the builkd function which recurses
//sets up one command and tells build the first logical break object to create
void Composite::parse(string pr) {
    string i, com;
    int next_num;
    stringstream tran (pr);
    
    //loops until there is no more commands to loop
    while (tran >> i) {
        //checks if this is a string for a break object, -1 is comamnd string
        next_num = check_break(i);
        
        //still making the command, or there is no comment code
        if (next_num < 0) {
            com += " ";
            com += i;
            //at the end of the command check for the semi colon, then points 
            //to the object
            if(check_semi(com)) {
                com.pop_back();//removes the semi colon form the command
                auto next_com = make_shared<Command> (com);//creates an object
                baseContainer.push_back(make_shared<SemiObj> (next_com));
                com.clear();
                //pushes back object
            }
        }
        else {
            //if the com is not an empty string this is the primary start for
            //recursion
            if(!com.empty()) {
                shared_ptr<Command> next_com = make_shared<Command> (com);
                build(next_com,next_num,tran);
                com.clear();
            }
        }
    }
    if (!com.empty()){
        auto next_com = make_shared<Command> (com);
        baseContainer.push_back(make_shared<SemiObj> (next_com));
    }
}

//recursion starts with the left command object and a selected but un made 
//break object. is recursive to allow for a command string of any length
//recursion ends after either a semicolon, then it return back to parse
//or there are no more string command or arguements to read in
void Composite::build(shared_ptr<Command> A, int num, stringstream& tran) {
    string i,com;
    int next_num;
    
    //loop until there is no string parts to parse through
    while (tran >> i) {
        
        //checks if the current iteration of the command is a break
        next_num = check_break(i);
        //still making the command
        if (next_num < 0) {
            com += " ";
            com += i;
            //checsk if the semicolon is at the end of the string
            //might need to change if semicolon is in the middle of a string
            if(check_semi(com)) {
                com.pop_back();
                auto next_com = make_shared<Command> (com);
                baseContainer.push_back(make_shared<SemiObj> (next_com));
                return;
            }
        }
        else {
            //makes sure there is a command to imput
            if(!com.empty()) {
                //creates the new pointer 
                auto next_com = make_shared<Command> (com);
                //determines the proper break object and then recurses
                ///RECURSIVE CALLS START HERE
                if(num == 0) {
                    baseContainer.push_back(make_shared<AndObj>(A, next_com));
                    build(next_com,next_num,tran);
                    return;
                }
                else if(num == 1) {
                    baseContainer.push_back(make_shared<OrObj>(A, next_com));
                    build(next_com,next_num,tran);
                    return;
                }
            }
        }
    }
    ///STOPS RECURSIVE CALLING
    //there are no more string to read in and so caps it off as if there was a 
    //semi-colon
    if (!com.empty()){
        shared_ptr<Command> next_com = make_shared<Command> (com);
        if(num == 0) {
            baseContainer.push_back(make_shared<AndObj>(A, next_com));
            baseContainer.push_back(make_shared<SemiObj> (next_com));
            return;
        }
        else if(num == 1) {
            baseContainer.push_back(make_shared<OrObj>(A, next_com));
            baseContainer.push_back(make_shared<SemiObj> (next_com));
            return;
        }
        return;
    }
    ///RECURSIVE CALLS AGIAN
    //makes sure that linking logical objects are never without two children
    else {
        stringstream tra(unfinished_mod());
        build(A,num,tra);
        return;
    }
    return;
}


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