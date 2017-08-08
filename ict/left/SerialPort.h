#pragma once

#include "winset.h"
#include <string.h>
#include <stdio.h>


using namespace std;

class		CSerialPort
{
	private:
		void		*hComm;
		OVERLAPPED	osRead, osWrite;
	public:
		string		porNumber;
		unsigned long	baudrate;
		unsigned char	dataBits;
		unsigned char	stopBits;
		unsigned char	parity;

	public:
		CSerialPort();
		~CSerialPort();
		CSerialPort(unsigned long baudrate);
		CSerialPort(string portNumber, unsigned long baudrate, unsigned char dataBits, unsigned char stopBits, unsigned char parity);
		int		OpenPort(int readIntervalTimeout = 100);
		int		ClosePort();
		void		*GethComm() { return hComm; }
		OVERLAPPED	*GetOsRead() { return &osRead; }
		OVERLAPPED	*GetOsWrite() { return &osWrite; }
};
