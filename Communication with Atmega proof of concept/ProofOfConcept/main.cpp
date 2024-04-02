#include <iostream>

//
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include "initMagVM.h"

using namespace std;

int main()
{
    int error = initMagVM();

    if(error){
        return error;
    }




    return 0;
}
