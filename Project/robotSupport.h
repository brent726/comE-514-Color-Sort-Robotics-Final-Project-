#pragma once
//Main lnx5 robotic arm controller


#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "SerialCom.h"

using namespace std;

class robotSupport
{
private:
	
	std::list<int> jointChannels; //holds the number of joints in the arm
	int toolChannel;
	SerialCom comm;
	HANDLE hComm;
	bool status;

public:
	//methods to connect to ports
	bool connectPort(void);
	bool disconnectPort(void);

	//pre-movement functions
	void setJoints(int numberJoints, int jointNumber[]);
	void setToolArm(int setChannel);

	//main movement functions
	bool moveJoints(int joints, int angles[]);
	bool moveToolArm(int angle);
	bool wait();

	robotSupport(void);
	


};


