
#include "MarkerDet_Bluetooth1.h"

#include <stdio.h>
#include <math.h>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

IplConvKernel *m_element = cvCreateStructuringElementEx(3, 3, 1, 1, CV_SHAPE_RECT, NULL);
int picnum = 0;
char buff[20];
char buff1[20];
char buff2[20];
char buff3[20];
char buff4[20];
char buff5[20];



CMarkerDet_B1::CMarkerDet_B1(void)
{

}

CMarkerDet_B1::~CMarkerDet_B1(void)
{


	cvDestroyAllWindows();

}


int CMarkerDet_B1::GetPoseInfo(bool *bDetect, float* x, float* y, float* z, float* roll, float* pitch, float* yaw)
{

	    *bDetect=pose_info.bDetect;
		*x = pose_info.x;
		*y = pose_info.y;
		*z = pose_info.z;
		*roll = pose_info.roll;
		*pitch = pose_info.pitch;
		*yaw = pose_info.yaw;

		
	
	return 0;
}

void CMarkerDet_B1::OnOpenPort(WPARAM wParam, LPARAM lParam)
{
	pCSerialPort = (CSerialPort*)wParam;

	if (OpenPort() == TRUE) {
						
	} else {
		ClosePort();
	}
}

BOOL CMarkerDet_B1::OpenPort() 
{
	if ( pCSerialPort->OpenPort(0) ) {
		isConnected = TRUE;
		hComm = pCSerialPort->GethComm();
		osRead = pCSerialPort->GetOsRead();
		osWrite = pCSerialPort->GetOsWrite();

		/*share_data->hComm=hComm;
		share_data->isConnected=isConnected;
		share_data->osRead=osRead;
		share_data->osWrite=osWrite;*/

	} else {
		isConnected = FALSE;
	    //share_data->isConnected=isConnected;
	}

	return TRUE;
}

void CMarkerDet_B1::ClosePort() 
{
	
	if ( pCSerialPort->ClosePort() ) {
		isConnected = FALSE;
	} 	
}

DWORD CMarkerDet_B1::WriteComm(BYTE *pBuff, DWORD bufferSize)
{
	DWORD dwWritten, error, errorFlag;
	COMSTAT comstat;
	
	if( !isConnected ) {
		return FALSE;
	}
	
	if( !WriteFile( hComm, pBuff, bufferSize, &dwWritten, osWrite)) {
		// Is exist data to write?
		if (GetLastError() == ERROR_IO_PENDING) {
			while (! GetOverlappedResult( hComm, osWrite, &dwWritten, TRUE)) {
				error = GetLastError();
				if (error != ERROR_IO_INCOMPLETE) {
					ClearCommError( hComm, &errorFlag, &comstat);
					break;
				}
			}
		} else 	{
			dwWritten = 0;
			ClearCommError( hComm, &errorFlag, &comstat);
		}
	}

	return dwWritten;
}



DWORD CMarkerDet_B1::WatchComm_Scan()
{
	DWORD serialEvent;
	OVERLAPPED os;
	BOOL isConfig = TRUE;
	DWORD countReadByte;
	int proced_return;
	proced_return=1;
	// Init event, os
	memset(&os, 0, sizeof(OVERLAPPED));
	if ( !(os.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) ) {
		isConfig = FALSE;
	}

	// Config event mask
	if( !SetCommMask( hComm, EV_RXCHAR) ) {
	   isConfig = FALSE;
	}

	if ( !isConfig ) {
		printf("Error Creating WatchComm.");
		return FALSE;
	}

	while((isConnected == TRUE) && proced_return) {
		serialEvent = 0;

		// Wait for Read data
		WaitCommEvent(hComm, &serialEvent, NULL);

		// Get Data
		if ((serialEvent & EV_RXCHAR) == EV_RXCHAR) {
			
			do {

				countReadByte = ReadComm(&buff, 1);
				if (countReadByte > 0) 
				{   //one bit is received
					proced_return = ProcessMarker1Data(buff);
				}

			} while(countReadByte*(proced_return));

		}
	}
	return TRUE;
}

DWORD CMarkerDet_B1::ReadComm(BYTE *pBuff, DWORD bufferSize) 
{
	DWORD dwRead, error, errorFlag;
	COMSTAT comstat;

	ClearCommError(hComm, &errorFlag, &comstat);
	if (!isConnected) {
		return FALSE;
	}

	// Is exist data to read?
	dwRead = comstat.cbInQue;
	if (dwRead > 0) {
		if ( !ReadFile(hComm, pBuff, bufferSize, &dwRead, osRead) ) {

			// if remain data
			if (GetLastError() == ERROR_IO_PENDING) {
				// wait for timeout
				while (!GetOverlappedResult(hComm, osRead, &dwRead, TRUE)) {
					error = GetLastError();
					if (error != ERROR_IO_INCOMPLETE) {
						ClearCommError(hComm, &errorFlag, &comstat);
						break;
					}

				} // end while
			} else {
				dwRead = 0;
				ClearCommError(hComm, &errorFlag, &comstat);
			}
		}
	} // end if

	return dwRead;
}


BOOL CMarkerDet_B1::ProcessMarker1Data(BYTE _b)
{
			
	//receive data
	rx[tmp_idx]=_b;
	int temp_flag_comm=0;
	//x ,y, z
	if(rx[tmp_idx-ONE_LINE_MAX_BINARY+1]==STX_UPPER && rx[tmp_idx-ONE_LINE_MAX_BINARY+2]==STX_LOWER_ROW1 && rx[tmp_idx-1]==ETX_UPPER && rx[tmp_idx]==ETX_LOWER)
	{


		    // bit data are translated to 6-DOF
		    // 6-DOF is negative
			if((int)((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+1]>>7))==1)
			{	
				 pose_info.x=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+1]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+2]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+3]))-8388608))/1000;
				 pose_info.x=-pose_info.x;
			}
			// 6-DOF is positive
			else
			{
				pose_info.x=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+1]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+2]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+3]))))/1000;
			}
		
			if((int)((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+4]>>7))==1)
			{	
				 pose_info.y=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+4]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+5]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+6]))-8388608))/1000;
				 pose_info.y=-pose_info.y;
			}
			else
			{
				pose_info.y=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+4]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+5]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+6]))))/1000;
			}

			if((int)((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+7]>>7))==1)
			{	
				 pose_info.z=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+7]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+8]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+9]))-8388608))/1000;
				 pose_info.z=-pose_info.z;
			}
			else
			{
				pose_info.z=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+7]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+8]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+9]))))/1000;
			}

		

		
		count_flag_first=1;
		temp_first=1;
		sequence[0]=1;
	
	}

	//roll ,pitch, yaw
	else if( temp_first==1 && rx[tmp_idx-ONE_LINE_MAX_BINARY+1]==STX_UPPER && rx[tmp_idx-ONE_LINE_MAX_BINARY+2]==STX_LOWER_ROW2 && rx[tmp_idx-1]==ETX_UPPER && rx[tmp_idx]==ETX_LOWER)
	{

		    if((int)((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+1]>>7))==1)
			{	
				 pose_info.roll=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+1]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+2]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+3]))-8388608))/100;
				 pose_info.roll=-pose_info.roll;
			}
			else
			{
				pose_info.roll=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+1]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+2]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+3]))))/100;
			}
		
			if((int)((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+4]>>7))==1)
			{	
				 pose_info.pitch=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+4]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+5]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+6]))-8388608))/100;
				 pose_info.pitch=-pose_info.pitch;
			}
			else
			{
				pose_info.pitch=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+4]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+5]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+6]))))/100;
			}

			if((int)((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+7]>>7))==1)
			{	
				 pose_info.yaw=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+7]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+8]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+9]))-8388608))/100;
				 pose_info.yaw=-pose_info.yaw;
			}
			else
			{
				pose_info.yaw=((float)(((rx[4+tmp_idx-ONE_LINE_MAX_BINARY+7]<<16) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+8]<<8) | (rx[4+tmp_idx-ONE_LINE_MAX_BINARY+9]))))/100;
			}

			pre_time= ((float)(rx[tmp_idx-ONE_LINE_MAX_BINARY+3]<<8 | rx[tmp_idx-ONE_LINE_MAX_BINARY+4]))/1000;

		count_flag_first=2;
		temp_first=2;
	    sequence[1]=1;
	}
	
	//printf("=================== 1 ====================\n");
	//printf("pose_info.x = %f\n", pose_info.x);
	//printf("pose_info.y = %f\n", pose_info.y);
	//printf("pose_info.z = %f\n", pose_info.z);
	//printf("pose_info.roll = %f\n", pose_info.roll);
	//printf("pose_info.pitch = %f\n", pose_info.pitch);
	//printf("pose_info.yaw = %f\n", pose_info.yaw);


	if(count_flag_first==2)

	{
		count_flag_first=0;
		tmp_idx = 0;
		temp_first=0;

		return 0;
	}

	
		tmp_idx++;

		if(count_flag_first==1)
		{
			tmp_idx = 0;
			count_flag_first=0;
		}

	if(tmp_idx == 199) tmp_idx = 0;
		return 1;

}

void CMarkerDet_B1::data_receive()
{
    //receive bluetooth data by bit
	if (WatchComm_Scan() == FALSE) {
			ClosePort();}
}


void CMarkerDet_B1::data_send(int Data_sort_flag,SOCKET HSocket)
{
	
#if TCPIP

	int sbyte;
	int len = sizeof (pose_info);

	
	pose_info.pose_flag = Data_sort_flag;
	
	if(pose_info.x==0 && pose_info.y==0 && pose_info.z==0 && pose_info.roll==0 && pose_info.pitch==0 && pose_info.yaw==0)
		//if 6-DOF is not calculated
		pose_info.bDetect=false;
	else
		pose_info.bDetect=true;
   //send data	
	sbyte=send(HSocket, (char *) &pose_info,len,0);

	printf("==================left_marker_data===================\n");
	printf("left_marker_bDetect=%d\n",pose_info.bDetect);
	printf("left_marker_x=%f\n",pose_info.x);
	printf("left_marker_y=%f\n",pose_info.y);
	printf("left_marker_z=%f\n",pose_info.z);
	printf("left_marker_roll=%f\n",pose_info.roll);
	printf("left_marker_pitch=%f\n",pose_info.pitch);
	printf("left_marker_yaw=%f\n",pose_info.yaw);
	//printf("len=%d sbyte=%d\n",len,sbyte);
	

	if(sbyte != len)
	{
	//	AfxMessageBox("send() error!");
	}
#endif

}

