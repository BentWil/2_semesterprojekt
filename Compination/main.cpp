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
	
	//Defining varibles for user input or standard values for use in pyramid and fk_func
	float grip_h;
	float pile_diff;
	int cupn;
	float cuph;
	float cupd;
	float cupspace;
	double sp[3];
	double theta;
	double theta1;
	double outputArg1[3];
  	double outputArg2[3];
  	double cf[3];
  	double sf[3];
	
	//User choise weather to rund the standard 10 cup program og at user defined program
	std::cout << "Do you wish to run the standard program? Y/N"<< std::endl;
	char choise;
        std::cin >> choise;
	
	if(choise = Y or choise = y){
	//Creation of varibles for pyramid
	grip_h = 0.08;
    	pile_diff = 0.011;
    	cupn = 10;
	cuph = 0.108;
	cupd = 0.08;
	cupspace = 0.02;
	
	//Creation of varibles for FK_func
	sp {-0.15, 0.15, 0.240};
	theta = M_PI/2;
	theta1 = 0;
	cf = {0.5,0,0};
	sf = {0.025,0.025,0};
	};
	
	if(choise = N or choise = n){
	//User input for varibles for pyramid
	std::cout << "All values should be in meter's" << std::endl;
	std::cout << "Enter grip height "; 
        std::cin >> grip_h;
        std::cout<<std::endl;
        
        std::cout << "Enter pile difference "; 
        std::cin >> pile_diff;
        std::cout<<std::endl;
        
	std::cout << "Enter number of cups "; 
        std::cin >> cupn;
        std::cout<<std::endl;
        
        std::cout << "Enter cup height "; 
        std::cin >> cuph;
        std::cout<<std::endl;
        
	std::cout << "Enter cup diameter "; 
        std::cin >> cupd;
        std::cout<<std::endl;
        
	std::cout << "Enter space between cups "; 
        std::cin >> cupspace;
        std::cout<<std::endl;
        
        std::cout << "Enter x value for safepoint "; 
        std::cin >> sp[0];
        std::cout<<std::endl;
        
        std::cout << "Enter y value for safepoint "; 
        std::cin >> sp[1];
        std::cout<<std::endl;
        
        std::cout << "Enter z value for safepoint "; 
        std::cin >> sp[2];
        std::cout<<std::endl;
        
        std::cout << "Enter radian value z rotation of cup frame "; 
        std::cin >> theta;
        std::cout<<std::endl;
        
        std::cout << "Enter x value for cup frame "; 
        std::cin >> cf[0];
        std::cout<<std::endl;
        
        std::cout << "Enter y value for cup frame "; 
        std::cin >> cf[1];
        std::cout<<std::endl;
        
        std::cout << "Enter z value for cup frame "; 
        std::cin >> cf[2];
        std::cout<<std::endl;
        
        std::cout << "Enter radian value z rotation of stack frame "; 
        std::cin >> theta;
        std::cout<<std::endl;
        
        std::cout << "Enter x value for stack frame "; 
        std::cin >> sf[0];
        std::cout<<std::endl;
        
        std::cout << "Enter y value for stack frame "; 
        std::cin >> sf[1];
        std::cout<<std::endl;
        
        std::cout << "Enter z value for stack frame "; 
        std::cin >> sf[2];
        std::cout<<std::endl;
	};
	
	//call pyramid function to find all cup points
	std::vector<Vec> positions = pyramidAllCups();
   	std::vector<Vec> bunke = pile(grip_h,cupn, pile_diff);
    	
    	//Lifted point
    	Vec bp(0, 0, 0.17);
    	
    	//Naming Gripper
    	Gripper bigbertha;
    	
    	// Initialize function 'FK_function' input arguments.
    	// Initialize function input argument 'P'.
    	// Call the entry-point 'FK_function'.
    	fkfunc(sp, cf, theta1, outputArg1, outputArg2);
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
  	fkfunc(sp, cf, theta1, outputArg1, outputArg2);
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
  	fkfunc(sp, cf, theta1, outputArg1, outputArg2);
  	std::cout<<outputArg1[0]<<" "<<outputArg1[1]<<" "<<outputArg1[2]<<" "<<"output1"<<" " <<outputArg2[0]<<" "<<outputArg2[1]<<" "<<outputArg2[2]<<" "<<"output2"<<std::endl;
  	rtde_control.moveL({outputArg1[0], outputArg1[1], outputArg1[2], outputArg2[0], outputArg2[1], outputArg2[2]}, 0.05, 0.2);
  	
    }
	return 0;
}
