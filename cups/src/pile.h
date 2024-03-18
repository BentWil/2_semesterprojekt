#pragma once

#include<array>
#include<vector>
#include"vec.h"

//bottom cup is element 0
std::vector<Vec> pile(int grip,int cups, int diff)
{
    std::vector<Vec> list;
    Vec cup(0,0,grip);   // placement of first cup
    Vec shift(0,0,diff);

    //
    for(int i = 0; i<cups; i++)
    {
        list.push_back(cup);
        cup.move(shift);
    }

    return list;
}
