
#include "stdafx.h"
#include "robotMotion.h"

void robotMotion::setJointChannels(int num,int setChannels[])
{
	int x;
	
	for(x=0;x<num;x++)
	{
		jointChannels.push_back(setChannels[x]);
	}
};

void robotMotion::setEndEffectorChannel(int setChannel)
{
	endEffectorChannel = setChannel;
};

bool robotMotion::moveArm(int num,double angles[]) //in degrees
{
	std::list<int>::iterator i;
	int angle,trans;
	char buffer1[35],buffer2[35];
	std::string stream; 
	DWORD sizeWritten;
	char tab[1024];
	char test[200];
	
	angle = 0;
	
	for(i=jointChannels.begin();(i != jointChannels.end())&&(num-- > 0); ++i)
	{
		trans = (int)angles[angle++];
		//stream = stream + "#" + _itoa_s(*i,buffer1,10) + " P" + _itoa(trans,buffer2,10) + " S750 "; 
		_itoa_s(*i, buffer1, 10);
		_itoa_s(trans, buffer2, 10);
		strcat_s(test, "#");
		strcat_s(test, buffer1);
		strcat_s(test, " P");
		strcat_s(test, buffer2);
		strcat_s(test, " S750");
	}
	
	strcat_s(test, " <cr>\r\n");
	//stream = stream + " <cr> \r \n";
	
	//strcpy(tab,stream.c_str());
	
	if(openPort)
	{
		cout << test << endl;
		return comm.SendData(&hComm,&sizeWritten,test);
	}
	else
	{
		return openPort;
	}
};

void robotMotion::initializeARM()
{
	
};

bool robotMotion::endEffector(int pos)
{

	char buffer1[35],buffer2[35];
	DWORD sizeWritten;
	char tab[1024];
	char test[200];

	_itoa_s(endEffectorChannel, buffer1, 10);
	_itoa_s(pos, buffer2, 10);

	strcat_s(test, "#");
	strcat_s(test, buffer1);
	strcat_s(test, " P");
	strcat_s(test, buffer2);
	strcat_s(test, " S750<cr>\r\n");

	//strcpy(tab,stream.c_str());
	
	if(openPort)
	{
		cout << tab << endl;
		return comm.SendData(&hComm,&sizeWritten,test);
	}
	else
	{
		return openPort;
	}
};


bool robotMotion::connectPort()
{
	openPort = comm.SetPort(&hComm, 115200);
	return openPort;

};


bool robotMotion::disconnectPort(void)
{

	openPort = CloseHandle(&hComm);
	return openPort;
};

//void forwardKinematics(int num,double angles[]);

robotMotion::robotMotion(void)
{
	hComm = NULL;
	openPort = false;
};


robotMotion::~robotMotion(void)
{
	
};