#include "Composite.h"


int main() {
    Composite commandline;
    commandline.activate();
    
    
    // OrObj test(make_shared<Command>("ls -a"),make_shared<Command>("date"));
    // test.run();
    
    //AndObj test("ls", "date");
    //test.run();
    return 0;
}