#pragma once
#include<iostream>
#include<array>
#include<vector>
#include"vec.h"

//bottom cup is element 0
std::vector<Vec> pile(float grip,int cups, float diff)
{
    std::vector<Vec> list;
    Vec cup(0,0,grip + (cups-1)*diff);   // placement of first cup
    Vec shift(0,0,-diff);

    //
    for(int i = 0; i<cups; i++)
    {
        list.push_back(cup);
        cup.move(shift);
    }

    return list;
}
