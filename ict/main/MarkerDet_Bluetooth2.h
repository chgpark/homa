#pragma once

#pragma once


#include "MarkerDet_Conf.h"
#include "stdafx.h"

//#include "Result.h"
//#include "MCL.h"
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


typedef struct 
{
	float x;
	float y;
	float z;
	float roll;
	float pitch;
	float yaw;
	int data_flag;
	bool bDetect;
} Pose_Info_Marker2;

class CMarkerDet_B2
{
	
public:
	CMarkerDet_B2();           // protected constructor used by dynamic creation
	virtual ~CMarkerDet_B2();

public:

	CSerialPort *pCSerialPort;
	BYTE buff_Marker2;
	OVERLAPPED	*osRead, *osWrite;
	HANDLE hComm;
	BOOL isConnected;

	void OnInitialize(WPARAM wParam, LPARAM lParam);
	void OnOpenPort(WPARAM wParam, LPARAM lParam);
	BOOL OpenPort();
	void ClosePort();

	void OnScanStart(WPARAM wParam, LPARAM lParam);
	void OnScanStop(WPARAM wParam, LPARAM lParam);
	DWORD WatchComm_Scan();
	DWORD ReadComm(BYTE *pBuff, DWORD bufferSize);
	DWORD WriteComm(BYTE *pBuff, DWORD bufferSize);
	BOOL ProcessMarker2Data(BYTE _b);
	int temp_first;


	//temporary data
	BYTE rx[200];
	int tmp_idx;

	//for MT settings
	void	MT_Mode(int mode);
	void	MT_SetOutputMode(WORD mode);
	void	MT_SetOutputSettings(WORD mode);


	int GetPoseInfo(bool *bDetect, float* x, float* y, float* z, float* roll, float* pitch, float* yaw);

	int count_flag_first;
	float pre_time;

	int sequence[6];

	void data_receive();
	void data_send(int Data_sort_flag,SOCKET HSocket);

	private:

	Pose_Info_Marker2 pose_info;

protected:

};
