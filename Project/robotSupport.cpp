
#include "stdafx.h"
#include "robotSupport.h"

#include <windows.h>
#include <string>


robotSupport::robotSupport(void)
{
	hComm = NULL;
	status = false;
};

bool robotSupport::connectPort(void)
{
	status = comm.SetPort(&hComm, 115200);
	if (status) cout << "connected" << endl; 
	return status;
}

bool robotSupport::disconnectPort(void)
{
	status = comm.ClosePort(&hComm);
	if(!status)cout << "disconnected" << endl;
	return status;
}

/*
numberJoints = number of joints inside the robot
jointNumber[x] x= number of channels inside the robot
	useful because hardware hardcodes the channel number inside the robot

*/

void robotSupport::setJoints(int numberJoints, int jointNumber[])
{
	int x;

	for (x = 0; x<numberJoints; x++)
	{
		jointChannels.push_back(jointNumber[x]);
	}
}

void robotSupport::setToolArm(int setChannel)
{	
	toolChannel = setChannel;
}

//moves from joints down
bool robotSupport::moveJoints(int joints, int angles[])
{
	std::list<int>::iterator i;
	DWORD sizeWritten;
	char position[35], pulse[35]; //stores joing channel; stores joint angle
	int max=joints; //for # spacing logic
	char inst[200]="";

	for (i=jointChannels.begin(); (i!=jointChannels.end()) && (joints--> 0); i++)
	{
		
		_itoa((angles[joints]), pulse, 10);
		_itoa(*i,position,10);
		
		if(joints==max-1)
			strcat(inst, "#");
		else
			strcat(inst, " #");

		strcat(inst, position);
		strcat(inst, " P");
		strcat(inst, pulse);
		strcat(inst, " S1000");
	}
	
		strcat(inst, " <cr>\r\n"); //add remaining comands
	if (status)
	{
		cout << inst << endl;
		return comm.SendData(&hComm, &sizeWritten, inst);
	}
	else
	{
		return status;
	}

}

bool robotSupport::moveToolArm(int angle)
{
	DWORD sizeWritten;
	char position[35], pulse[35]; //stores joing channel; stores joint angle
	char inst[200] = "";

	_itoa(angle, pulse, 10);
	_itoa(toolChannel, position, 10);

	strcat(inst, "#");
	strcat(inst, position);
	strcat(inst, " P");
	strcat(inst, pulse);
	strcat(inst, " S750");
	strcat(inst, " <cr>\r\n"); //add remaining comands
	if (status)
	{
		cout << inst << endl;
		return comm.SendData(&hComm, &sizeWritten, inst);
	}
	else
	{
		return status;
	}
}

bool robotSupport::wait()
{

	std::string chk, stream;

	char *query, inst[20] = " Q <cr>\r \n";
	DWORD sizeWritten;

	query = (char*)malloc(sizeof(char) * 4);
	comm.SendData(&hComm, &sizeWritten, inst);
	chk = "+";
	while (chk == "+")
	{
		if (comm.SendData(&hComm, &sizeWritten, inst))
		{
			Sleep(1000);
			if (comm.ReadData(&hComm, &sizeWritten, &query))
			{
				chk = query[0];
				cout << chk << endl;
			}

		}
	}
	return false;
}