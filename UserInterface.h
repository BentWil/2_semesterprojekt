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
    enum class UIState {
        MAIN_MENU,
        STACKING_CUPS
    } currentState = UIState::MAIN_MENU;

public:


    void displayWelcome() {
        std::cout << "Welcome to the Command Prompt Interface!" << std::endl
                  << "This is a simple command prompt program to control a UR5 robot to stack cups." << std::endl;
    }

    void displayHelp() {
        if (currentState == UIState::MAIN_MENU) {
            std::cout << "Available commands:" << std::endl
                      << "welcome - Displays the welcome message again." << std::endl
                      << "help - Lists available commands." << std::endl
                      << "cups - Enter the cup stacking mode." << std::endl
                      << "exit - Exits the program." << std::endl;
        } else if (currentState == UIState::STACKING_CUPS) {
            std::cout << "Cup Stacking commands:" << std::endl
                      << "pyramid - Stack the cups in a pyramid formation." << std::endl
                      << "exit - Return to main menu." << std::endl;
        }
    }



    void startProgram(){
        std::string userInput;

        // Command loop
        while (true) {
            std::cout << "> "; // Prompt for input
            std::getline(std::cin, userInput); // Get the entire line of input

            // Handle commands
            if(userInput =="cups"| userInput=="1"){
                currentState = UIState::STACKING_CUPS; // Change state to stacking cups
                stackingCups();
                currentState = UIState::MAIN_MENU;
            } else if (userInput == "welcome" | userInput=="2") {
                displayWelcome();
            } else if (userInput == "help" | userInput=="3") {
                displayHelp();
            } else if (userInput == "exit" | userInput=="4") {
                std::cout << "Exiting program." << std::endl;
                break; // Exit the loop, thus the program
            } else {
                std::cout << "Unrecognized command. Type 'help' to see available commands." << std::endl;
            }
        }
    }

    void stackingCups(){
    std::string userInput;
    int numberOfCups;
    int cupType;


        while(true){
            std::cout << "How do you want to stack the cups?" << std::endl;
            std::getline(std::cin, userInput);

            if(userInput == "pyramid" | userInput=="1"){
                std::cout << "How many cups do you want to stack(1-15)" << std::endl;
                std::cin >> numberOfCups;
                std::cout << "What cups do you want to use" << std::endl;
                std::cin >> cupType;
                std::cout << "Stacking cups in a pyramid shape..." << std::endl;

                Pyramid(numberOfCups, cupType   ).pyramidAllCups();
            } else if(userInput == "Tower" | userInput=="2"){

            } else if(userInput == "exit" | userInput == "3"){
                std::cout << "Returning to main menu." << std::endl;
                break;
            }

    }
}

};
#endif //UNTITLED_USERINTERFACE_H
