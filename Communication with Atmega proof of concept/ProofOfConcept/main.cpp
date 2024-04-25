
#include "gripperDummy.h"

int main()
{

    Gripper bigbertha("/dev/ttyUSB0");

    bigbertha.gClose("hollo");


    bigbertha.gOpen();


    return 0;
}
