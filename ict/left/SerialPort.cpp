
#include "StdAfx.h"
#include "SerialPort.h"

#define SERIAL_BUFFER_SIZE			65535

CSerialPort::CSerialPort(void)
{
	portNumber = "";
	baudrate = 0;
	dataBits = 0;
	stopBits = 0;
	parity = 0;
}

CSerialPort::CSerialPort(DWORD baudrate) 
{
	this->baudrate = baudrate;
}

CSerialPort::CSerialPort(CString portNumber, DWORD baudrate, BYTE dataBits, BYTE stopBits, BYTE parity)
{
	this->portNumber = portNumber.GetString();
	this->baudrate = baudrate;
	this->dataBits = dataBits;
	this->stopBits = stopBits;
	this->parity = parity;
}

CSerialPort::~CSerialPort(void)
{
}

BOOL CSerialPort::OpenPort(int readIntervalTimeout) 
{
	COMMTIMEOUTS timeouts;
	DCB dcb;
	
	osRead.Offset = 0;
	osRead.OffsetHigh = 0; 
	if ( !(osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) ) {
		return FALSE;
	}

	osWrite.Offset = 0;
	osWrite.OffsetHigh = 0;
	if (! (osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL))) {
		return FALSE;
	}

	hComm = CreateFile("//./"+this->portNumber, GENERIC_READ | GENERIC_WRITE, 0, NULL,
							  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
							  NULL);

/*	if (hComm == (HANDLE)-1) {
		AfxMessageBox("Failed to Connect Comm port", MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	*/

	// Set Port Status
	// config EV_RXCHAR event
	SetCommMask(hComm, EV_RXCHAR);
	SetupComm(hComm, SERIAL_BUFFER_SIZE, SERIAL_BUFFER_SIZE);

	// config timeout
	timeouts.ReadIntervalTimeout = readIntervalTimeout;//0xFFFFFFFF;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	
	timeouts.WriteTotalTimeoutMultiplier = 2*CBR_9600 / this->baudrate;
	timeouts.WriteTotalTimeoutConstant = 0;

	SetCommTimeouts( hComm, &timeouts);

	//config DCB
	dcb.DCBlength = sizeof(DCB);
	GetCommState(hComm, &dcb);
	
	dcb.BaudRate = this->baudrate;
	dcb.ByteSize = this->dataBits;
	dcb.StopBits = this->stopBits;
	dcb.EvtChar = 0x02;

	if( !SetCommState( hComm, &dcb) )	 {
		return FALSE;
	}

	return TRUE;
}

BOOL CSerialPort::ClosePort()
{
	if ( !SetCommMask(hComm, 0) ) {
		return FALSE;
	}
	
	if ( !CloseHandle(hComm) ) {
		return FALSE;
	}

	return TRUE;
}