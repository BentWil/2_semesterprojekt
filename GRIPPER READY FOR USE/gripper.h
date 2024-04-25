#pragma once

#include <iostream>

//
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


//SQL
#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>






// REMEMBER: change SQLpassword+username, and possibly filename for UART










class Gripper{

public:

    // constructor initializes communication
    Gripper(){



        // init sql
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("../ProofOfConcept/test.db");
        db.open();

        std::cout << "Sql init done \n";

        // init UART
        _serialPort = open("/dev/ttyUSB0", O_RDWR);                 // find filename with terminal command:  ls -l /dev/ttyUSB* /dev/ttyACM

        if(tcgetattr(_serialPort, &tty) != 0) {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));

            std::cout << "If error 9, remember to connect microcontroller to VM\n";

            exit (EXIT_FAILURE);
        }

        tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
        tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
        tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
        tty.c_cflag |= CS8; // 8 bits per byte (most common)
        tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
        tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

        tty.c_lflag &= ~ICANON;
        tty.c_lflag &= ~ECHO; // Disable echo
        tty.c_lflag &= ~ECHOE; // Disable erasure
        tty.c_lflag &= ~ECHONL; // Disable new-line echo
        tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

        tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
        tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
        // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
        // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)


        tty.c_cc[VTIME] = 1;    // Wait for up to 2 deciseconds, returning as soon as any data is received.
        tty.c_cc[VMIN] = 0;

        // Set in/out baud rate to be 9600
        cfsetispeed(&tty, B9600);
        cfsetospeed(&tty, B9600);

        // Save tty settings, also checking for error
        if (tcsetattr(_serialPort, TCSANOW, &tty) != 0) {
            printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            exit (EXIT_FAILURE);
        }

        std::cout << "UART init done \n";

    }

    void lightOn(){
        write(_serialPort, "b", sizeof("a"));
    }

    void lightOff(){
        write(_serialPort, "e", sizeof("a"));
    }

    void gOpen(){
        write(_serialPort, "o", sizeof("o"));
        while(listen("Open"));
    }

    void gClose(){
        write(_serialPort, "c", sizeof("c"));
        while(listen("Close"));
    }



    void sqlTest(std::string sequence){
        QSqlQuery query;

        query.prepare("INSERT INTO data (current, sequence) VALUES (?,?);");
        query.addBindValue(10);
        query.addBindValue( QString::fromStdString(sequence));
        query.exec();
    }




    bool listen(std::string inputstring){

        QSqlQuery q;
        int8_t read_buf [10];

        int num_bytes = read(_serialPort, &read_buf, sizeof(read_buf));


        if (num_bytes < 0) {
            std::cout << "Error reading UART";
            return false;
        }

        if (0 == num_bytes){
            return false;
        }

        q.prepare("INSERT INTO data (current, sequence) VALUES (?, ?);");
        q.addBindValue(signed(read_buf[0]));
        q.addBindValue(QString::fromStdString(inputstring));
        q.exec();

        std::cout << signed(read_buf[0]);
        std::cout << std::endl;

        return true;
    }

    bool listen(){
        return listen("");

    }


private:

    int _serialPort;
    struct termios tty;




};

