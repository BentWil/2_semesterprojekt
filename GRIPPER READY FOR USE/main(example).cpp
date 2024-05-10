
#include "gripper.h"
// use gripperDummy.h if you want to test without gripper.'

// install SQLITE and QT-sqlite driver: 
// 		sudo apt install sqlite3
// 		sudo apt install libqt5sql5-sqlite

// HAVE THIS IN CMAKE.TXT for non :
// 		find_package(Qt5Sql REQUIRED)
//		target_link_libraries("projectName" Qt5::Core Qt5::Sql)



int main()
{

    Gripper bigbertha;
    

    bigbertha.gClose();


    //bigbertha.gOpen();


    return 0;
}
