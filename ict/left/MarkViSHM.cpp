// MarkViSHM.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#include <windows.h> // should be defined for the first time before others
#include "MarkerDet.h"
#include "MCL.h"
#include "SerialPort.h"
#include "stdafx.h"
#include <stdio.h>
#include <process.h>  //For Thread

CMarkerDet MarkerDet1;

int thread1 = 0;
CSerialPort cSerialPort;

char total_folder_name[50];
int thread1_flag =0;
unsigned __stdcall MyThread1(LPVOID arg);
char save_direct[50];
FILE *save_file;
int detected;
float trns[3];
float rot[3];
float trns_filtered[3];
float rot_filtered[3];
float trns_compen_filtered[3];
float rot_compen_filtered[3];

int _tmain(int argc, _TCHAR* argv[])
{
	
	SYSTEMTIME time;
	GetSystemTime(&time);
	sprintf(total_folder_name,"./FIELDTEST_data/%02d%02d%02d",time.wHour,time.wMinute,time.wSecond);
	mkdir(total_folder_name);
	sprintf(save_direct,"%s/result.txt",total_folder_name);
	save_file = fopen(save_direct, "wt");
	
	MarkerDet1.CMarkerDetInit();			// Marker Detection algorithm main
	

	MarkerDet1.CameraPowerOn(1, NULL);			// Camera Power On

	int check_thread1[2] = {0,};
	unsigned ThreadID1;
	HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, MyThread1, (LPVOID)&check_thread1, 0, &ThreadID1);
	if(hThread1 == NULL) return -1;

	//bluetooth port
	cSerialPort.portNumber = "COM7";
	cSerialPort.baudrate = CBR_115200;
	cSerialPort.dataBits = 8;
	cSerialPort.stopBits = ONESTOPBIT;
	cSerialPort.parity = NOPARITY;

	MarkerDet1.OnOpenPort((WPARAM)&cSerialPort,NULL);


while(1)

	{

		if(cvWaitKey(300) == 'q')
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
			
			break;

		}
		
		//adatptiveshould constant
		else if(cvWaitKey(300) == 2490368) //UP
		{
			MarkerDet1.Variable_block=MarkerDet1.Variable_block+10;
			if(MarkerDet1.Variable_block>=255)
			{

				MarkerDet1.Variable_block=255;

			}
		}

		else if(cvWaitKey(300) == 2621440) //DOWN
		{
			MarkerDet1.Variable_block=MarkerDet1.Variable_block-10;

			if(MarkerDet1.Variable_block<=0)
			{
				MarkerDet1.Variable_block=0;
			}

		}

		else if(cvWaitKey(300) == 2424832) //left
		{
			MarkerDet1.Variable_meansubtract=MarkerDet1.Variable_meansubtract+5;

		}

		else if(cvWaitKey(300) == 2555904) //right
		{
			MarkerDet1.Variable_meansubtract=MarkerDet1.Variable_meansubtract-5;

			if(MarkerDet1.Variable_meansubtract<=0)
			{
				MarkerDet1.Variable_meansubtract=0;
			}

		}

	
	}

	MarkerDet1.CameraPowerOff();	

	cvDestroyAllWindows();


	return 0;
}



unsigned __stdcall MyThread1(LPVOID arg) //for cam1
{

	while(1)
	{
		#if LEFT_CAMERA
		MarkerDet1.MarkerDetection(1,total_folder_name);	// Marker Detection main 
		#else if RIGHT_CAMERA 
		MarkerDet1.MarkerDetection(2,total_folder_name);
		#endif
		MarkerDet1.GetInfo(detected,trns,rot,trns_filtered,rot_filtered);
		//time
		SYSTEMTIME save_time;
		GetSystemTime(&save_time);
		double total_time;
		total_time = save_time.wMinute*60+save_time.wSecond+save_time.wMilliseconds*0.001;

#if FILESAVE
		fprintf(save_file, "%d,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",1,total_time,detected,trns[0],trns[1],trns[2],rot[0],rot[1],rot[2],trns_filtered[0],trns_filtered[1],trns_filtered[2],rot_filtered[0],rot_filtered[1],rot_filtered[2]);
#endif 
		MarkerDet1.Marker_detect_end();
	}

	fclose(save_file);
	return 0;

}
