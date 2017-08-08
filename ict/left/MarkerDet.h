#pragma once

#include "winset.h"
#include "MarkerDet_Conf.h"
#include "BlobLabeling.h"
#include "SerialPort.h"
#include "opencv2/opencv.hpp"
#include "opencv/cv.h"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
#include "opencv2/improc/imgproc_c.h"
#include "opencv2/legacy/compat.hpp"

#include "Eigen/Dense"
using Eigen::MatrixXf;

/*
#ifdef TIME_CHECK2
#include <time.h>
#endif
 */

#define CMV_MAX_BUF 1024
#define MAX_POL_LENGTH 64
#define MARKER_CANDIDATE MARKER_NUM*2

typedef	union			_LARGE_INTEGER
{
	struct
	{
		unsigned long		LowPart;
		long			HighPart;
	};
	struct
	{
		unsigned long		LowPart;
		long			HighPart;
	}			u;
	double			QuadPart;
}				LARGE_INTEGER;

typedef struct			s_OcamModel
{
	double			pol[MAX_POL_LENGTH];
	double			invpol[MAX_POL_LENGTH];
	int			length_pol;
	int			length_invpol;
	double			xc;
	double			yc;
	double			c;
	double			d;
	double			e;
	int			width;
	int			height;
}				OcamModel;

typedef struct			s_Marker_Info;
{
	bool			flag;
	int			marker_ID;
	CvPoint			pts[MARKER_INPUT_PTS];
	CvPoint2D32f		sub_pts[MARKER_INTPUT_PTS];
	int			id_pts_cnt;
	int			valid;
	int			count_marker_number;
	int			local_count_marker_number;
	int			count_marker_i_index;
}				Marker_Info;

typedef struct			s_Camera_Parm;
{
	CvSize			imgsize;
	Cvect32f		focal;
	CvPoint2D32f		principal;
	CvVect32f		distortion;
}				Camera_Parm;

typedef struct			s_Pose_Info
{
	float			x;
	float			y;
	float			z;
	float			pitch;
	float			roll;
	float			yaw;
	int			pose_flag;
	bool			bDetect;
}				Pose_Info;

typedef	struct			s_Pose_Info_MCL;
{
	float			rotvec[3];
	float			transvect[3];
	float			on_image_plane_x[12];
	float			on_image_plane_y[12];
}				Pose_Info_MCL

class				CMarekerDet
{
	public:
		CMarkerDet(void);
		~CMarkerDet(void);

		float		rot[3];
		float		trns[3];
		float		image_x[12];
		float		image_y[12];

		float		marker1_pixel_point_u[12];
		float		marker1_pixel_point_v[12];
		float		marker2_pixel_point_u[12];
		float		marker2_pixel_point_v[12];
		float		marker1_trans_v[3];
		float		marker1_rot_v[3];
		float		marker2_trans_v[3];
		float		marker2_rot_v[3];

		float		marker1_rot_m[9];
		float		marker1_rot_inv_m[9];

		float		marker2_rot_m[9];
		float		marker2_rot_inv_m[9];

		char		save_image_dir[50];
		bool		one_marker_det;
		bool		theother_marker;
		void		CMarkerDetInit(void);
		void		CameraPowerOn(int flag, const char* filename);
		void		CameraPowerOff(void);
		void		MarkerDetection(int flag_for_markerDet, char* total_folder_name);
		int		GetPoseInfo(float* x, float* y, float* z, float* pitch, float* roll, float* yaw);
		int		GetInfo(int &bDetected, float *trns, float *rot, float *filered_trns_marker, float *filtered_rot_marker);
		int		GetMCLInfo_marker1(int &bDetected_marker1, float *rot_marker1, float *trns_marker1, int &get_flag_marker1, char *totla_folder_name_marker1, float* left_marker1_point_x, float* left_marker1_point_y, float * left_marker1_trans_v, float* left_marker1_rot_v, float* left_marker1_rot_m, float* left_marker1_rot_inv_m, float *filtered_rot_marker1, float *filered_trns_marker1);
		int		GetMCLInfo_marker2(int& bDetected_marker2, float *rot_marker2, float *trns_marker2, int &get_flag_marker2, char *totla_folder_name_marker2, float* left_marker2_point_x, float* left_marker2_point_y, float * left_marker2_trans_v, float* left_marker2_rot_v, float* left_marker2_rot_m, float* left_marker2_rot_inv_m, float *filtered_rot_marker2, float *filered_trns_marker2);
		void		OnOpenPort(WPARAM wParam, LPARAM lParam);
		int		OpenPort(void);
		void		ClosePort(void);
		void		marker_comm(void);
		void		Marker_detect_end(void);
		unsigned long	WriteComm(unsigned char *pBuff, unsigned long bufferSize);
		MatrixXf	matCalib, matCalib_i, m_matXest, array_rodrigue;
		MatrixXf	MatFormation_4x4(MatrixXf Array);
		MatrixXf	MatFormation_3x4(MatrixXf Array);
		MatrixXf	MatFormation_3x4_inverse(MatrixXf Array);
		MatrixXf	MatFormation_3x4_rodrigue(MatrixXf Array);

		CSerialPort	*pCSerialPort;
		int		IMUMode;
		int		IMUCode;
		unsigned char	buff;

		OVERLAPPED	*osRead, *osWrite;
		void		*hComm;
		int		isConnected;

		bool		m_bFirstCheck;
		bool		initTMat;

		char		trans_time_upper[ROW_COMM_NUMBER];
		char		trans_time_lower[ROW_COMM_NUMBER];

		char		trans_x[COL_COMM_NUMBER];
		char		trans_y[COL_COMM_NUMBER];
		char		trans_z[COL_COMM_NUMBER];

		char		trans_roll[COL_COMM_NUMBER];
		char		trans_pitch[COL_COMM_NUMBER];
		char		trans_yaw[COL_COMM_NUMBER];

		char		stx_lower_row[6];

		time_t		t;
		unsigned short	hour, minute, sec, msec;
		int		time_comb;
		float           time_comb_save;
		Pose_Info       average_filter_marker_value;
		int             CAM_ADAP_TH_BLOCK_VALUE;
		int             Variable_block;
		int             Variable_meansubtract;
		bool            count_marker_id_buffer[MARKER_CANDIDATE][MARKER_NUM][MAX_BUFFER_SIZE];
		int             count_marker_id_inner_window[MARKER_NUM];
		int             result_marker_id_flag;
		unsigned int    count_iter;
		int             get_uv_idx_flag;
		int             count_sequency_flag;
		int             max_count_marker;
		int             save_marker_second_id;
		int		second_count_marker;
		int		count;
#ifdef	LOG_POSE_DATA
		bool		bFileWrite;
#endif

	private:
		VideoCapture	m_pCapture;
		Mat		m_pCapture_img;
		Mat		m_pre_pImage;
		Mat		m_pre_pImage_gray;
		Mat		m_pImage;
		Mat		m_mul_Image;
		Mat		m_hist_Image;
		Mat		m_hist_Image2;
		Mat		m_ReMapLUT;

		Mat		m_mapx_persp;
		Mat		m_mapy_persp;
		Mat		pMat;

		bool		MarkerIDPatternRot[MARKER_PTS][MARKER_NUM][MARKER_ID_PTS];
		Visited*	m_vPoint_mem;
		unsigned char	m_InvGrayThreshold_LUT[255 * 3];
		unsigned char	AThr_LUT[511];
#ifdef	WIN32_REC
		CvVideoWriter*	m_writer;
#endif

#ifdef	TIME_CHECK2
		struct	timeval	time1,time2;
#endif

		int		marker_info_idx;
		Marker_Info	marker_info[MARKER_CANDIDATE];
		Camera_Parm	cam_parm;
		Pose_Info	pose_info;
		Pose_Info	pose_info_1;
		Pose_Info	pose_info_2;

		Pose_Info	pose_marker1;
		Pose_Info	pose_marker2;

		Pose_Info	pose_filter_marker1_after;
		Pose_Info	pose_filter_marker1_pri;

		Pose_Info	pose_filter_marker2_after;
		Pose_Info	pose_filter_marker2_pri;

		Pose_Info	pose_filter_marker_after;;
		Pose_Info	pose_filter_marker_pri;

		LARGE_INTEGER	timefeq, start, end;
		float		tinterval;
		double		total_time_left_filtered_pri;
		double		total_time_left_filtered;
		unsigned int	count_flag;
		int		marker_flag;
		int		marker_count_id[2];
		bool		marker_check[4];
		bool		pose_info_success;

		float		tranInvMat[16];
		float		transInitVects[3];
		float		dist;

		void MarkerIDPatternMapping(void);
		void FindExtrinsicParm(void);
		int GetOcamModel(OcamModel *myocam_model, const char *filename);
		void World2Cam(double point2D[2], double point3D[3], OcamModel *myocam_model);
		void CreatePerspeciveUndistortionLUT(Mat mapx, Mat mapy, OcamModel *ocam_model, float sf);
		void CreateReMapLUT(void);
		void CreateInvGrayThreshold_LUT(void);
		void DoReMapWithLUT(Mat src, Mat dst);
		void InvGrayThreshold(Mat src, Mat dst);
		void CvtGray(Mat src, Mat dst);
		void GrayInverse(Mat src);
		void CreateAdaptiveThreshold_LUT(void);
		void AdaptiveThreshold(Mat src);
		void release();
};
