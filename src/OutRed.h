#ifndef OUTRED_H
#define OUTRED_H

//command.h includes base.h and is included in all the other break classes
#include "Command.h"
#include <iostream>
#include <memory>
//#include <system>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

class OutRed : public Base
{
    private:
        // shared_ptr<Base> left = nullptr;
        shared_ptr<Base> ptr = nullptr;
        int inp;
        string leftFile;
        int flag;
        // const char* path1;
        // const char* path2;
        //the shared pointer insure that there are no memory leaks
    public:
        //InRed(shared_ptr<Base>, shared_ptr<Base> rhs);
        //will point the left and right to the lhs, and rhs
        //this will allow us to implement the command pointers at parsing
        //and so we can search the tru value
        //InRed();
        //will defien an object but the child will be nullptr
        OutRed(string lhs, shared_ptr<Base> inPtr);
        OutRed(string str, int flag);
        //will implement the the string as commands in the constructor
        bool set_right(shared_ptr<Base> rhs);
        bool run();
        //will run the left child
        //we will let the command class deal with its own run error checking
};
#endif 