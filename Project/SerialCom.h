#pragma once
#include <windows.h>
#include <string>

class SerialCom
{
	
public:
	
	SerialCom(void);
	~SerialCom(void);
	bool SetPort(HANDLE *, int); //note. set the com manually inside code
	bool SendData(HANDLE * , DWORD * , char * );
	bool ReadData(HANDLE * hComm, DWORD * sizeWritten, char ** data);
	bool ClosePort(HANDLE *);


};

