#include <iostream>
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// transformation.cpp
//
// Code generation for function 'transformation'
//

// Include files
#include "transformation.h"

// Function Definitions
void FK_function(const double P[3])
{
    static const double b_a[16]{0.92718385456678742,
                              0.374606593415912,
                              0.0,
                              0.0,
                              0.37437839320073446,
                              -0.9266190392142547,
                              0.034899496702500969,
                              0.0,
                              0.013073581571653742,
                              -0.032358249875065734,
                              -0.99939082701909576,
                              0.0,
                              -0.09,
                              -0.684,
                              0.0,
                              1.0};
    static const signed char iv[4]{0, 0, 0, 1};
    double a[4];
    double P_idx_0;
    double P_idx_1;
    double P_idx_2;
    // Translation between the robot base and the custom frame, findes på selve
    // roboten
    // Rotation from robot base to custom frame is given in Z-Y-X Euler angles in
    // degress findes også på selve robotten
    // The tool measured in meter måles på gripper
    // Opbygning af transformationsmatrix fra base til custom
    // Making the point vektors a 4*1 so the can work with the transformation
    // matrix
    // Calculating the points in the robot frame, using X(4,1)=[] to remove the
    // 4th row to give a 3x1 position vektor
    P_idx_0 = P[0];
    P_idx_1 = P[1];
    P_idx_2 = P[2];
    for (int i{0}; i < 4; i++) {
        a[i] = (((b_a[i] * P_idx_0 + b_a[i + 4] * P_idx_1) + b_a[i + 8] * P_idx_2) +
                b_a[i + 12]) -
               static_cast<double>(iv[i]);
    }
    double output_data[2];
    int output_size[1];
    output_size[0] = 3;
    output_data[0] = a[0];
    output_data[1] = a[1];
    output_data[2] = a[2];
    std::cout<<output_data[0]<<std::endl;
    std::cout<<output_data[1]<<std::endl;
    std::cout<<output_data[2]<<std::endl;
}

int main(){
	double M[3]={0, 0, 0};
	FK_function(M);
	double M1[3]={0.30, 0, 0};
	FK_function(M1);
return 0;
}

