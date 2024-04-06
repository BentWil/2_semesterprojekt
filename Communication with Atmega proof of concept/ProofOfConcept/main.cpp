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
    int serial_port = initMagVM();

    if(serial_port == 1){
        std::cout << "error while init\n";
        return 1;
    }


    // Write to serial port
    unsigned char msg[] = {'e'};
    write(serial_port, msg, sizeof(msg));



    // // Allocate memory for read buffer, set size according to your needs
    // char read_buf [256];

    // // Normally you wouldn't do this memset() call, but since we will just receive
    // // ASCII data for this example, we'll set everything to 0 so we can
    // // call printf() easily.
    // memset(&read_buf, '\0', sizeof(read_buf));

    // // Read bytes. The behaviour of read() (e.g. does it block?,
    // // how long does it block for?) depends on the configuration
    // // settings above, specifically VMIN and VTIME
    // int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));

    // // n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
    // if (num_bytes < 0) {
    //     printf("Error reading: %s", strerror(errno));
    //     return 1;
    // }

    // // Here we assume we received ASCII data, but you might be sending raw bytes (in that case, don't try and
    // // print it to the screen like this!)
    // printf("Read %i bytes. Received message: %s", num_bytes, read_buf);




    close(serial_port);




    return 0;
}
