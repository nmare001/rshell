#include "OrObj.h" 

OrObj::OrObj(string lhs, string rhs) {
    //the make shared is a slower implementation of the new pointer call
    //but it uses less memory and has better readability
    //bar = std::make_shared<int> (20);
    left = make_shared<Command> (lhs);
    right = make_shared<Command> (rhs);
    
}
//constructor that points to already made Commands
OrObj::OrObj(shared_ptr<Base> lhs, shared_ptr<Base> rhs) {
    left = lhs;
    right = rhs;
}

OrObj::OrObj(shared_ptr <Base> lhs) {
   left = lhs;
}

bool OrObj::set_right(shared_ptr <Base> rhs) {
    if (rhs == nullptr) return false;
    right = rhs;
    return true;
}

bool OrObj::run() {
    ///still need to figure out how fork() work with this and if it need to be ran
    ///in this function call or command->run();
    
    
    // //if the left command has been ran check to see if it worked
    // if(left->check_run()) {
    //     //if the left command worked then don't run the right command return false
    //     if(left->check_worked()) {
    //         right->set_no_run();
    //         return false;
    //     }
        
    //     //return whether the right command ran or not
    //     else return right->run();
        
    // }
    // //if the command has not been ran yet, run it
    // else {
    //     //the left succeeded so run nothing
    //     if(left->run()) {
    //         right->set_no_run();
    //         return false;
    //     }
            
    //     //the left command ran but didn't work so don't run anything
    //     else return right->run();
        
    // }
    // return false;
    
    bool lhs = left->run();
    bool rhs = false;
    //cout << lhs << endl;
    if(!lhs) {
        rhs = right->run();
    }
    if(lhs != rhs) return true;
    return false;
}