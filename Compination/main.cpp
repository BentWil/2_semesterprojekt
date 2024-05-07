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
#include "../GRIPPER READY FOR USE/gripperDummy.h"
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
	//RTDEControlInterface rtde_control("192.168.1.54");
	//Creation of varibles for Pyriamid
	float grip_h = 0.05;
    	float pile_diff = 0.03;
    	int cupn = 14;
	float cuph = 0.08;
	float cupd = 0.05;
	float cupspace = 0.02;
	std::vector<Vec> positions = pyramidAllCups();
   	std::vector<Vec> bunke = pile(grip_h,cupn, pile_diff);
	
	//Creation of varibles for FK_func
	double P_tmp[3] = {175, 0, 240};
	double G_org[3] = {0, 500, 0};
	double theta = 0;
    	double outputArg1[3];
  	double outputArg2[3];
    	
    	//Creation of varibles for frames
    	double cf[3]={0,50,0};
    	double sf[3]={25,25,0};
    	
    	//Naming Gripper
    	//Gripper bigbertha;
    	
    	// Initialize function 'FK_function' input arguments.
    	// Initialize function input argument 'P'.
    	// Call the entry-point 'FK_function'.
    	fkfunc(P_tmp, G_org, theta, outputArg1, outputArg2);
    	std::cout<<outputArg1[0]/1000<<" "<<outputArg1[1]/1000<<" "<<outputArg1[2]/1000<<" "<<"output1"<<" " <<outputArg2[0]/1000<<" "<<outputArg2[1]/1000<<" "<<outputArg2[2]/1000<<" "<<"output2";
    	
	// Stack argument is the pose 6d vector followed by speed and acceleration
	//safe position move
	//rtde_control.moveL({output1_data[0], output1_data[1], -output1_data[2], output2[0], output2[1], output2[2]}, 0.05, 0.2);
	/*
	//Creation of pyramid
	for(int i = 0; i < cupn; i++)
    {
  	//Above stack
  	Vec bp(0, 0, 0.17);
  	Vec bt = bunke[i]+bp;
  	
  	//Above point
  	Vec pt = positions[i]+bp;
  	
  	//Above stack
  	Projekfunction(bt.Getarray(), output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
  	
  	//Stack
  	Projekfunction(bunke[i].Getarray(), output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
  	//Closing of gripper
  	//bigbertha.gClose();
  	
  	//Above stack
  	Projekfunction(bt.Getarray(), output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
  	
  	//Safepoint
  	Projekfunction(sp, output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
  	
  	//Above point
  	Projekfunction(pt.Getarray(), output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
  	
  	//point
  	Projekfunction(positions[i].Getarray(), output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
  	//Opening of gripper
  	//bigbertha.gOpen();
  	
  	//Above point
  	Projekfunction(pt.Getarray(), output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
  	
  	//Safepoint
  	Projekfunction(sp, output1_data, *(int(*)[1]) & output1_size, output2);
  	//rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[0], output2[1], output2[2]}, 0.02, 0.2);
    }*/
	return 0;
}
