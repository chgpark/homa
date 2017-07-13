
#pragma once


/*-------------------------------------------------*/
// Ganeral Define
/*-------------------------------------------------*/

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define WIN32_GUI 
#define WIN32_GUI_POSEMAP
//#define WIN32_REC
#define LOG_POSE_DATA


#define FILTER 1
#define FILESAVE 0
#define SAVEIMAGE 0
#define CAMERA 1	// 0= loading image 1= camera 
#define LEFT_CAMERA 1 //choice left camera or right camera
#define RIGHT_CAMERA 0

//marker size
#define MARKERSIZE_270 1
#define MARKERSIZE_250 0
#define MARKERSIZE_230 0

//marker size
#if MARKERSIZE_270
#define MARKER_WIDTH 		270.
#define MARKER_HEIGHT 		270.
#elif MARKERSIZE_250
#define MARKER_WIDTH 		250.
#define MARKER_HEIGHT 		250.
#elif MARKERSIZE_230
#define MARKER_WIDTH 		230.
#define MARKER_HEIGHT 		230.
#endif

//image size
#define CAM_HEIGHT 			1080
#define CAM_WIDTH 		    1920
#define CAM_IMG_THRESHOLD	100
#define CAM_ADAP_TH_BLOCK	201
#define CAM_ADAP_TH_PARM1	5

#define CALIB_SF			1.35

#define PI 3.14159265358979

#define MARKER_NUM 			4 //30
#define MARKER_PTS 			4
#define MARKER_INPUT_PTS 	12
#define MARKER_ID_PTS 		8
#define MARKER_CONTOUR_SIZE_MIN	1000
#define MARKER_CONTOUR_SIZE_MAX	990000

//wireless communication start byte and end byte
#define STX_UPPER 0xff
#define STX_LOWER_ROW1 0xf9
#define STX_LOWER_ROW2 0xfa
#define STX_LOWER_ROW3 0xfb
#define STX_LOWER_ROW4 0xfc
#define ETX_UPPER 0xff
#define ETX_LOWER 0xf0

#define ROW_COMM_NUMBER 2
#define COL_COMM_NUMBER 3
#define ONE_LINE_LENGTH 15
#define CUTOFF 1.5  // low passs filter 
#define ABLOCKSIZE 231
#define MEANSUBTRACT 20
#define ANGLE_THRESHOLD_LOWER 70
#define ANGLE_THRESHOLD_UPPER 110
#define MAX_BUFFER_SIZE 50 //the number of id buffer
#define WINDOW_SIZE 8 //window size

extern float CamParm_focal[2];
extern float CamParm_principal[2];
extern float CamParm_principal_theoretical[2];
extern float CamParm_distortion[4];

extern float srcIDPoints[MARKER_ID_PTS*2];
extern float srcTheOtherPoints[];
extern bool MarkerIDPattern[MARKER_NUM][MARKER_ID_PTS];
extern int MarkerIDPattern_cnt[MARKER_NUM];
extern float World_XYZ_data[MARKER_NUM][MARKER_INPUT_PTS][3];