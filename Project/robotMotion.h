#include <iostream>
#include <list>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "SerialCom.h"

using namespace std;

class robotMotion
{
	private:
		std::list<int> jointChannels;
		int endEffectorChannel;
		SerialCom comm;
		HANDLE hComm;
		bool openPort;
		
	public:
		void setJointChannels(int num,int setChannels[]);
		void setEndEffectorChannel(int setChannel);
		bool moveArm(int num,double angles[]);
		
		void initializeARM(void);
		bool endEffector(int pos);
		
		bool connectPort(void);
		bool disconnectPort(void);
		void forwardKinematics(int num,double angles[]);
		robotMotion(void);
		~robotMotion(void);
};
