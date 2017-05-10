#ifndef SEMI_H
#define SEMI_H

//command.h includes base.h and is included in all the other break classes
#include "Command.h"
#include <iostream>
#include <memory>
using namespace std;

class SemiObj: public Base
{
    private:
        shared_ptr<Base> left = nullptr;
        //the shared pointer insure that there are no memory leaks
    public:
        SemiObj(shared_ptr<Base> lhs);
        //will point the left and right to the lhs, and rhs
        //this will allow us to implement the command pointers at parsing
        //and so we can search the tru value
        SemiObj();
        //will defien an object but the child will be nullptr
        SemiObj(string lhs);
        //will implement the the string as commands in the constructor
        virtual bool run();
        //will run the left child
        //we will let the command class deal with its own run error checking
};
#endif 