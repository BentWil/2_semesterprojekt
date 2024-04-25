#pragma once

#include <iostream>


class Gripper{

public:

    // constructor initializes communication
    Gripper(){
        std::cout << "Initialized gripper\n";
    }

    Gripper(std::string string){
        std::cout << "Initialized gripper " <<string <<"\n";
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

    void gOpen(std::string str){
        std::cout << "ran gOpen(), saving values with " << str << " as name \n";
    }

    void gClose(){
        std::cout << "gOpen()\n";
    }

    void gClose(std::string str){
        std::cout << "gOpen(), saving values with " << str << " as name \n";
    }


private:



};

