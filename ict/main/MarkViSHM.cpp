// MarkViSHM.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#include <windows.h> // should be defined for the first time before others
#include "MarkerDet_Bluetooth1.h"
#include "MarkerDet_Bluetooth2.h"
//#include "MCL.h"
#include "SerialPort.h"
#include "stdafx.h"
#include <stdio.h>
#include <process.h>  //For Thread
#include <direct.h>
#include <iostream>
#include <fstream>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")
#define PORT 9999
#define IP     "192.168.0.5"  //tablet
//#define IP     "192.168.0.50"  //notebook


CMarkerDet_B1 MarkerDet1,  MarkerDet2;

int thread1 = 0;
int thread2 = 0;

char total_folder_name[50];

int thread1_flag =0;
int thread2_flag =0;


unsigned __stdcall MyThread1(LPVOID arg);
unsigned __stdcall MyThread2(LPVOID arg);


int data_sort_flag1;
int data_sort_flag2;
CMarkerDet_B1 left_variable;
CMarkerDet_B2 right_variable;

WSADATA wsaData; 
SOCKET hSocket; 


FILE *right_file;
FILE *right_marker1_file;
FILE *right_marker2_file;

FILE *total_result_file;
FILE *left_time;
FILE *right_time;
int left_detected;
int right_detected;


CSerialPort cSerialPort_left;
CSerialPort cSerialPort_right;

 LARGE_INTEGER Frequency;
 LARGE_INTEGER BeginTime_left;
 LARGE_INTEGER Endtime_left;
 LARGE_INTEGER BeginTime_right;
 LARGE_INTEGER Endtime_right;
 char file_name_left[50];
 char file_name_right[50];
 FILE *data_save_left;
 FILE *data_save_right;


int _tmain(int argc, _TCHAR* argv[])
{
	//TCPIP
	#if TCPIP
    SOCKADDR_IN    servAddr; 
    if(WSAStartup(MAKEWORD(2,2), &wsaData) !=0)
		printf("WSAStartup() error!");
	//creat a socket
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
     if(hSocket == INVALID_SOCKET) 
		 printf("hSocket() error");
    
    memset(&servAddr, 0 , sizeof(servAddr));
     servAddr.sin_family = AF_INET; 
    servAddr.sin_addr.S_un.S_addr = inet_addr(IP); 
    servAddr.sin_port = htons(PORT); 
	//connect server
    if(connect(hSocket, (SOCKADDR*)&servAddr,
         sizeof(servAddr)) == SOCKET_ERROR) 
		 printf("connect() error");
	else
	printf("connect() success");
#endif
	//creat folder
	SYSTEMTIME time;
	GetSystemTime(&time);
	sprintf(total_folder_name,"./FIELDTEST_data/%02d%02d%02d",time.wHour,time.wMinute,time.wSecond);
	mkdir(total_folder_name);
	sprintf_s(file_name_left,"./%s/data_left.txt",total_folder_name);
	sprintf_s(file_name_right,"./%s/data_right.txt",total_folder_name);

	
	//bluetooth port left camera
	cSerialPort_left.portNumber = "COM1";
	cSerialPort_left.baudrate = CBR_115200;
	cSerialPort_left.dataBits = 8;
	cSerialPort_left.stopBits = ONESTOPBIT;
	cSerialPort_left.parity = NOPARITY;

	left_variable.OnOpenPort((WPARAM)&cSerialPort_left,NULL);
 
	//bluetooth port right camera
	cSerialPort_right.portNumber = "COM2";
	cSerialPort_right.baudrate = CBR_115200;
	cSerialPort_right.dataBits = 8;
	cSerialPort_right.stopBits = ONESTOPBIT;
	cSerialPort_right.parity = NOPARITY;

	right_variable.OnOpenPort((WPARAM)&cSerialPort_right,NULL);

	QueryPerformanceFrequency( &Frequency );
	int check_thread1[2] = {0,};

	//thread left camera
	unsigned ThreadID1;
	HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, MyThread1, (LPVOID)&check_thread1, 0, &ThreadID1);
	if(hThread1 == NULL) return -1;
	//CloseHandle(hThread1);

	//thread right camera
	int check_thread2[2] = {0,};
	unsigned ThreadID2;
	HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, MyThread2, (LPVOID)&check_thread2, 0, &ThreadID2);
	if(hThread2 == NULL) return -1;
	//CloseHandle(hThread2);
	
	int recv_data;
	recv_data=0;

	while(1)
	{

#if TCPIP
		recv(hSocket, (char*)&recv_data, sizeof(recv_data) -1 ,0);
		// re-connect if receive data 2 from server
		if(recv_data==2) 
		{
			while(1)
			{					
				if(WSAStartup(MAKEWORD(2,2), &wsaData) !=0)
				printf("WSAStartup() error!");
 
				hSocket = socket(PF_INET, SOCK_STREAM, 0);
				if(hSocket == INVALID_SOCKET) 
				printf("hSocket() error"); 

				memset(&servAddr, 0 , sizeof(servAddr));
				servAddr.sin_family = AF_INET; 
				servAddr.sin_addr.S_un.S_addr = inet_addr(IP); 
				servAddr.sin_port = htons(PORT); 
				//re-connect with server
				if(connect(hSocket, (SOCKADDR*)&servAddr,
				sizeof(servAddr)) == SOCKET_ERROR) 
				printf("connect() error!"); 
			    Sleep(1000);
				recv(hSocket, (char*)&recv_data, sizeof(recv_data) -1 ,0);
				
				if(recv_data==1)
				{
					break;
				}
			}	
		
		}
#endif
	    //thread termination
		if(cvWaitKey(10000) == 'q')
		{
			DWORD dwExitCode1=0;
			::GetExitCodeThread(hThread1, &dwExitCode1);

			if(dwExitCode1 == STILL_ACTIVE)
             {
				 ::TerminateThread(hThread1, 0);
			 	 CloseHandle(hThread1);
			 }
			
			hThread1 = NULL; 
			delete hThread1;

			DWORD dwExitCode2;
			GetExitCodeThread(hThread2, &dwExitCode2);

			if(dwExitCode2 == STILL_ACTIVE)
			{ 
				::TerminateThread(hThread2, 0);
				CloseHandle(hThread2);
			}

			hThread2 = NULL; 
			delete hThread2;

			break;

		}
		
		
	}

	cvDestroyAllWindows();
	
	return 0;
}



unsigned __stdcall MyThread1(LPVOID arg) //for left camera
{

	bool bDetect;
	float x;
	float y;
	float z;
	float roll;
	float pitch;
	float yaw;
	SYSTEMTIME time_left;
	

	while(1)
	{
		data_save_left = fopen(file_name_left, "a+");
		QueryPerformanceCounter( &BeginTime_left ); 
		double elapsed_left =0;
	    double duringtime_left=0;
		double total_time_left=0;
		GetSystemTime(&time_left);
		total_time_left = time_left.wMinute*60+time_left.wSecond+time_left.wMilliseconds*0.001;
		data_sort_flag1=1;
		//receive bluetooth date from left module
		left_variable.data_receive();
		//send data throung TCPIP
		left_variable.data_send(data_sort_flag1,hSocket);
		//data save
		left_variable.GetPoseInfo(&bDetect, &x, &y, &z,&roll,&pitch,&yaw);
#if DATA_SAVE		
		QueryPerformanceCounter( &Endtime_left );
		elapsed_left = Endtime_left.QuadPart- BeginTime_left.QuadPart;
		duringtime_left = (double)elapsed_left / (double)Frequency.QuadPart;
		fprintf(data_save_left, "%d,%f,%f,%d,%f,%f,%f,%f,%f,%f\n",data_sort_flag1,duringtime_left*1000,total_time_left,bDetect,x,y,z,roll,pitch,yaw);
		fclose(data_save_left);
#endif
	}
	
	return 0;

}


unsigned __stdcall MyThread2(LPVOID arg) //for right camera
{
	bool bDetect;
	float x;
	float y;
	float z;
	float roll;
	float pitch;
	float yaw;
	SYSTEMTIME time_right;
	
	while(1)
	{   
		
		data_save_right = fopen(file_name_right, "a+");
		QueryPerformanceCounter( &BeginTime_right); 
		double elapsed_right =0;
	    double duringtime_right =0;
		double total_time_right=0;
		GetSystemTime(&time_right);
		total_time_right = time_right.wMinute*60+time_right.wSecond+time_right.wMilliseconds*0.001;
		//printf("thread2\n");
		data_sort_flag2=2;
		//receive bluetooth date from right module
	    right_variable.data_receive();
		//send data throung TCPIP
		right_variable.data_send(data_sort_flag2,hSocket);
		//data save
		right_variable.GetPoseInfo(&bDetect, &x, &y, &z,&roll,&pitch,&yaw);
#if DATA_SAVE	
		QueryPerformanceCounter( &Endtime_right );
		elapsed_right = Endtime_right.QuadPart- BeginTime_right.QuadPart;
		duringtime_right = (double)elapsed_right / (double)Frequency.QuadPart;
		fprintf(data_save_right, "%d,%f,%f,%d,%f,%f,%f,%f,%f,%f\n",data_sort_flag2,duringtime_right*1000,total_time_right,bDetect,x,y,z,roll,pitch,yaw);
		fclose(data_save_right);
#endif
	}
	
	return 0;

}

