#include <iostream>
#include <cmath>
#include <limits>
#include </home/kasper/Workplace/Exam/2_semesterprojekt/FK_func/FK_func.cpp>
#include </home/kasper/ur_rtde/include/ur_rtde/rtde_control_interface.h>
#include </home/kasper/ur_rtde/include/ur_rtde/rtde_receive_interface.h>
#include <boost/program_options.hpp>
#include <thread>
#include <chrono>
#include <csignal>
#include <string>
#include <array>
#include <vector>
#include </home/kasper/Workplace/Exam/2_semesterprojekt/PickAndPlace_allCups/pile.h>
#include </home/kasper/Workplace/Exam/2_semesterprojekt/PickAndPlace_allCups/vec.h>
#include </home/kasper/Workplace/Exam/2_semesterprojekt/PickAndPlace_allCups/pyramide.h>
#include </home/kasper/Workplace/Exam/2_semesterprojekt/GRIPPER READY FOR USE/gripper.h>

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
	RTDEControlInterface rtde_control("192.168.1.54");
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
	double sp[3]={0.5, 0.25, 0.25};
    	double output1_data[3];
   	double output2[3];
    	int output1_size;
    	
    	//Naming Gripper
    	Gripper bigbertha;
    	
    	// Initialize function 'FK_function' input arguments.
    	// Initialize function input argument 'P'.
    	// Call the entry-point 'FK_function'.
    	FK_function(sp, output1_data, *(int(*)[1]) & output1_size, output2);
    	
	// Stack argument is the pose 6d vector followed by speed and acceleration
	//safe position move
	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
	
	//Creation of pyramid
	for(int i = 0; i < cupn; i++)
    {
  	//Above stack
  	FK_function(bunke[i]+(0, 0, 0.17), output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
  	
  	//Stack
  	FK_function(bunke[i], output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
  	//Closing of gripper
  	bigbertha.gClose();
  	
  	//Above stack
  	FK_function(bunke[i]+(0, 0, 0.17), output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
  	
  	//Safepoint
  	FK_function(sp, output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
  	
  	//Above point
  	FK_function(positions[i]+(0, 0, 0.17), output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
  	
  	//point
  	FK_function(positions[i], output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
  	//Opening of gripper
  	bigbertha.gOpen();
  	
  	//Above point
  	FK_function(positions[i]+(0, 0, 0.17), output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
  	
  	//Safepoint
  	FK_function(sp, output1_data, *(int(*)[1]) & output1_size, output2);
  	rtde_control.moveL({output1_data[0], output1_data[1], output1_data[2], output2[2], output2[1], output2[0]}, 0.5, 0.2);
    }
	return 0;
}
