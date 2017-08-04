#include "SerialPort.h"

#define SERIAL_BUFFER_SIZE	65535

CSerialPort::CSerialPort()
{
	portNumber = "";
	baudrate = 0;
	dataBits = 0;
	stopBits = 0;
	parity = 0;
}

CSerialPort::CSerialPort(unsigned long baudrate)
{
	this->baudrate = baudrate;
}

CSerialPort::CSerialPort(string portNumber, unsigned long baudrate, unsigned char dataBits, unsigned char stopBits, unsigned char parity)
{
	this->portNumber = portNumber.c_str();
	this->baudrate = baudrate;
	this->dataBits = dataBits;
	this->stopBits = stopBits;
	this->parity = parity;
}

CSerialPort::~CSerialPort()
{
}

int CSerialPort::OpenPort(int readIntervalTimeout)
{
	COMMTIMEOUTS	timeouts;
	DCB		dcb;

	osRead.Offset = 0;
	osRead.OffsetHigh = 0;
	if (!(osRead.hEvent = CreateEvent
