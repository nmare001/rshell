#include "OutRed.h"


OutRed::OutRed(string lhs, shared_ptr<Base> inPtr) {
    ptr = inPtr;
    leftFile = lhs;
    //inp = dup(1);
    cout << "hello";
}


bool OutRed::run() {
    int sdin = dup(1);
    int fd = 0;
    if(flag == 1) fd = open(leftFile.c_str(), O_CREAT|O_WRONLY, 0777);
    else if(flag == 0) fd = open(leftFile.c_str(), O_CREAT|O_WRONLY|O_APPEND, 0777);
    else { 
        exit(1);
        perror("no flag");
    }
    //cout << fd << endl;
    dup2(fd, 1); // stdin now points to fd
    close(fd);
    //runs the command on the right
    bool ret = ptr->run();
    //switches back to standard out
    dup2(sdin, 1);
    
    close(sdin);
    
    return ret;
}

OutRed::OutRed(string str, int flag) {
    leftFile = str;
    this->flag = flag;
    //inp = dup(1);  
    //cout << "hello" << endl;
}

bool OutRed::set_right(shared_ptr<Base> rhs) {
    if(rhs == nullptr) return false;
    ptr = rhs;
    return true;
}

