#ifndef Par_H
#define Par_H

//command.h includes base.h and is included in all the other break classes
//needs to operate like a command 
#include "Command.h"
#include <iostream>
using namespace std;

class ParObj: public Base
{
    protected:
        vector<shared_ptr<Base>> held_cmd;
        //the shared pointer insure that there are no memory leaks
    public:
        ParObj(vector <shared_ptr<Base>> passed);
        //will point the left and right to the lhs, and rhs
        //this will allow us to implement the command pointers at parsing
        //and so we can search the tru value
        ParObj();
        //will defien an object but the children will be nullptr
        virtual bool run();
        //will run the lefdt child and will run the right child
        //if the left child does not run then it will not run the right child
        //we will let the command class deal with its own run error checking
};
#endif 