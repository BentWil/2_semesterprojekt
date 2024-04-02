#include<iostream>
#include<array>
#include<vector>
#include "pile.h"
#include "vec.h"
#include "pyramide.h"
    
 int main()
 {   
    	int grip_h = 5;
    	int pile_diff = 3;
    	int cupn = 40;
	int cuph = 8;
	int cupd = 5;
	int cupspace = 2;
    
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
