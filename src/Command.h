#ifndef Command_H
#define Command_H


//is included in all break logic classes
#include "Base.h"
#include <iostream>
#include <memory>
#include <stdio.h>//don't knoww if we need
#include <sys/types.h>//don't know if we need
#include <unistd.h>//for execvp();
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include "Base.h"
#include <fstream>
//#include <inFile>
//#include <outFile>
using namespace std;

class Command: public Base
{
    
    //change the protected datatype from string to char* array. at construction 
    //we would parse the string out by each space and parse that into a sperate 
    //cell in the array. this would be run by a private non-virtaul function
    protected:
        string com;
        //char* c_char = NULL;
        //is the string of the command and all arguemnets that are going to
        //be ran. is still contains all spaces tha the user typed in
        vector<char*> trans();
        //return the string com as a veector of char to be run in excvp
    public:
        Command();
        //will defien an object but there will be no stirng com
        Command(string con);
        //will implement the the string as the string con
        virtual bool run();
        //will run the 
        int test_red(string&, string&);
};
#endif 