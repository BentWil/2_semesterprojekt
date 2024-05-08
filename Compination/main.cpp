#include <iostream>
#include <cmath>
#include <limits>
#include <thread>
#include <chrono>
#include <csignal>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

//Includes for control of the robot through ur_rtde
#include "../ur_rtde/include/ur_rtde/rtde_control_interface.h"
#include "../ur_rtde/include/ur_rtde/rtde_receive_interface.h"
#include "../boost/program_options.hpp"

//Includes for finding cup placement position
#include "../PickAndPlace_allCups/pile.h"
#include "../PickAndPlace_allCups/vec.h"
#include "../PickAndPlace_allCups/pyramide.h"

//Includes for Gripper control
#include "../GRIPPER READY FOR USE/gripper.h"
#include <bits/stdc++.h>

//Includes for matlab function, all files matlab code generator created has been included just in case.
#include "../FK_func/fkfunc_data.h"
#include "../FK_func/fkfunc_initialize.cpp"
#include "../FK_func/fkfunc_initialize.h"
#include "../FK_func/fkfunc_terminate.cpp"
#include "../FK_func/fkfunc_types.h"
#include "../FK_func/rt_defines.h"
#include "../FK_func/rtGetInf.cpp"
#include "../FK_func/rtGetInf.h"
#include "../FK_func/rtGetNaN.h"
#include "../FK_func/rt_nonfinite.cpp"
#include "../FK_func/rt_nonfinite.h"
#include "../FK_func/rtwtypes.h"
#include "../FK_func/sqrt.cpp"
#include "../FK_func/sqrt.h"
#include "../FK_func/svd.cpp"
#include "../FK_func/svd.h"
#include "../FK_func/tmwtypes.h"
#include "../FK_func/xaxpy.cpp"
#include "../FK_func/xaxpy.h"
#include "../FK_func/xdotc.cpp"
#include "../FK_func/xdotc.h"
#include "../FK_func/xnrm2.cpp"
#include "../FK_func/xnrm2.h"
#include "../FK_func/xrot.cpp"
#include "../FK_func/xrot.h"
#include "../FK_func/xrotg.cpp"
#include "../FK_func/xrotg.h"
#include "../FK_func/xswap.cpp"
#include "../FK_func/xswap.h"
#include "../FK_func/fkfunc.h"
#include "../FK_func/fkfunc.cpp"
#include "../FK_func/rtGetNaN.cpp"
#include "../FK_func/fkfunc_terminate.h"
#include "../FK_func/rt_nonfinite.h"

using namespace ur_rtde;
using namespace ur_rtde;
using namespace std::chrono;
namespace po = boost::program_options;

// Interrupt flag
bool running = true;
void raiseFlag(int param)
{
  running = false;
}

int main(){
	// The constructor simply takes the IP address of the Robot
	RTDEControlInterface rtde_control("192.168.1.53");
	
	//User input for varibles for pyramid
	std::cout << "Enter grip height "; 
	float grip_h;
        std::cin >> grip_h;
        std::cout<<std::endl;
        std::cout << "Enter pile difference "; 
	float pile_diff;
        std::cin >> pile_diff;
        std::cout<<std::endl;
	std::cout << "Enter number of cups "; 
	int cupn;
        std::cin >> cupn;
        std::cout<<std::endl;
        std::cout << "Enter cup height "; 
	float cuph;
        std::cin >> cuph;
        std::cout<<std::endl;
	std::cout << "Enter cup diameter "; 
	float cupd;
        std::cin >> cupd;
        std::cout<<std::endl;
	std::cout << "Enter space between cups "; 
	float cupspace;
        std::cin >> cupspace;
        std::cout<<std::endl;
	
	//Creation of varibles for pyramid
	//float grip_h = 0.08;
    	//float pile_diff = 0.011;
    	//int cupn = 10;
	//float cuph = 0.108;
	//float cupd = 0.08;
	//float cupspace = 0.02;
	std::vector<Vec> positions = pyramidAllCups();
   	std::vector<Vec> bunke = pile(grip_h,cupn, pile_diff);
	
	//Creation of varibles for FK_func
	double P_tmp[3] = {-0.15, 0.15, 0.240};
	double theta = M_PI/2;
	double theta1 = 0;
    	double outputArg1[3];
  	double outputArg2[3];
    	
    	//Creation of varibles for frames  // Origin er i millimeter
    	double cf[3]={0.5,0,0};
    	double sf[3]={0.025,0.025,0};
    	
    	//Lifted point
    	Vec bp(0, 0, 0.17);
    	
    	//Naming Gripper
    	Gripper bigbertha;
    	
    	// Initialize function 'FK_function' input arguments.
    	// Initialize function input argument 'P'.
    	// Call the entry-point 'FK_function'.
    	fkfunc(P_tmp, cf, theta1, outputArg1, outputArg2);
    	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
    	
	// Stack argument is the pose 6d vector followed by speed and acceleration
	//safe position move
	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.1, 0.2);
	
	//Creation of pyramid
	for(int i = 0; i < cupn; i++)
    {
  	//Above stack
  	Vec bt = bunke[i]+bp;
  	
  	//Above point
  	Vec pt = positions[i]+bp;
  	
  	//print z axis value
  	std::cout<<"Above "<<bt.ar[2]<<" stack "<<bunke[i].ar[2]<<std::endl;
  	
  	//Above stack
  	std::cout<<"Above stack"<<std::endl;
  	fkfunc(bt.ar, sf, theta1, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.1, 0.2);
  	
  	//Stack
  	std::cout<<"stack"<<std::endl;
  	fkfunc(bunke[i].ar, sf, theta1, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.1, 0.2);
  	//Closing of gripper
  	bigbertha.gClose();
  	
  	//Above stack
  	std::cout<<"Above stack"<<std::endl;
  	fkfunc(bt.ar, sf, theta1, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.1, 0.2);
  	
  	//Safepoint
  	std::cout<<"Safe point"<<std::endl;
  	fkfunc(P_tmp, cf, theta1, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.1, 0.2);
  	
  	//Above point
  	std::cout<<"Above point"<<std::endl;
  	fkfunc(pt.ar, cf, theta, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.1, 0.2);
  	
  	//point
  	std::cout<<"Point"<<std::endl;
  	fkfunc(positions[i].ar, cf, theta, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.1, 0.2);
  	//Opening of gripper
  	bigbertha.gOpen();
  	
  	//Above point
  	std::cout<<"Above Point"<<std::endl;
  	fkfunc(pt.ar, cf, theta, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.05, 0.2);
  	
  	//Safepoint
  	std::cout<<"Safepoint"<<std::endl;
  	fkfunc(P_tmp, cf, theta1, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.05, 0.2);
  	
    }
	return 0;
}
