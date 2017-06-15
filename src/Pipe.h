#ifndef PIPE_H
#define PIPE_H

//command.h includes base.h and is included in all the other break classes
#include "Command.h"
#include <iostream>
#include <memory>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

class Pipe: public Base
{
    private:
        vector<shared_ptr<Base>> pip;
        //shared_ptr<Base> first = nullptr;
        string preparse;
        //the shared pointer insure that there are no memory leaks
    public:
        Pipe(shared_ptr<Base> inPtr);
        Pipe(string str, int flag);
        //will implement the the string as commands in the constructor
        bool set_right(shared_ptr<Base> rhs);
        bool run();
        
};
#endif 