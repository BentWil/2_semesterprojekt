#include<iostream>
#include<array>
#include<vector>
#include "vec.h"
#include "pyramid.h"
#include "pile.h"


int main(int argc,char** argv){


    int cup_d = 50;     //mm
    int cup_h = 100;
    int grip_h = 75;    // heigh of TCP while gripping
    int cup_count = 10;
    int base_p = 4;     //base of pyramid in cups
    int pile_diff = 20; // difference between height of single cup and double cup




    std::vector<Vec> positions = pyramid(cup_h,grip_h,cup_d,base_p);
   
    std::vector<Vec> bunke = pile(grip_h,cup_count, pile_diff);
   
    std::cout<< "Builds: ";
    for(int i = 0; i< cup_count;i++)
    {
        positions[i].print();
        
        bunke[i].print();
        std::cout << std::endl;
    }
    std::cout  << std::endl;


  
/*
    std::cout<< "From: ";
        for(int i = 0; i < cup_count; i++)
    {
        positions[i].print();
    }
    std::cout  << std::endl;*/


}



