#ifndef OR_H
#define OR_H

//command.h includes base.h and is included in all the other break classes
#include "Command.h"
#include <iostream>
#include <memory>
using namespace std;

class OrObj: public Base
{
    private:
        shared_ptr<Base> left = nullptr;
        shared_ptr<Base> right = nullptr;
        //the shared pointer insure that there are no memory leaks
    public:
        OrObj(shared_ptr<Base> lhs, shared_ptr<Base> rhs);
        //will point the left and right to the lhs, and rhs
        //this will allow us to implement the command pointers at parsing
        //and so we can search the tru value
        OrObj();
        //will defien an object but the children will be nullptr
        OrObj(string lhs, string rhs);
        //will implement the the string as commands in the constructor
        virtual bool run();
        //will run the left child
        //or will run the right child if the left child does not run.
        //we will let the command class deal with its own run error checking
        //return false when the left command ran, return true if the right command ran

};
#endif 