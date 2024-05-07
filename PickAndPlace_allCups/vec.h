#pragma once
#include<iostream>
#include<array>

class Vec
{
public:
    Vec():ar({0, 0, 0})
    {}
    Vec(double x, double y, double z):ar({x, y, z})
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
    Vec operator+(Vec m){
    	Vec add({0, 0, 0});
    	add.ar[0] += m.ar[0];
        add.ar[1] += m.ar[1];
        add.ar[2] += m.ar[2];
        return add;
    }
    double* Getarray(){
    	double cstyle[3];
    	std::copy(ar, ar + 3, cstyle);
    	return cstyle;
    }
private:
    double ar[3];

};
