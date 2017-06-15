#include "Command.h"

///sets a string as the command to be run
Command::Command(string con) {
    com = con;
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
                this->set_worked();
                return true;
            }
            else {//else exit(1) terminated
                //the command didn't work
                this->set_no_run();
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

//return 0 if none are found
//return 1 if input redirection
//return 2 if output redirection
//return 3 if both
//needs delete the arrows if there are any
// int Command::test_red(string& in, string& out) {
   
// }