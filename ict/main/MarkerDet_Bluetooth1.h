
#pragma once


#include "MarkerDet_Conf.h"
#include "stdafx.h"
#include <Windows.h>
#include "SerialPort.h"

#include "opencv2\opencv.hpp"
#include "opencv\cv.h"
#include "opencv\cxcore.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc_c.h"
#include "opencv2\legacy\compat.hpp"


#pragma comment(lib, "staticlib/opencv_calib3d2411.lib")
#pragma comment(lib, "staticlib/opencv_core2411.lib")
#pragma comment(lib, "staticlib/opencv_highgui2411.lib")
#pragma comment(lib, "staticlib/opencv_imgproc2411.lib")
#pragma comment(lib, "staticlib/opencv_legacy2411.lib")

#pragma comment(lib, "staticlib/IlmImf.lib")
#pragma comment(lib, "staticlib/libjasper.lib")
#pragma comment(lib, "staticlib/libjpeg.lib")
#pragma comment(lib, "staticlib/libpng.lib")
#pragma comment(lib, "staticlib/libtiff.lib")
#pragma comment(lib, "staticlib/zlib.lib")

#pragma comment(lib, "vfw32.lib")
#pragma comment(lib, "comctl32.lib")

#include "Eigen/Dense"
using Eigen::MatrixXf;


#ifdef TIME_CHECK2
#include <sys/time.h>
#endif

typedef struct 
{
	float x;
	float y;
	float z;
	float roll;
	float pitch;
	float yaw;
	int pose_flag;
	bool bDetect;
} Pose_Info;


class  CMarkerDet_B1
{
public:
	CMarkerDet_B1(void);
	~CMarkerDet_B1(void);
	
	float rot[3];
	float trns[3];

	int GetPoseInfo(bool *bDetect, float* x, float* y, float* z, float* pitch, float* roll, float* yaw);
	
	void OnOpenPort(WPARAM wParam, LPARAM lParam);
	BOOL OpenPort(void);
	void ClosePort(void);
	DWORD WatchComm_Scan();
	DWORD ReadComm(BYTE *pBuff, DWORD bufferSize);
	DWORD WriteComm(BYTE *pBuff, DWORD bufferSize);
	BOOL ProcessMarker1Data(BYTE _b);
		
	CSerialPort *pCSerialPort;
	BYTE buff;

	OVERLAPPED	*osRead, *osWrite;
	HANDLE hComm;
	BOOL isConnected;

	void data_receive();
	void data_send(int Data_sort_flag,SOCKET HSocket);

	int count_flag_first;
	int sequence[6];
	float pre_time;
	int temp_first;
	BYTE rx[200];
	int tmp_idx;

private:

	Pose_Info pose_info;
};
