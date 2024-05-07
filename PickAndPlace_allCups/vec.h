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
    double ar[3];


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
    friend Vec operator+(Vec l, const Vec& r){
    	Vec add = l;
    	add.ar[0] += r.ar[0];
        add.ar[1] += r.ar[1];
        add.ar[2] += r.ar[2];
        return add;
    }
    double* Getarray(){
    double cstyle[3];
    	cstyle[0] = ar[0];
    	cstyle[1] = ar[1];
    	cstyle[2] = ar[2];
    	return cstyle;
    }
private:
    

};
