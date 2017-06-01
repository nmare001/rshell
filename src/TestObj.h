#ifndef TESTOBJ_H
#define TESTOBJ_H
//command.h includes base.h and is included in all the other break classes
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include "Command.h"
#include <iostream>
#include <memory>
#include <sys/types.h>
#include <sstream>


using namespace std;

class TestObj: public Base
{
    private:
        shared_ptr<Base> filePath = nullptr;
        const char* path;
        
        //the shared pointer insure that there are no memory leaks
        char flag;
        //this is the glag that tells us which test to run
    public:
        TestObj(shared_ptr<Base> filePath);
        //will point the left and right to the lhs, and rhs
        //this will allow us to implement the command pointers at parsing
        //and so we can search the tru value
        TestObj();
        //will defien an object but the children will be nullptr
        TestObj(const char* path);
        //will implement the the string as commands in the constructor
        TestObj(string Spath);
        bool parse(string& com);
        
        virtual bool exists();
        virtual bool run();
        //will test if the filepath testing occurs
        //or will run the right child if the left child does not run.
        //we will let the command class deal with its own run error checking
        //return false when the left command ran, return true if the right command ran

};
#endif 