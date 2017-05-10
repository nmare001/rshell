#ifndef Base_H
#define Base_H
#include <memory>


class Base
{
    public:
       virtual bool run() = 0;
       //might want to get rid of these and then change all the pointer to base
       //to pointers of Command
       virtual bool check_run() {return false;}
       virtual bool check_worked() {return false;}
       virtual void set_no_run() {return;}
};
#endif 

