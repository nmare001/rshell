#include "SemiObj.h" 


SemiObj::SemiObj(string lhs) {
    //the make shared is a slower implementation of the new pointer call
    //but it uses less memory and has better readability
    //bar = std::make_shared<int> (20);
    left = make_shared<Command> (lhs);
    
}
//constructor that points to already made Commands
SemiObj::SemiObj(shared_ptr<Base> lhs) {
    left = lhs;
}

bool SemiObj::run() {
    //need to add back the true and false of the commands
    //but only for the left command because we don't want to run a command twice
    
    //if the left command has been ran check to see if it worked
    if(left->check_run()) {
        //then return if it worked
        return left->check_worked(); 
    }
    //if the command has not been ran yet, run it
    else {
        return left->run();
        
    }
    return false;
}