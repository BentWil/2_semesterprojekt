
#include "gripper.h"

int main()
{

    Gripper bigbertha("/dev/ttyUSB0");


    bigbertha.gClose();
    bigbertha.gOpen();



    return 0;
}
