#pragma once

#include <iostream>


class Gripper{

public:

    // constructor initializes communication
    Gripper(){

        std::cout << "Initialized gripper\n";
    }

    void lightOn(){
        std::cout << "ran lightOn()\n";
    }

    void lightOff(){
        std::cout << "ran lightOff()\n";
    }

    void gOpen(){
        std::cout << "ran gOpen()\n";
    }

    void gClose(){
        std::cout << "gOpen()\n";
    }



private:



};

