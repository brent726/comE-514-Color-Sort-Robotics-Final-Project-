

// robot move method.cpp
//functions for robotic arm movement in picking and throwing the caps
//owner: brent group  10/13/16

#include "stdafx.h"
#include "serialCom.h"
#include "robotSupport.h"
#include <windows.h>
#include <string>
void pickC1()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorCol1[4] = {1190,1275,2375,1050};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorCol1);
		robot.wait();
		robot.moveToolArm(1200);
		robot.wait();
		robot.disconnectPort();
}

void pickC2()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorCol2[4] = {1425,1275,2375,1000};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorCol2);
		robot.wait();
		robot.moveToolArm(1200);
		robot.wait();
		robot.disconnectPort();
}

void pickC3()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorCol3[4] = {1600,1275,2375,1000};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorCol3);
		robot.wait();
		robot.moveToolArm(1200);
		robot.wait();
		robot.disconnectPort();
}

void pickC4()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorCol4[4] = {1825,1250,2375,1075};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorCol4);
		robot.wait();
		robot.moveToolArm(1200);
		robot.wait();
		robot.disconnectPort();
}

void pickC5()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorCol5[4] = {1950,1150,2300,1225};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorCol5);
		robot.wait();
		robot.moveToolArm(1200);
		robot.wait();
		robot.disconnectPort();
}

//functions for throwing the caps
void throwB1()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorBin1[4] = {1400,975,1700,1300};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorBin1);
		robot.wait();
		robot.moveToolArm(1900);
		robot.wait();
		robot.disconnectPort();
}

void throwB2()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorBin2[4] = {1550,975,1700,1250};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorBin2);
		robot.wait();
		robot.moveToolArm(1900);
		robot.wait();
		robot.disconnectPort();
}

void throwB3()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorBin3[4] = {1700,975,1700,1250};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorBin3);
		robot.wait();
		robot.moveToolArm(1900);
		robot.wait();
		robot.disconnectPort();
}

// for resetting the robotic arm
void reset()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorReset[4] = {1500,2100,2400,700};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorReset);
		robot.wait();
		robot.disconnectPort();
}

//for initialization
void startformation()
{
	int channels[5] = {3,2,1,0};
	int endChannel =4;
    int coorStart[4] = {1500,2100,2400,700};
	robotSupport robot;
	
	if (robot.connectPort()) cout << "robot connected" << endl;
		robot.setJoints(4, channels);
		robot.setToolArm(4);
		robot.moveJoints(4,coorStart);
		robot.wait();
		robot.moveToolArm(1900);
		robot.wait();
		robot.disconnectPort();

}
