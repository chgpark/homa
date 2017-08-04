#ifndef _WINSET_H_
#define _WINSET_H_

typedef struct		s_OVERLAPPED
{
	unsigned long			Internal;
	unsigned long			InternalHigh;
	union
	{
		struct
		{
			unsigned long	Offset;
			unsigned long	OffsetHigh;
		};
		void			*Pointer;
	};
	void				*hEvent;
}			OVERLAPPED, *LPOVERLAPPED;

typedef struct		s_COMMTIMEOUTS
{
	unsigned long			ReadIntervalTimeout;
	unsigned long			ReadTotalTimeoutMultiplier;
	unsigned long			ReadTotalTimeoutConstant;
	unsigned long			WriteTotalTimeoutMultiplier;
	unsigned long			WriteTotalTimeoutConstant;
}			COMMTIMEOUTS, *LPCOMMTIMEOUTS;

typedef struct		s_DCB
{
	unsigned long			DCBlength;
	unsigned long			BaudRate;
	unsigned long			fBinary  :1;
	unsigned long			fParity  :1;
	unsigned long			fOutxCtsFlow  :1;
	unsigned long			fOutxDsrFlow  :1;
	unsigned long			fDtrControl  :2;
	unsigned long			fDsrSensitivity  :1;
	unsigned long			fTXContinueOnXoff  :1;
	unsigned long			fOutX  :1;
	unsigned long			fInX  :1;
	unsigned long			fErrorChar  :1;
	unsigned long			fNull  :1;
	unsigned long			fRtsControl  :2;
	unsigned long			fAbortOnError  :1;
	unsigned long			fDummy2  :17;
	unsigned short			wReserved;
	unsigned short			XonLim;
	unsigned short			XoffLim;
	unsigned char			ByteSize;
	unsigned char			Parity;
	unsigned char			StopBits;
	char				XonChar;
	char				XoffChar;
	char				ErrorChar;
	char				EofChar;
	char				EvtChar;
	unsigned short			wReserved1;
} DCB, *LPDCB;
#endif
