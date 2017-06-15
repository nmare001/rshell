#include "InRed.h"


InRed::InRed(string lhs, shared_ptr<Base> inPtr) {
    ptr = inPtr;
    leftFile = lhs;
    inp = dup(0);
    //cout << "hello";
}


bool InRed::run() {
    //cout << "run" << endl;
    int sdin = dup(0);
    //if(ptr == nullptr) cout << "error" << endl;
    int fd = open(leftFile.c_str(), O_RDONLY|O_CREAT, 0777);
    dup2(fd, 0); // stdin now points to fd
    close(fd);
    
    bool ret = ptr->run();
    
    dup2(sdin, 0);
    close(sdin);
    
    return ret;
}

InRed::InRed(string str) {
    leftFile = str;
    //inp = dup(0);  
    //cout << "hello" << endl;
}

bool InRed::set_right(shared_ptr<Base> rhs) {
    if(rhs == nullptr) return false;
    ptr = rhs;
    return true;
}

