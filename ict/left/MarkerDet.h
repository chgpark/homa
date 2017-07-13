
#pragma once


#include "MarkerDet_Conf.h"
#include "BlobLabeling.h"
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

#define CMV_MAX_BUF 1024
#define MAX_POL_LENGTH 64

#define MARKER_CANDITATE MARKER_NUM*2

typedef struct
{
	double pol[MAX_POL_LENGTH];       // the polynomial coefficients: pol[0] + x"pol[1] + x^2*pol[2] + ... + x^(N-1)*pol[N-1]
	int length_pol;                   // length of polynomial
	double invpol[MAX_POL_LENGTH];    // the coefficients of the inverse polynomial
	int length_invpol;                // length of inverse polynomial
	double xc;                        // row coordinate of the center
	double yc;                        // column coordinate of the center
	double c;                         // affine parameter
	double d;                         // affine parameter
	double e;                         // affine parameter
	int width;                        // image width
	int height;                       // image height
} OcamModel;

typedef struct 
{
	bool flag;							// true marker ?
	int marker_ID;
	CvPoint pts[MARKER_INPUT_PTS];
	CvPoint2D32f sub_pts[MARKER_INPUT_PTS];
	int id_pts_cnt;
	bool id_pts_flag[MARKER_ID_PTS];
	int vaild;
	int count_marker_number;
	int local_count_marker_number;
	int count_marker_i_index;
} Marker_Info;

typedef struct 
{
	CvSize imgsize;
	CvVect32f focal;
	CvPoint2D32f principal;
	CvVect32f distortion;
} Camera_Parm;

typedef struct 
{
	float x;
	float y;
	float z;
	float pitch;
	float roll;
	float yaw;
	int pose_flag;
	bool bDetect;
} Pose_Info;

typedef struct 
{
	float rotvec[3];
	float transvect[3];

	float on_image_plane_x[12];
	float on_image_plane_y[12];

} Pose_Info_MCL;


class  CMarkerDet
{
public:
	CMarkerDet(void);
	~CMarkerDet(void);
	

	float rot[3];
	float trns[3];
	float image_x[12];
	float image_y[12];
	
	float marker1_pixel_point_u[12];
	float marker1_pixel_point_v[12];
	float marker2_pixel_point_u[12];
	float marker2_pixel_point_v[12];
	float marker1_trans_v[3];
	float marker1_rot_v[3];
	float marker2_trans_v[3];
	float marker2_rot_v[3];

	float marker1_rot_m[9];
	float marker1_rot_inv_m[9];

    float marker2_rot_m[9];
	float marker2_rot_inv_m[9];

	char save_image_directory[50];
	bool one_marker_detected;
	bool theother_marker_detected;
	void CMarkerDetInit(void);
	void CameraPowerOn(int flag, const char* filename);
	void CameraPowerOff(void);
	void MarkerDetection(int flag_for_markerDet, char* total_folder_name);
	int GetPoseInfo(float* x, float* y, float* z, float* pitch, float* roll, float* yaw);
	//int GetMCLInfo(float *rot, float *trns, float *image_x, float *image_y);
	int GetInfo(int &bDetected,float *trns,float *rot,float *filered_trns_marker,float *filtered_rot_marker);
	int GetMCLInfo_marker1(int &bDetected_marker1,float *rot_marker1, float *trns_marker1, int &get_flag_marker1,char *totla_folder_name_marker1, float* left_marker1_point_x,float* left_marker1_point_y,float * left_marker1_trans_v,float* left_marker1_rot_v,float* left_marker1_rot_m,float* left_marker1_rot_inv_m,float *filtered_rot_marker1, float *filered_trns_marker1);
	int GetMCLInfo_marker2(int& bDetected_marker2,float *rot_marker2, float *trns_marker2, int &get_flag_marker2,char *totla_folder_name_marker2, float* left_marker2_point_x,float* left_marker2_point_y,float * left_marker2_trans_v,float* left_marker2_rot_v,float* left_marker2_rot_m,float* left_marker2_rot_inv_m,float *filtered_rot_marker2, float *filered_trns_marker2);
	void OnOpenPort(WPARAM wParam, LPARAM lParam);
	BOOL OpenPort(void);
	void ClosePort(void);
	void marker_comm(void);
	void Marker_detect_end(void);
	DWORD WriteComm(BYTE *pBuff, DWORD bufferSize);
	MatrixXf matCalib,matCalib_i,m_matXest, array_rodrigue;
	MatrixXf MatFormation_4x4(MatrixXf Array);
	MatrixXf MatFormation_3x4(MatrixXf Array);
	MatrixXf MatFormation_3x4_inverse(MatrixXf Array);
	MatrixXf MatFormation_3x4_rodrigue(MatrixXf Array);
	
	CSerialPort *pCSerialPort;
	int IMUMode;
	int IMUCode;
	BYTE buff;

	OVERLAPPED	*osRead, *osWrite;
	HANDLE hComm;
	BOOL isConnected;

	bool m_bFirstCheck;
	bool initTMat;

	char trans_time_upper[ROW_COMM_NUMBER];
	char trans_time_lower[ROW_COMM_NUMBER];
	
	char trans_x[COL_COMM_NUMBER];
	char trans_y[COL_COMM_NUMBER];
	char trans_z[COL_COMM_NUMBER];

	char trans_roll[COL_COMM_NUMBER];
	char trans_pitch[COL_COMM_NUMBER];
	char trans_yaw[COL_COMM_NUMBER];

	char stx_lower_row[6];

	SYSTEMTIME t;
	WORD hour,minute,sec,msec; 
	int time_comb;
	float time_comb_save;
	Pose_Info average_filter_marker_value;
		int CAM_ADAP_TH_BLOCK_VALUE;
	int Variable_block;
	int Variable_meansubtract;
	bool count_marker_id_buffer[MARKER_CANDITATE][MARKER_NUM][MAX_BUFFER_SIZE];
	int count_marker_id_inner_window[MARKER_NUM];
	int result_marker_id_flag;
	unsigned int count_iter;
	int get_uv_idx_flag;
	int count_sequency_flag;
	int max_count_marker;
	int save_marker_second_id;
	int second_count_marker;
	int count;
#ifdef LOG_POSE_DATA
	bool bFileWrite;
//	FILE *m_Log_6dis;

#endif

private:
	CvCapture*	m_pCapture;
	IplImage*	m_pCapture_img;
	IplImage*	m_pre_pImage;
	IplImage*   m_pre_pImage_gray;
	IplImage*	m_pImage;
    IplImage*	m_mul_Image;
	IplImage*	m_hist_Image;
	IplImage*	m_hist_Image2;
	IplImage*	m_ReMapLUT;

	CvMat* m_mapx_persp;
	CvMat* m_mapy_persp;
	CvMat* pMat;

	bool MarkerIDPatternRot[MARKER_PTS][MARKER_NUM][MARKER_ID_PTS];
	Visited* m_vPoint_mem;
	unsigned char m_InvGrayThreshold_LUT[255*3];
	unsigned char AThr_LUT[511];
#ifdef WIN32_REC
	CvVideoWriter* m_writer;
#endif

#ifdef TIME_CHECK2
	struct timeval time1,time2;		//declare the timer
#endif

	int marker_info_idx;
	Marker_Info marker_info[MARKER_CANDITATE];
	Camera_Parm cam_parm;
	Pose_Info pose_info;
	Pose_Info pose_info_1;
	Pose_Info pose_info_2;

	Pose_Info pose_marker1; 
	Pose_Info pose_marker2; 
	
	Pose_Info pose_filter_marker1_after;
    Pose_Info pose_filter_marker1_pri;

	Pose_Info pose_filter_marker2_after;
    Pose_Info pose_filter_marker2_pri;

	Pose_Info pose_filter_marker_after;
	Pose_Info pose_filter_marker_pri;

	LARGE_INTEGER timefeq,start,end;
    float tinterval;
	double total_time_left_filtered_pri;
	double total_time_left_filtered;
	unsigned int count_flag;
	int marker_flag;
	int marker_count_id[2];
	bool marker_check[4];
	bool pose_info_success;
	

	float tranInvMat[16];
	float transInitVects[3];
	float dist;
//	FILE *left_result;
//	FILE *right_result;

	void MarkerIDPatternMapping(void);
	void FindExtrinsicParm(void);
	int GetOcamModel(OcamModel *myocam_model, const char *filename);
	void World2Cam(double point2D[2], double point3D[3], OcamModel *myocam_model);
	void CreatePerspeciveUndistortionLUT(CvMat *mapx, CvMat *mapy, OcamModel *ocam_model, float sf);
	void CreateReMapLUT(void);
	void CreateInvGrayThreshold_LUT(void);
	void DoReMapWithLUT(IplImage* src, IplImage* dst);
	void InvGrayThreshold(IplImage* src, IplImage* dst);
	void CvtGray(IplImage* src, IplImage* dst);
	void GrayInverse(IplImage* src);
	void CreateAdaptiveThreshold_LUT(void);
	void AdaptiveThreshold(IplImage* src);
	void release();
};
