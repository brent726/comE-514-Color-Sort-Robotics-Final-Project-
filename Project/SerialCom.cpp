/*
	Includes all methods to communicate with the SSC-32 controller in the LynX 5 robotic arm
	-basically enables you to send string commands to the controller
	-used to build the robotMotion API


*/

#include "stdafx.h"
#include "SerialCom.h"


//Constructor
SerialCom::SerialCom(void)
{

}

//Destructor
SerialCom::~SerialCom(void)
{
	
}

//set the com mannually here
bool SerialCom::SetPort(HANDLE *m_hComm, int Baudrate)
{
	DCB m_dcb;
	BOOL port_ready;
	COMMTIMEOUTS m_timeOuts;

	LPCWSTR str = L"COM2";
	*m_hComm = CreateFile(str, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING,0,NULL);
	if(*m_hComm == INVALID_HANDLE_VALUE)return false;

	port_ready = SetupComm(*m_hComm, 128, 128);
	port_ready = GetCommState(*m_hComm, &m_dcb);
	m_dcb.BaudRate = Baudrate;
	m_dcb.ByteSize = 8;
	m_dcb.Parity = NOPARITY;
	m_dcb.StopBits = ONESTOPBIT;
	m_dcb.fAbortOnError = TRUE;
	port_ready = SetCommState(*m_hComm, &m_dcb);

	port_ready = GetCommTimeouts(*m_hComm, &m_timeOuts);
	m_timeOuts.ReadIntervalTimeout = 50;
	m_timeOuts.ReadTotalTimeoutConstant = 50;
	m_timeOuts.ReadTotalTimeoutMultiplier = 10;
	m_timeOuts.WriteTotalTimeoutConstant = 50;
	m_timeOuts.WriteTotalTimeoutMultiplier = 50;
	port_ready = SetCommTimeouts(*m_hComm, &m_timeOuts);

	return port_ready;
}


bool SerialCom::SendData(HANDLE *hComm, DWORD *sizeWritten, char * data)
{
	bool write;
	int len = strlen(data);

 	write = WriteFile(*hComm, data, len, sizeWritten, NULL);
	if(write)return true;

	else return false;
}


bool SerialCom::ReadData(HANDLE *hComm,DWORD *sizeWritten, char**data)
{
	bool read;

	int len = strlen(*data);

	read = ReadFile(*hComm, *data,len,sizeWritten,NULL);

	if (read) return true;
	return false;
}


bool SerialCom::ClosePort(HANDLE * m_hComm)
{

	bool closed;

	closed = CloseHandle(*m_hComm);
	return closed;
}
