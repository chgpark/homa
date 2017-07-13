#pragma once
#include <windows.h>
#include <atlstr.h>
class CSerialPort
{
private:
	HANDLE hComm;
	OVERLAPPED	osRead, osWrite;
public:
	CString portNumber;
	DWORD baudrate;
	BYTE dataBits;
	BYTE stopBits;
	BYTE parity;

public:
	CSerialPort(void);	
	~CSerialPort(void);
	CSerialPort(DWORD baudrate);
	CSerialPort(CString portNumber, DWORD baudrate, BYTE dataBits, BYTE stopBits, BYTE parity);
	BOOL OpenPort(int readIntervalTimeout = 100);
	BOOL ClosePort();
	HANDLE GethComm() { return hComm; }
	OVERLAPPED* GetOsRead() { return &osRead; }
	OVERLAPPED* GetOsWrite() { return &osWrite; }
};
