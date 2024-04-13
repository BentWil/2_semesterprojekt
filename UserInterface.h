//
// Created by bentw on 14/03/2024.
//

#ifndef UNTITLED_USERINTERFACE_H
#define UNTITLED_USERINTERFACE_H

#include <iostream>
#include <string>
#include "PickAndPlace_allCups/pyramide.h"

class UserInterface {

private:

public:


    void displayWelcome() {
        std::cout << "Welcome to the Command Prompt Interface!" << std::endl
                  << "This is a simple command prompt program to control a UR5 robot to stack cups." << std::endl;
    }

    void displayHelp() {
        std::cout << "Available commands:" << std::endl
                  << "welcome - Displays the welcome message again." << std::endl
                  << "help - Lists available commands." << std::endl
                  << "exit - Exits the program." << std::endl;
    }



    void startProgram(){
        std::string userInput;

        // Command loop
        while (true) {
            std::cout << "> "; // Prompt for input
            std::getline(std::cin, userInput); // Get the entire line of input

            // Handle commands
            if(userInput =="cups"){
                stackingCups();
            } else if (userInput == "welcome") {
                displayWelcome();
            } else if (userInput == "help") {
                displayHelp();
            } else if (userInput == "exit") {
                std::cout << "Exiting program." << std::endl;
                break; // Exit the loop, thus the program
            } else {
                std::cout << "Unrecognized command. Type 'help' to see available commands." << std::endl;
            }
        }
    }

    void stackingCups(){
    std::string userInput;

    Pyramid pyramid();
        while(true){
            std::cout << "How do you want to stack the cups?" << std::endl;
            std::getline(std::cin, userInput);

            if(userInput == "pyramid"){

                pyramid().pyramidAllCups();
            }

    }
}

};
#endif //UNTITLED_USERINTERFACE_H