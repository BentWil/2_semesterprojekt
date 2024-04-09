#include<iostream>
#include<array>
#include<vector>
#include "pile.h"
#include "vec.h"
#include "pyramide.h"
    
 int main()
 {   
    	float grip_h = 0.05;
    	float pile_diff = 0.03;
    	int cupn = 14;
	float cuph = 0.08;
	float cupd = 0.05;
	float cupspace = 0.02;
    
    std::vector<Vec> positions = pyramidAllCups();
   
    std::vector<Vec> bunke = pile(grip_h,cupn, pile_diff);
   
    //std::cout << "Builds: ";
    for(int i = 0; i < cupn; i++)
    {
        positions[i].print();
        
        bunke[i].print();
        std::cout << std::endl;
    }
    std::cout  << std::endl;
}
