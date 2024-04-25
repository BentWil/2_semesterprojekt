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
	
	// First argument is the pose 6d vector followed by speed and acceleration
	//Cup position move
	//rtde_control.moveL({0.346, -0.017, 0.046, 0.120, 2.138, -1.267}, 0.5, 0.2);
	
	//safe position move
	//rtde_control.moveL({0.346, -0.017, 0.233, 0.120, 2.138, -1.267}, 0.05, 0.1);
	return 0;
}
