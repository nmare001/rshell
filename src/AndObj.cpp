#include "AndObj.h" 


AndObj::AndObj(string lhs, string rhs) {
    //the make shared is a slower implementation of the new pointer call
    //but it uses less memory and has better readability
    //bar = std::make_shared<int> (20);
    left = make_shared<Command> (lhs);
    right = make_shared<Command> (rhs);
    //cout << "constructor" << endl;
    
}

//constructor that points to already made Commands
AndObj::AndObj(shared_ptr<Base> lhs, shared_ptr<Base> rhs) {
    left = lhs;
    right = rhs;
}

AndObj::AndObj(shared_ptr <Base> lhs) {
   left = lhs;
}

bool AndObj::set_right(shared_ptr <Base> rhs) {
    if (rhs == nullptr) return false;
    right = rhs;
    return true;
}

bool AndObj::run() {
    ///still need to figure out how fork() work with this and if it need to be ran
    ///in this function call or command->run();
    //cout << "run" << endl;
    
    // //if the left command has been ran check to see if it worked
    // if(left->check_run()) {
    //     //if the left command worked then run the right command
    //     if(left->check_worked()) logic_fail = right->run();

    //     //the left command didn't work so don't run the command
    //     else {
    //         right->set_no_run();
    //         return false;
    //     }
    // }
    
    // //if the command has not been ran yet, run it
    // else {
    //     //cout << "ping" << endl;
    //     //the left succeeded so run the right command
    //     if(left->run()) return right->run();

    //     //the left command ran but didn't work so don't run anything
    //     else {
    //         right->set_no_run();
    //         return false;
    //     }
        
    // }
    // return false;
    
    
    //if left base worked run right
    //if the right worked return true
    //else return false
    bool lhs = left->run();
    //cout << lhs << endl;
    bool rhs = false;
    if(lhs) rhs = right->run();
    if(lhs && rhs) return true;
    return false;
}