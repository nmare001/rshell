#ifndef AND_H
#define AND_H

//command.h includes base.h and is included in all the other break classes
#include "Command.h"
#include <iostream>
using namespace std;

class AndObj: public Base
{
    protected:
        shared_ptr<Base> left = nullptr;
        shared_ptr<Base> right = nullptr;
        //the shared pointer insure that there are no memory leaks
    public:
        AndObj(shared_ptr<Base> lhs, shared_ptr<Base> rhs);
        //will point the left and right to the lhs, and rhs
        //this will allow us to implement the command pointers at parsing
        //and so we can search the tru value
        AndObj();
        //will defien an object but the children will be nullptr
        AndObj(string lhs, string rhs);
        //will implement the the string as commands in the constructor
        virtual bool run();
        //will run the lefdt child and will run the right child
        //if the left child does not run then it will not run the right child
        //we will let the command class deal with its own run error checking
};
#endif 