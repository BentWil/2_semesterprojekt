#pragma once

#include<array>

class Vec
{
public:
    Vec():ar({0, 0, 0})
    {}
    Vec(int x, int y, int z):ar({x, y, z})
    {}



    void move(Vec m)
    {
        ar[0] += m.ar[0];
        ar[1] += m.ar[1];
        ar[2] += m.ar[2];
    }

    void print()
    {
        std::cout << "(" <<ar[0] << ", " << ar[1] <<", " << ar[2] << ")";
    }
private:
    std::array<int,3> ar;

};
