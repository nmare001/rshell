#include "Command.h"

///sets a string as the command to be run
Command::Command(string con) {
    com = con;
}

//sets a command to not be ran by a different logical class that points to the 
//same object
void Command::set_no_run() {
    ran = 2;
}

//forks the process so system calls can be made without ended the program
bool Command::run () {
    //create child process
    pid_t pid = fork();
    
    //fork failed
    if(pid < 0) {
        perror("fork failure");
        exit(1);
    }
    //child process
    else if (pid == 0) {
        //uses the vector instread of arrray to run the command
        //the first index is that command
        //the other indecies are arguments
        vector <char*> args = this->trans();
        //if execvp doesn't end process, exit(1) will
        if(execvp(args.at(0),args.data()) == -1) {
            perror("execvp didn't find the file");
            exit(1);
        }
    }
    //parent process
    else {
        int status;
        pid = wait(&status);//wait until child is terminated and give the reasn
        if(WIFEXITED(status)) {//if true than it was terminated
            if(WEXITSTATUS(status) == 0) {//if true execvp terminated
                //the command worked
                ran = 1;
                return true;
            }
            else {//else exit(1) terminated
                //the command didn't work
                ran = 2;
                return false;
            }
        }
        else {
            perror("wait failed");
            exit(1);
        }
    }
    return false;
}


//if the ran is 1 or 2 that mean that the Command::run() has been run
//return true if it has been run, return false if it hasn't been run
bool Command::check_run() {
    if (ran > 0) return true;
    else return false;
}

//checks if the Command::run() worked as in the command was found in /bin.
//the /bin fnctionality has not been added yet
//returns true if the command was found and ran
//return false if the command was not found and not ran
bool Command::check_worked() {
    if (ran == 1) return true;
    else return false;
}

//changes the com string into a vector of char so that it can be inputted into
//execvp() function
vector<char*> Command::trans() {
    //taking in a string
    stringstream push(com);
    string temp;
    vector <string> contain;
    while(push>>temp) {
        contain.push_back(temp);
    }
    //cout << contain.size() << endl;
    //a vector of character pointers
    vector<char*> print;
    //takes in the string of input and converts it to a vector of character pointers
    for (unsigned int i = 0; i < contain.size(); ++i) {
        print.push_back(&contain[i][0]);
    }
    return print;
    
}
