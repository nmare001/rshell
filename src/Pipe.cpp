#include "Pipe.h

//clears and set the vector
Pipe::Pipe(shared_ptr<Base> inPtr) {
    pip.clear();
    pip.push_back(inPtr);
}

//adds pointer to the vector pip
bool Pipe::set_right(shared_ptr<Base> rhs) {
    if(rhs == nullptr) return false;
    pip.push_back(rhs);
    return true;
}

bool Pipe::run() {
    //pip then run each element in the vector
    //cout << "ran" << endl;
    
    //set up
    int piping[2], sdin = dup(0), sdout = dup(1);
    pipe(piping);
    
    //alter output
    dup2(piping[1], 1);
    close(piping[1]);
    
    //run first process
    pip.at(0)->run();
    
    //alter input
    dup2(piping[0], 0);
    close(piping[0]);
    
    //run the rest but one process
    for (unsigned int i = 1; i < pip.size() - 1; ++i) {
        pip.at(i)->run();
    }
    
    //alter output to the prior output
    dup2(sdout, 1);
    close(sdout);
    
    //print last process
    pip.at(pip.size() - 1)->run();
    
    //alter the input to the prior input
    dup2(sdin, 0);
    close(sdin);
    return true;
}