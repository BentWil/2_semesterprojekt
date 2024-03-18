#pragma once

#include<array>
#include"vec.h"


std::vector<Vec> pyramid(int cupheight, int grip, int diameter, int base)
{
    std::vector<Vec> list;
    Vec start(0,0,grip);   // placement of first cup
    Vec here;
    Vec hor(diameter,0,0);  // horizontal displacement between each cup in a line
    Vec ver(diameter/2,0,cupheight); // displacement of startingpoint between layers


    int height = base;

    // outer loop increases vertical placement per iteration
    for(int j=0; j<height; j++)
    {
        // inner loop places a whole line of cups
        here = start;
        for(int i=0; i<base; i++)
        {
            list.push_back(here);
            here.move(hor);
        }

        // move start of next line
        start.move(ver);
        // decrease number of cups in next line
        base--;
    }
    return list;
}
