#ifndef Base_H
#define Base_H
#include <memory>
using namespace std;


class Base
{
    private:
        int ran = 0;
        //0 means the command hasn't been ran
        //1 mean it ran and worked
        //2 means it ran but failed
    public:
        virtual bool run() = 0;
        //might want to get rid of these and then change all the pointer to base
        //to pointers of Command
        bool check_run() {
            if (ran > 0) return true;
            return false;
        }
        bool check_worked() {
            if (ran == 1) return true;
            return false;
        }
        void set_no_run() {
            ran = 2;
        }
        void set_worked() {
            ran = 1;
        }
        virtual bool set_right(shared_ptr<Base> rhs) {
            if(rhs != nullptr) return false;
            return true;
        };
};
#endif 

