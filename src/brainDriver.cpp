#include "brainDriver.hpp"
#include "hamburger.hpp"

#define MAX_BUFFER 35

BrainDriver::BrainDriver() {
    pros::Task task(asyncReadSerialTask,Hamburger::getRobot(),"SerialReadTask");
}

void BrainDriver::asyncReadSerialTask(void* param) {
    Hamburger* robot = (Hamburger*)param;
    char buffer[MAX_BUFFER];
    while(true) {
        // We will always write out 35 bytes of data.
        fgets(buffer, MAX_BUFFER, stdin);
        if(strlen(buffer) > 0) {
            // do the thing
        }
        resetBuffer(buffer);
        pros::delay(1);
    }
}

void BrainDriver::resetBuffer(char* buffer) {
    for(int i=0; i<MAX_BUFFER; i++) {
        buffer[i] = '\0';
    }
}