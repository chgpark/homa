
#include "MarkerDet.h"

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
char read_figure[50];
char figure_name[50];
char total_figure_name[50];
CMarkerDet::CMarkerDet(void)
{
	m_pCapture = NULL;
	m_pCapture_img = NULL;
	m_pre_pImage = NULL;
	m_pImage = NULL;
	m_mul_Image = NULL;
	m_hist_Image = NULL;
	m_hist_Image2 = NULL;
	CAM_ADAP_TH_BLOCK_VALUE = CAM_ADAP_TH_BLOCK;
	Variable_block=ABLOCKSIZE;
	Variable_meansubtract=MEANSUBTRACT;

#ifdef WIN32_REC
    m_writer = NULL;
#endif

	MarkerIDPatternMapping();
	one_marker_detected=false;
	theother_marker_detected=false;
	// Camera Parameters
	cam_parm.imgsize.width = CAM_WIDTH;
	cam_parm.imgsize.height = CAM_HEIGHT;
	cam_parm.focal = new float[2];
	cam_parm.distortion = new float [4];

	cam_parm.focal[0] = CamParm_focal[0];
	cam_parm.focal[1] = CamParm_focal[1];
	cam_parm.principal.x = CamParm_principal[0];
	cam_parm.principal.y = CamParm_principal[1];
	cam_parm.distortion[0] = CamParm_distortion[0];
	cam_parm.distortion[1] = CamParm_distortion[1];
	cam_parm.distortion[2] = CamParm_distortion[2];
	cam_parm.distortion[3] = CamParm_distortion[3];

	total_time_left_filtered_pri=0;
	count_flag=0;
	count_sequency_flag=0;
	count_iter=0;
	get_uv_idx_flag=0;
	result_marker_id_flag=0;
	count=230;
	m_vPoint_mem = new Visited [CAM_WIDTH * CAM_HEIGHT];

	for(int i=0; i<MARKER_NUM; i++)
	{
		MarkerIDPattern_cnt[i] = 0;

		for(int j=0; j<MARKER_ID_PTS; j++)
		{
			if(MarkerIDPattern[i][j] == 1)
				MarkerIDPattern_cnt[i]++;
		
		}
		//printf("MarkerIDPattern_cnt[1]=%d\n",MarkerIDPattern_cnt[1]);
	}

#if LEFT_CAMERA
	cvNamedWindow("Binary1", 0);
	cvNamedWindow("Output1", 0);
	cvResizeWindow("Binary1", 800, 600);
	cvResizeWindow("Output1", 800, 600);
#elif RIGHT_CAMERA
	cvNamedWindow("Output2", 0);
	cvNamedWindow("Binary2", 0);
	cvResizeWindow("Binary2", 800, 600);
	cvResizeWindow("Output2", 800, 600);
#endif

#ifdef LOG_POSE_DATA
	
//	m_Log_6dis = fopen("_log_6dis.txt", "wt");

#endif
	initTMat = true;
	bFileWrite = false;
	m_bFirstCheck = true;

	matCalib = MatrixXf::Matrix(4,4);
	matCalib_i = MatrixXf::Matrix(4,4);
	m_matXest = MatrixXf::Matrix(6,1);
	array_rodrigue = MatrixXf::Matrix(12,1);
	dist = 0.0f;
}

CMarkerDet::~CMarkerDet(void)
{
	delete [] cam_parm.focal;
	delete [] cam_parm.distortion;
	delete [] m_vPoint_mem;

#ifdef WIN32_REC
	if(m_writer)
		cvReleaseVideoWriter(&m_writer);
#endif

#ifdef LOG_POSE_DATA
	//fclose(m_Log_6dis);
	//fclose(left_result);
	//fclose(right_result);
#endif

	if(m_pre_pImage_gray)
		cvReleaseImage(&m_pre_pImage_gray);

	if(m_pImage)
		cvReleaseImage(&m_pImage);

	if(m_mul_Image)
		cvReleaseImage(&m_mul_Image);

	if(m_hist_Image)
		cvReleaseImage(&m_hist_Image);

	if(m_hist_Image2)
		cvReleaseImage(&m_hist_Image2);

	if(m_ReMapLUT)
		cvReleaseImage(&m_ReMapLUT);

#ifdef WIN32_GUI
	cvDestroyAllWindows();
#endif

	
}

void CMarkerDet::MarkerIDPatternMapping(void)
{
	int IDPattern_idx[MARKER_PTS][MARKER_ID_PTS] =
	{
		{1,2,3,
		 4,  5,
		 6,7,8},
		 {6,4,1,
		 7,  2,
		 8,5,3},
		 {8,7,6,
		 5,  4,
		 3,2,1},
		 {3,5,8,
		 2,  7,
		 1,4,6},
	};

	for(int i=0; i<MARKER_NUM; i++)
	{
		for(int m=0; m<MARKER_ID_PTS; m++)
		{
			for(int k=0; k<MARKER_PTS; k++)
			{
				MarkerIDPatternRot[k][i][m] = MarkerIDPattern[i][IDPattern_idx[k][m]-1];
			}
		}
	}
}

void CMarkerDet::CMarkerDetInit(void)
{

	// Fish-eye calibration
	int height = CAM_HEIGHT;
	int width = CAM_WIDTH;
	//OcamModel o; // our ocam_models for the fisheye and catadioptric cameras
	//GetOcamModel(&o, "./calib_results.txt");

	float size_rate = 1.0;

	m_mapx_persp = cvCreateMat((int)(height*size_rate), (int)(width*size_rate), CV_32FC1);
	m_mapy_persp = cvCreateMat((int)(height*size_rate), (int)(width*size_rate), CV_32FC1);

	float sf = (float)CALIB_SF;
	//CreatePerspeciveUndistortionLUT( m_mapx_persp, m_mapy_persp, &o, sf );

    // undistorted perspective and panoramic image
	m_pre_pImage_gray = cvCreateImage( cvSize((int)(width*size_rate), (int)(height*size_rate)), 8, 1 );

	m_pImage = cvCreateImage( cvSize((int)(width*size_rate), (int)(height*size_rate)), 8, 1 );

	m_mul_Image = cvCreateImage( cvSize((int)(width*size_rate), (int)(height*size_rate)), 8, 1 );

	m_hist_Image = cvCreateImage( cvSize((int)(width*size_rate), (int)(height*size_rate)), 8, 1 );

	m_hist_Image2 = cvCreateImage( cvSize((int)(width*size_rate), (int)(height*size_rate)), 8, 1 );

	m_ReMapLUT = cvCreateImage( cvSize((int)(width*size_rate), (int)(height*size_rate)), 8, 3 );

	CreateReMapLUT();
	CreateInvGrayThreshold_LUT();
	CreateAdaptiveThreshold_LUT();
}

void CMarkerDet::CameraPowerOn(int flag, const char* filename)
{
	if(m_pCapture)
		cvReleaseCapture(&m_pCapture);

#if CAMERA
	m_pCapture = cvCreateCameraCapture(0); // from camera

	if(m_pCapture != NULL)
	{
		cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_FPS, 30.0);
		cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
		cvSetCaptureProperty(m_pCapture, CV_CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);
	}
#endif
}

void CMarkerDet::CameraPowerOff(void)
{
	if(m_pCapture)
		cvReleaseCapture(&m_pCapture);

	if(m_pCapture_img)
		cvReleaseImage(&m_pCapture_img);
}

void CMarkerDet::MarkerDetection(int flag_for_markerDet , char *total_folder_name)
{
	//initialization
	marker_flag = flag_for_markerDet;
	marker_info_idx = 0;
	pose_info_success = FALSE;
	pose_filter_marker_after.x =0;
	pose_filter_marker_after.y =0;
	pose_filter_marker_after.z =0;
	pose_filter_marker_after.roll =0;
	pose_filter_marker_after.pitch =0;
	pose_filter_marker_after.yaw =0;
	pose_filter_marker_after.pose_flag=0;
	pose_filter_marker_after.bDetect=false;


	#if !CAMERA	
	sprintf_s(read_figure,"./014747_leftcamera_leftgirder/output_%d.jpg",count);
	m_pre_pImage=cvLoadImage(read_figure,CV_LOAD_IMAGE_UNCHANGED);
	//printf("count=%d\n",count);
	count++;
	if(count==401)
	{
		count=400;
	}


	#endif

	if(m_pCapture)  m_pre_pImage = cvQueryFrame( m_pCapture );

	if(m_pCapture_img)  m_pre_pImage = m_pCapture_img;

	if(m_pre_pImage == NULL)
	{
		pose_filter_marker_after.x =0;
		pose_filter_marker_after.y =0;
		pose_filter_marker_after.z =0;
		pose_filter_marker_after.roll =0;
		pose_filter_marker_after.pitch =0;
		pose_filter_marker_after.yaw =0;
		pose_filter_marker_after.pose_flag=0;
		pose_filter_marker_after.bDetect=false;
		return;
	}
	

	//image save
#if SAVEIMAGE
	sprintf(figure_name, "output_%d.jpg", picnum);
	sprintf(total_figure_name, "%s/%s",total_folder_name,figure_name);
	cvSaveImage(total_figure_name,m_pre_pImage);
#endif


	picnum++;

	// 원본 영상 그레이 변환
	// 이진화(레이블링시 흰색(255)을 개체로 잡으므로 이진화된 영상을 반전시킨다)
	
	//convert rgb to gray
	CvtGray(m_pre_pImage, m_pre_pImage_gray);
	CvtGray(m_pre_pImage, m_pImage);

	//convert gray to binary
	cvAdaptiveThreshold(m_pImage,m_pImage,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY_INV,Variable_block,Variable_meansubtract);

#if LEFT_CAMERA
	cvShowImage("Binary1", m_pImage);
#elif RIGHT_CAMERA
	cvShowImage("Binary2", m_pImage);
#endif
	
	IplImage* gray=cvCreateImage( cvSize( m_pImage->width, m_pImage->height ), 8, 1 );
	//IplImage* gray = m_pImage;
	cvCopy(m_pImage,gray);
	// 레이블링
	CBlobLabeling blob;
	blob.SetParam( gray, 150, m_vPoint_mem );	// 레이블링 할 이미지와 최소 픽셀수 등을 설정

	blob.DoLabeling();


	// 노이즈 제거
	int nMaxWidth	= (int)(gray->width  * 95. / 100.);	// 영상 가로 전체 크기의 90% 이상인 레이블은 제거
	int nMaxHeight	= (int)(gray->height * 95. / 100.);	// 영상 세로 전체 크기의 90% 이상인 레이블은 제거

	blob.BlobSmallSizeConstraint( 20, 20 );
	blob.BlobBigSizeConstraint( nMaxWidth, nMaxHeight );

	// 각 후보영역 검사
	for( int i=0; i < blob.m_nBlobs; i++ )
	{
		bool bIsMarker = false;

		CvPoint	pt1 = cvPoint(	blob.m_recBlobs[i].x,				
								blob.m_recBlobs[i].y );
		CvPoint pt2 = cvPoint(	pt1.x + blob.m_recBlobs[i].width,	
								pt1.y + blob.m_recBlobs[i].height );

		/////////////////////////////////////////////////////////////////////
		// 각 레이블이 속해있는 영상을 반전시킨 뒤, 
		// 그 영상 내부에서 다시 레이블을 찾아낸다.
		IplImage* sub_gray = cvCreateImage( cvSize( blob.m_recBlobs[i].width, blob.m_recBlobs[i].height ), 8, 1 );

		blob.GetBlobImage( sub_gray, i );

		// 이미지 반전
		GrayInverse( sub_gray );
		//cvThreshold( sub_gray, sub_gray, 1, 255, CV_THRESH_BINARY_INV );

		// 레이블링
		CBlobLabeling inner;
		inner.SetParam( sub_gray, 150, m_vPoint_mem );

		inner.DoLabeling();

	 	// 노이즈 제거
		int nSubMinWidth	= sub_gray->width * 4 / 10;
		int nSubMinHeight	= sub_gray->height * 4 / 10;

		int nSubMaxWidth	= sub_gray->width * 8 / 10;
		int nSubMaxHeight	= sub_gray->height * 8 / 10;

		inner.BlobSmallSizeConstraint( nSubMinWidth, nSubMinHeight );
		inner.BlobBigSizeConstraint( nSubMaxWidth, nSubMaxHeight );

		for( int j=0; j < inner.m_nBlobs; j++ )
		{
			int nThick = 6;

			if(		inner.m_recBlobs[j].x < nThick
				||	inner.m_recBlobs[j].y < nThick
				||	( sub_gray->width - (inner.m_recBlobs[j].x + inner.m_recBlobs[j].width) ) < nThick
				||	( sub_gray->height - (inner.m_recBlobs[j].y + inner.m_recBlobs[j].height) ) < nThick )	continue;
			
			// 마커를 찾은 경우
			CvPoint	s_pt1 = cvPoint(	pt1.x + inner.m_recBlobs[j].x,				
										pt1.y + inner.m_recBlobs[j].y );
			CvPoint s_pt2 = cvPoint(	s_pt1.x + inner.m_recBlobs[j].width,	
										s_pt1.y + inner.m_recBlobs[j].height );

			// green
			//CvScalar green = cvScalar( 0, 255, 0 );
			//cvDrawRect( m_pre_pImage, s_pt1, s_pt2, green, 2 );

			bIsMarker = true;

			break;
		}

		if( bIsMarker && marker_info_idx < MARKER_CANDITATE)
		{
			marker_info[marker_info_idx].vaild = -1;
			marker_info[marker_info_idx].id_pts_cnt = 0;
			marker_info[marker_info_idx].pts[0] = cvPoint(0, 0);
			marker_info[marker_info_idx].pts[1] = cvPoint(0, 0);
			marker_info[marker_info_idx].pts[2] = cvPoint(0, 0);
			marker_info[marker_info_idx].pts[3] = cvPoint(0, 0);

			// 레이블 표시
			CvScalar red	= CV_RGB (255, 0, 0);
			//cvDrawRect( m_pre_pImage, pt1, pt2, red, 1 );

			CvMemStorage* storage	= cvCreateMemStorage(0);
			CvSeq* contours			= 0;
			
			// 1. 윤곽 검출
			int mw	= blob.m_recBlobs[i].width;
			int mh	= blob.m_recBlobs[i].height;

			IplImage* marker = cvCreateImage( cvSize(mw, mh), 8, 1 );

			blob.GetBlobImage( marker, i );

			cvFindContours( marker, storage, &contours, sizeof (CvContour), CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
			cvReleaseImage( &marker );
			double tmp_markerSize;

		tmp_markerSize = cvContourArea(contours,CV_WHOLE_SEQ);
		//remove out of range marker candidate based on area
		if(fabs(tmp_markerSize) <= MARKER_CONTOUR_SIZE_MIN || fabs(tmp_markerSize) >= MARKER_CONTOUR_SIZE_MAX)
		{	if(storage)
			cvReleaseMemStorage( &storage );
			if(sub_gray)
			cvReleaseImage( &sub_gray );
			continue;
		}
		CvSeq* m_tmp_contour_approx;
		m_tmp_contour_approx=cvApproxPoly(contours,sizeof(CvContour),storage,CV_POLY_APPROX_DP,5,0);
		//remove out of range marker candidate based on the number of marker corner point 4
		if(m_tmp_contour_approx->total!=4)
		{	if(storage)
			cvReleaseMemStorage( &storage );
			if(sub_gray)
			cvReleaseImage( &sub_gray );
			continue;
		}
	
			// 2. 윤곽선 표시 및 윤곽선 영상 생성
			//cvDrawContours( m_pre_pImage, contours, CV_RGB (255, 255, 0), CV_RGB (0, 255, 0), -1, 1, CV_AA, cvPoint (blob.m_recBlobs[i].x, blob.m_recBlobs[i].y));

			// 3. 꼭지점 추출
			int x;
			
			float fMaxDist;

			CvPoint	corner[4];

			for( x=0; x < 4; x++ )		corner[x] = cvPoint(0, 0);

			// 초기 위치 설정
			CvPoint *st  = (CvPoint *)cvGetSeqElem( contours, 0 );

			// 첫 번 째 꼭지점 추출(최대 거리를 가지는 점 선택)
			fMaxDist = 0.0;

			for( x = 1; x < contours->total; x++ )
			{
				CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

				float fDist = sqrt( (float)(( st->x - pt->x ) * ( st->x - pt->x ) + ( st->y - pt->y ) * ( st->y - pt->y ) ));

				if( fDist > fMaxDist )
				{
					corner[0] = *pt;

					fMaxDist = fDist;
				}
			}

			// 두 번 째 꼭지점 추출(첫 번 째 꼭지점에서 최대 거리를 가지는 점 선택)
			fMaxDist = 0.0;

			for( x = 0; x < contours->total; x++ )
			{
				CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

				float fDist = sqrt( (float)(( corner[0].x - pt->x ) * ( corner[0].x - pt->x ) + ( corner[0].y - pt->y ) * ( corner[0].y - pt->y ) ));

				if( fDist > fMaxDist )
				{
					corner[1] = *pt;

					fMaxDist = fDist;
				}
			}

			// 세 번 째 꼭지점 추출(첫 번 째, 두 번 째 꼭지점에서 최대 거리를 가지는 점 선택)
			fMaxDist = 0.0;

			for( x = 0; x < contours->total; x++ )
			{
				CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

				float fDist =		sqrt( (float)(( corner[0].x - pt->x ) * ( corner[0].x - pt->x ) + ( corner[0].y - pt->y ) * ( corner[0].y - pt->y ) ))
								+	sqrt( (float)(( corner[1].x - pt->x ) * ( corner[1].x - pt->x ) + ( corner[1].y - pt->y ) * ( corner[1].y - pt->y ) ));

				if( fDist > fMaxDist )
				{
					corner[2] = *pt;

					fMaxDist = fDist;
				}
			}

			// 네 번 째 꼭지점 추출
			int x1 = corner[0].x;	int y1 = corner[0].y;			
			int x2 = corner[1].x;	int y2 = corner[1].y;
			int x3 = corner[2].x;	int y3 = corner[2].y;

			int nMaxDim = 0;

			for( x = 0; x < contours->total; x++ )
			{
				CvPoint* pt = (CvPoint *)cvGetSeqElem( contours, x );

				int x = pt->x;
				int y = pt->y;

				int nDim =		abs( ( x1 * y2 + x2 * y  + x  * y1 ) - ( x2 * y1 + x  * y2 + x1 * y  ) )
							+	abs( ( x1 * y  + x  * y3 + x3 * y1 ) - ( x  * y1 + x3 * y  + x1 * y3 ) )
							+	abs( ( x  * y2 + x2 * y3 + x3 * y  ) - ( x2 * y  + x3 * y2 + x  * y3 ) );

				if( nDim > nMaxDim )
				{
					corner[3] = *pt;

					nMaxDim = nDim;
				}
			}

			// vector inner product
			int inner_idx = 1;

			marker_info[marker_info_idx].pts[0].x = corner[0].x + blob.m_recBlobs[i].x;
			marker_info[marker_info_idx].pts[0].y = corner[0].y + blob.m_recBlobs[i].y;

            for(int m=1; m<MARKER_PTS; m++)
			{
				int idx1 = 0, idx2 = 0;
				int x1 = 0, x2 = 0;
				int y1 = 0, y2 = 0;
				float inner_result;
				float temp;

	            for(int n=1; n<MARKER_PTS; n++)
				{
					if(m!=n && idx1==0)
						idx1 = n;
					else if(m!=n && idx2==0)
						idx2 = n;
				}

				x1 = (marker_info[marker_info_idx].pts[0].x - (corner[m].x + blob.m_recBlobs[i].x));
				y1 = (marker_info[marker_info_idx].pts[0].y - (corner[m].y + blob.m_recBlobs[i].y));

				x2 = (corner[idx1].x + blob.m_recBlobs[i].x - (corner[idx2].x + blob.m_recBlobs[i].x));
				y2 = (corner[idx1].y + blob.m_recBlobs[i].y - (corner[idx2].y + blob.m_recBlobs[i].y));

				temp = (float)(abs(x1*x2+y1*y2)/(sqrt((float)(x1*x1+y1*y1))*sqrt((float)(x2*x2+y2*y2))));

				if(m==1)
				{
					inner_result = temp;
					inner_idx = m;
				}
				else
				{
					if(inner_result > temp)
					{
						inner_result = temp;
						inner_idx = m;
					}
				}
			}

			marker_info[marker_info_idx].pts[2].x = corner[inner_idx].x + blob.m_recBlobs[i].x;
			marker_info[marker_info_idx].pts[2].y = corner[inner_idx].y + blob.m_recBlobs[i].y;

			// vector outer product
			for( int m=0; m<MARKER_PTS; m++ )
			{
				if( m == 0 || m == inner_idx )
					continue;

				int x = corner[m].x + blob.m_recBlobs[i].x;
				int y = corner[m].y + blob.m_recBlobs[i].y;

				int outer_product = (marker_info[marker_info_idx].pts[0].x-x)*(marker_info[marker_info_idx].pts[2].y-y)
                                    -(marker_info[marker_info_idx].pts[2].x-x)*(marker_info[marker_info_idx].pts[0].y-y);

				if(outer_product > 0)
				{
					marker_info[marker_info_idx].pts[3] = cvPoint(x, y);
				}
				else
				{
					marker_info[marker_info_idx].pts[1] = cvPoint(x, y);
				}
			}

			// marker ID position
			float _h[9];
			CvMat H = cvMat(3, 3, CV_32F, _h);
			CvPoint2D32f srcPoints[MARKER_PTS], dstPoints[MARKER_PTS];

			srcPoints[0].x = 0.0; srcPoints[0].y = 0.0;
			srcPoints[1].x = MARKER_WIDTH; srcPoints[1].y = 0.0;
			srcPoints[2].x = MARKER_WIDTH; srcPoints[2].y = MARKER_HEIGHT;
			srcPoints[3].x = 0.0; srcPoints[3].y = MARKER_HEIGHT;

			for(int m=0; m<MARKER_PTS; m++)
			{
				dstPoints[m].x = (float)marker_info[marker_info_idx].pts[m].x;
				dstPoints[m].y = (float)marker_info[marker_info_idx].pts[m].y;
			}

			cvGetPerspectiveTransform(srcPoints, dstPoints, &H); // to find the transformation matrix "H"

			CvMat    spm = cvMat(1, MARKER_ID_PTS, CV_32FC2, srcIDPoints); //srcIDPoint: marker's geometry
			float    dstIDPoints[MARKER_ID_PTS*2] = {0};
			CvMat    dpm = cvMat(1, MARKER_ID_PTS, CV_32FC2, dstIDPoints); //dstIDPoint: 

			cvPerspectiveTransform(&spm, &dpm, &H); // invert transform to original coordinate

			// marker ID detection
			//IplImage* sub_gray2 = cvCreateImage( cvSize( blob.m_recBlobs[i].width, blob.m_recBlobs[i].height ), 8, 1 );

			cvSetImageROI(gray, cvRect(blob.m_recBlobs[i].x, blob.m_recBlobs[i].y, blob.m_recBlobs[i].width, blob.m_recBlobs[i].height));
			cvCopy(gray, sub_gray, NULL);
			cvResetImageROI(gray);

			for(int m=0; m<MARKER_ID_PTS*2; m+=2)
			{
				int data_ptr_cnt = 0;
				int img_idx;

				for(int sear_x = -2; sear_x<=2; sear_x++)
				{
					for(int sear_y = -2; sear_y<=2; sear_y++)
					{
						img_idx = ((int)dstIDPoints[m+1]-blob.m_recBlobs[i].y+sear_y) * sub_gray->widthStep + ((int)dstIDPoints[m]-blob.m_recBlobs[i].x+sear_x);

						if(img_idx >= sub_gray->imageSize || img_idx < 0)
							continue;

						if(sub_gray->imageData[img_idx] != 0)
							data_ptr_cnt++;
					}
				}

				if(data_ptr_cnt > 2)
				{
					marker_info[marker_info_idx].id_pts_cnt++;
					marker_info[marker_info_idx].id_pts_flag[m/2] = TRUE;
#ifdef WIN32_GUI
					cvCircle( m_pre_pImage, cvPoint((int)dstIDPoints[m], (int)dstIDPoints[m+1]), 2, CV_RGB(150,150,150), 1 );
#endif /* WIN32_GUI */
				}
				else
				{
					marker_info[marker_info_idx].id_pts_flag[m/2] = FALSE;
				}
			}

			marker_info_idx++;
			if(storage)
			cvReleaseMemStorage( &storage );
			if(marker)
			cvReleaseImage( &marker );
		}
		if(sub_gray)
		cvReleaseImage( &sub_gray );
	}
if(gray)
cvReleaseImage( &gray );

#ifdef TIME_CHECK2
	gettimeofday(&time2,NULL);
	print_time2("98", time1, time2);
#endif

	if(marker_info_idx > 0)
		FindExtrinsicParm();
	else
	{
		pose_filter_marker_after.x=0;
		pose_filter_marker_after.y=0;
		pose_filter_marker_after.z=0;
		pose_filter_marker_after.roll=0;
		pose_filter_marker_after.pitch=0;
		pose_filter_marker_after.yaw=0;
		pose_filter_marker_after.pose_flag=0;
		pose_filter_marker_after.bDetect=false;
	}


#if LEFT_CAMERA
	cvShowImage("Output1", m_pre_pImage);
#elif RIGHT_CAMERA
	cvShowImage("Output2", m_pre_pImage);
#endif


#if !CAMERA
	if(m_pre_pImage)
	cvReleaseImage(&m_pre_pImage);
#endif

}

//calculate 6-DOF
void CMarkerDet::FindExtrinsicParm(void)
{
	
	int i, l, m, k;
	int marker_flag_true_cnt = 0;
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, .7, .7, 0, 1, 15);
	char text[100];

	for(i=0; i<marker_info_idx; i++)
	{
		for(l=0; l<MARKER_NUM; l++)
		{
			if(marker_info[i].id_pts_cnt != MarkerIDPattern_cnt[l])
				continue;

			int ID_pt_result = 0;

			for(m=0; m<MARKER_PTS; m++)
			{
				for(k=0; k<MARKER_ID_PTS; k++)
				{
					ID_pt_result += MarkerIDPatternRot[m][l][k]*marker_info[i].id_pts_flag[k];
				}

				if(ID_pt_result == marker_info[i].id_pts_cnt)
					break;

				ID_pt_result = 0;
			}
			//find same id marker
			if(ID_pt_result == marker_info[i].id_pts_cnt)
			{
				
				marker_info[marker_info_idx].vaild =1;
				marker_info[i].marker_ID = l;
				marker_flag_true_cnt++;

				if(m > 0)
				{
					CvPoint temp_pts[MARKER_PTS];

					for(k=0; k<MARKER_PTS; k++)
					{
						temp_pts[k].x = marker_info[i].pts[k].x;
						temp_pts[k].y = marker_info[i].pts[k].y;
					}

					for(k=0; k<MARKER_PTS; k++)
					{
						marker_info[i].pts[k].x = temp_pts[(m+k)%MARKER_PTS].x;
						marker_info[i].pts[k].y = temp_pts[(m+k)%MARKER_PTS].y;
					}
				}

				break;
			}
		}

		// marker ID position
		float _h[9];
		CvMat H = cvMat(3, 3, CV_32F, _h);
		CvPoint2D32f srcPoints[MARKER_PTS], dstPoints[MARKER_PTS];

		srcPoints[0].x = 0.0; srcPoints[0].y = 0.0;
		srcPoints[1].x = MARKER_WIDTH; srcPoints[1].y = 0.0;
		srcPoints[2].x = MARKER_WIDTH; srcPoints[2].y = MARKER_HEIGHT;
		srcPoints[3].x = 0.0; srcPoints[3].y = MARKER_HEIGHT;

		for(int m=0; m<MARKER_PTS; m++)
		{
			dstPoints[m].x = (float)marker_info[i].pts[m].x;
			dstPoints[m].y = (float)marker_info[i].pts[m].y;
		}

		cvGetPerspectiveTransform(srcPoints, dstPoints, &H);

		CvMat    spm2 = cvMat(1, MARKER_INPUT_PTS-MARKER_PTS, CV_32FC2, srcTheOtherPoints);
		float    dstIDPoints2[(MARKER_INPUT_PTS-MARKER_PTS)*2] = {0};
		CvMat    dpm2 = cvMat(1, MARKER_INPUT_PTS-MARKER_PTS, CV_32FC2, dstIDPoints2);

		cvPerspectiveTransform(&spm2, &dpm2, &H);

		for(int m=MARKER_PTS; m<MARKER_INPUT_PTS; m++)
		{
			marker_info[i].pts[m].x = (int)dstIDPoints2[(m-MARKER_PTS)*2];
			marker_info[i].pts[m].y = (int)dstIDPoints2[(m-MARKER_PTS)*2+1];
		}

		for(int m=0; m<MARKER_INPUT_PTS; m++)
		{
			marker_info[i].sub_pts[m].x = (float)marker_info[i].pts[m].x;
			marker_info[i].sub_pts[m].y = (float)marker_info[i].pts[m].y;
		}
		  
		//subpixel algorithm
		cvFindCornerSubPix(m_pre_pImage_gray, marker_info[i].sub_pts, MARKER_INPUT_PTS, cvSize(5,5), cvSize(-1,-1),
						   cvTermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 100, 1e-5));
	}

	if(marker_flag_true_cnt == 0)
	{
		pose_filter_marker_after.x=0;
		pose_filter_marker_after.y=0;
		pose_filter_marker_after.z=0;
		pose_filter_marker_after.roll=0;
		pose_filter_marker_after.pitch=0;
		pose_filter_marker_after.yaw=0;
		pose_filter_marker_after.pose_flag=0;
		pose_filter_marker_after.bDetect=false;
		return;
	}
	pose_info_success = TRUE;
	
	int local_count_marker_number[MARKER_NUM]={0,};
	int count_marker_i_index[MARKER_NUM]={-1,};
	int z =0;
	int uv_index[4]={3,0,1,2};
	

	for(i=0; i<marker_info_idx; i++)
	{
		marker_info[i].vaild=0;

		for (z=0;z<4;z++)
			{		
				float first_x =  marker_info[i].sub_pts[z+1].x - marker_info[i].sub_pts[z].x; // difference x between two pixels 
				float first_y =  marker_info[i].sub_pts[z+1].y - marker_info[i].sub_pts[z].y; // difference y between two pixels
				float second_x =  marker_info[i].sub_pts[uv_index[z]].x - marker_info[i].sub_pts[z].x; // difference x between the other two pixels
				float second_y =  marker_info[i].sub_pts[uv_index[z]].y - marker_info[i].sub_pts[z].y; // difference y between the other two pixels

				float inner_product_result = (first_x * second_x + first_y * second_y) / (sqrt(first_x * first_x+ first_y * first_y) * sqrt(second_x * second_x + second_y * second_y));
				float angle = acos(inner_product_result)*180/PI; //angle
			    //if angle is not included with certain range, the candidate marker is not real marker
				if(angle<=ANGLE_THRESHOLD_LOWER || angle>=ANGLE_THRESHOLD_UPPER)
				{	
						   marker_info[i].vaild=-1;
				}
			
			}

		//fill id buffer if marker is detected, it is true
		for (k=0;k<MARKER_NUM;k++)
		{
			if(marker_info[i].marker_ID==k)
				count_marker_id_buffer[i][k][count_iter]=true;
			else
				count_marker_id_buffer[i][k][count_iter]=false;
		}
					
	}	

	if(count_sequency_flag==1)
	{			
		int check_count_id=0;
		for(i=0; i<marker_info_idx; i++)
		{
			for (k=0;k<MARKER_NUM;k++)
			{   //count how many id is detected
				for(check_count_id=count_iter-WINDOW_SIZE+1; check_count_id<=count_iter; check_count_id++)
				{
					if(count_marker_id_buffer[i][k][check_count_id]==true)
							count_marker_id_inner_window[k]++;
				
				}
			}
		}
		int save_marker_final_id=-1;
		max_count_marker=0;
		second_count_marker=0;
		for(k=0;k<MARKER_NUM;k++)
		{   //check the best checked marker id
			if(count_marker_id_inner_window[k]>=max_count_marker)
			{ 
				second_count_marker = max_count_marker;
				save_marker_second_id=save_marker_final_id;
				max_count_marker=count_marker_id_inner_window[k];
				save_marker_final_id=k;
				
			}
		}
	
		for(i=0; i<marker_info_idx; i++)
		{    // if the best checked marker id is more than window size-1, the id is choosen.
			if((marker_info[i].marker_ID==save_marker_final_id && max_count_marker>=WINDOW_SIZE-1) || (marker_info[i].marker_ID==save_marker_second_id && second_count_marker>=WINDOW_SIZE-1))
			{
				if(marker_info[i].vaild!=-1)
				  {
					marker_info[i].vaild = 1;
					result_marker_id_flag = 1;
				  }
			}
			else
			marker_info[i].vaild = -1;
		}
	
	
	}

	count_iter++;
		
	//ring buffer. if id buffer is full, the last is filled the first id buffer
	if(count_iter==MAX_BUFFER_SIZE)
	{
		int r;
		for(i=0; i<marker_info_idx; i++)
		{
			for(k=0;k<MARKER_NUM;k++)
			{
				for(r=0; r<WINDOW_SIZE-1;r++)
				{
					count_marker_id_buffer[i][k][r]=count_marker_id_buffer[i][k][MAX_BUFFER_SIZE-WINDOW_SIZE+1+r];
				}
			}
		}
		count_iter=WINDOW_SIZE-1;

	}

	//if window is not full
	if(count_iter==WINDOW_SIZE-1 && count_sequency_flag==0)
	{
		for(i=0; i<marker_info_idx; i++)
		{

			marker_info[i].vaild = -1;
		
		}
		count_sequency_flag=1;
	}

	CvPoint2D32f* Marker_uv = new CvPoint2D32f[MARKER_INPUT_PTS];
	CvPoint3D32f* World_XYZ = new CvPoint3D32f[MARKER_INPUT_PTS];
	CvPoint2D32f* Marker_uv_2 = new CvPoint2D32f[MARKER_INPUT_PTS];
	CvPoint3D32f* World_XYZ_2 = new CvPoint3D32f[MARKER_INPUT_PTS];
	int Marker_uv_idx = 0;
	float Marker_uv_dist, Marker_uv_max_dist = 0.0;


	for(i=0; i<marker_info_idx; i++)
	{
		
	Marker_uv_idx=i;

	//marker id 1,3  marker_flag 1=left camera   marker_flag 2=right camera 
    if(marker_info[i].vaild==1 && ((marker_info[i].marker_ID+1==1) && (marker_flag==1)) || ((marker_info[i].marker_ID+1==3) && (marker_flag==2)))
	{
		result_marker_id_flag=0;
		marker_count_id[0]=marker_info[i].marker_ID+1;
		for( m=0; m < MARKER_INPUT_PTS; m++ )
		{
			Marker_uv[m].x = (float)(marker_info[Marker_uv_idx].sub_pts[m].x);
			Marker_uv[m].y = (float)((float)(CAM_HEIGHT)-1.0-marker_info[Marker_uv_idx].sub_pts[m].y);

			marker1_pixel_point_u[m] = marker_info[Marker_uv_idx].sub_pts[m].x;
			marker1_pixel_point_v[m] = marker_info[Marker_uv_idx].sub_pts[m].y;

			World_XYZ[m].x = World_XYZ_data[marker_info[Marker_uv_idx].marker_ID][m][0];
			World_XYZ[m].y = World_XYZ_data[marker_info[Marker_uv_idx].marker_ID][m][1];
			World_XYZ[m].z = World_XYZ_data[marker_info[Marker_uv_idx].marker_ID][m][2];
			
		}

		CvFont font;
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1, 0, 2, 15);
		char text[100];

		for( m=0; m < MARKER_PTS; m++ )
		{
			int x1 = (int)marker_info[Marker_uv_idx].sub_pts[(m)%MARKER_PTS].x;
			int y1 = (int)marker_info[Marker_uv_idx].sub_pts[(m)%MARKER_PTS].y;
			int x2 = (int)marker_info[Marker_uv_idx].sub_pts[(m+1)%MARKER_PTS].x;
			int y2 = (int)marker_info[Marker_uv_idx].sub_pts[(m+1)%MARKER_PTS].y;

			cvLine( m_pre_pImage, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB( 0, 255, 0), 2 );
		
		}

		for( m=0; m < 4; m++ )
		{
			int x = (int)marker_info[i].sub_pts[m].x;
			int y = (int)marker_info[i].sub_pts[m].y;

			cvCircle( m_pre_pImage, cvPoint(x, y), 2, CV_RGB(255,100,100), 2 );

			if(m==0)
			{
				sprintf(text, "%d", marker_info[i].marker_ID+1, x, y );
				x += 5;	// 5픽셀 밀어서 출력
				cvPutText(m_pre_pImage, text, cvPoint(x, y), &font, CV_RGB(255,50,50));
			}

		}


	float transVects[3];
	float transVects2[3];
	float rotVects[3];
	//float PI = (float)(3.14159265358979);

	cvFindExtrinsicCameraParams(12,
		cam_parm.imgsize,
		Marker_uv,
		World_XYZ,
		cam_parm.focal,
		cam_parm.principal,
		cam_parm.distortion,
		rotVects,
		transVects
		);

	marker1_trans_v[0]=transVects[0];
	marker1_trans_v[1]=transVects[1];
	marker1_trans_v[2]=transVects[2];
	marker1_rot_v[0]=rotVects[0];
	marker1_rot_v[1]=rotVects[1];
	marker1_rot_v[2]=rotVects[2];


	float rotMat[9];
	float rotInvMat[9];
	float EulerAngles[3];
	//oat temp_pose_information[6];

	CvMat srcMat = cvMat(3, 1, CV_32F, rotVects);
	CvMat dstMat = cvMat(3, 3, CV_32F, rotMat);
	CvMat invMat = cvMat(3, 3, CV_32F, rotInvMat);

	cvRodrigues2(&srcMat, &dstMat);


	cvInvert(&dstMat, &invMat, CV_LU);

	int temp_iter;

	for(temp_iter=0;temp_iter<9;temp_iter++)
	{
		marker1_rot_m[temp_iter] = rotMat[temp_iter];
		marker1_rot_inv_m[temp_iter] = rotInvMat[temp_iter];

	}

	transVects2[0] = rotInvMat[0]*transVects[0] + rotInvMat[1]*transVects[1] + rotInvMat[2]*transVects[2];
	transVects2[1] = rotInvMat[3]*transVects[0] + rotInvMat[4]*transVects[1] + rotInvMat[5]*transVects[2];
	transVects2[2] = rotInvMat[6]*transVects[0] + rotInvMat[7]*transVects[1] + rotInvMat[8]*transVects[2];

	EulerAngles[0] = atan2(rotInvMat[8], rotInvMat[7]);
	EulerAngles[1] = asin(rotInvMat[6]);
	EulerAngles[2] = atan2(rotInvMat[0], rotInvMat[3]);

	/*pose_info_1.x = (float)(-1.0*transVects2[0]/10.0);
	pose_info_1.y = (float)(-1.0*transVects2[1]/10.0);
	pose_info_1.z = (float)(transVects2[2]/10.0);*/
	pose_info_1.x = (float)(-1.0*transVects[0]/10.0);
	pose_info_1.y = (float)(-1.0*transVects[1]/10.0);
	pose_info_1.z = (float)(transVects[2]/10.0);
	pose_info_1.roll = (float)(EulerAngles[0]/PI*180.0);
	pose_info_1.pitch = (float)(EulerAngles[1]/PI*180.0);
	pose_info_1.yaw = (float)(EulerAngles[2]/PI*180.0);
	
	// modify roll and yaw sign and direction
	pose_info_1.roll =  (float)((pose_info_1.roll-90));
	pose_info_1.yaw =  (float)((-1*pose_info_1.yaw+90));

	
	marker_check[1]=true;

	}

	//marker id 2,4  marker_flag 1=left camera   marker_flag 2=right camera 
    else if( marker_info[i].vaild==1 && ((marker_info[i].marker_ID+1==2) && (marker_flag==1)) || ((marker_info[i].marker_ID+1==4) && (marker_flag==2)))
	{

		result_marker_id_flag=0;
		marker_count_id[1]=marker_info[i].marker_ID+1;

			for( m=0; m < MARKER_INPUT_PTS; m++ )
		{
			Marker_uv_2[m].x = (float)(marker_info[Marker_uv_idx].sub_pts[m].x);
			Marker_uv_2[m].y = (float)((float)(CAM_HEIGHT)-1.0-marker_info[Marker_uv_idx].sub_pts[m].y);

			marker2_pixel_point_u[m] = marker_info[Marker_uv_idx].sub_pts[m].x;
			marker2_pixel_point_v[m] = marker_info[Marker_uv_idx].sub_pts[m].y;

			World_XYZ_2[m].x = World_XYZ_data[marker_info[Marker_uv_idx].marker_ID][m][0];
			World_XYZ_2[m].y = World_XYZ_data[marker_info[Marker_uv_idx].marker_ID][m][1];
			World_XYZ_2[m].z = World_XYZ_data[marker_info[Marker_uv_idx].marker_ID][m][2];
		}


		CvFont font;
		cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1, 0, 2, 15);
		char text[100];

		for( m=0; m < MARKER_PTS; m++ )
		{
			int x1 = (int)marker_info[Marker_uv_idx].sub_pts[(m)%MARKER_PTS].x;
			int y1 = (int)marker_info[Marker_uv_idx].sub_pts[(m)%MARKER_PTS].y;
			int x2 = (int)marker_info[Marker_uv_idx].sub_pts[(m+1)%MARKER_PTS].x;
			int y2 = (int)marker_info[Marker_uv_idx].sub_pts[(m+1)%MARKER_PTS].y;

			cvLine( m_pre_pImage, cvPoint(x1, y1), cvPoint(x2, y2), CV_RGB( 0, 255, 0), 2 );
		
		}

		for( m=0; m < 4; m++ )
		{
			int x = (int)marker_info[i].sub_pts[m].x;
			int y = (int)marker_info[i].sub_pts[m].y;

			cvCircle( m_pre_pImage, cvPoint(x, y), 2, CV_RGB(255,100,100), 2 );

			if(m==0)
			{
				sprintf(text, "%d", marker_info[i].marker_ID+1, x, y );
				x += 5;	// 5픽셀 밀어서 출력
				cvPutText(m_pre_pImage, text, cvPoint(x, y), &font, CV_RGB(255,50,50));
			}

		}


	float transVects_2[3];
	float transVects2_2[3];
	float rotVects_2[3];

	cvFindExtrinsicCameraParams(12,
		cam_parm.imgsize,
		Marker_uv_2,
		World_XYZ_2,
		cam_parm.focal,
		cam_parm.principal,
		cam_parm.distortion,
		rotVects_2,
		transVects_2
		);

	marker2_trans_v[0]=transVects_2[0];
	marker2_trans_v[1]=transVects_2[1];
	marker2_trans_v[2]=transVects_2[2];
	marker2_rot_v[0]=rotVects_2[0];
	marker2_rot_v[1]=rotVects_2[1];
	marker2_rot_v[2]=rotVects_2[2];

	float rotMat_2[9];
	float rotInvMat_2[9];
	float EulerAngles_2[3];
	//oat temp_pose_information[6];

	CvMat srcMat_2 = cvMat(3, 1, CV_32F, rotVects_2);
	CvMat dstMat_2 = cvMat(3, 3, CV_32F, rotMat_2);
	CvMat invMat_2 = cvMat(3, 3, CV_32F, rotInvMat_2);

	cvRodrigues2(&srcMat_2, &dstMat_2);
	cvInvert(&dstMat_2, &invMat_2, CV_LU);


	int temp_iter2;

	for(temp_iter2=0;temp_iter2<9;temp_iter2++)
	{
		marker2_rot_m[temp_iter2] = rotMat_2[temp_iter2];
		marker2_rot_inv_m[temp_iter2] = rotInvMat_2[temp_iter2];

	}


	transVects2_2[0] = rotInvMat_2[0]*transVects_2[0] + rotInvMat_2[1]*transVects_2[1] + rotInvMat_2[2]*transVects_2[2];
	transVects2_2[1] = rotInvMat_2[3]*transVects_2[0] + rotInvMat_2[4]*transVects_2[1] + rotInvMat_2[5]*transVects_2[2];
	transVects2_2[2] = rotInvMat_2[6]*transVects_2[0] + rotInvMat_2[7]*transVects_2[1] + rotInvMat_2[8]*transVects_2[2];

	EulerAngles_2[0] = atan2(rotInvMat_2[8], rotInvMat_2[7]);
	EulerAngles_2[1] = asin(rotInvMat_2[6]);
	EulerAngles_2[2] = atan2(rotInvMat_2[0], rotInvMat_2[3]);

	/*pose_info_2.x = (float)(-1.0*transVects2_2[0]/10.0);
	pose_info_2.y = (float)(-1.0*transVects2_2[1]/10.0);
	pose_info_2.z = (float)(transVects2_2[2]/10.0);*/
	pose_info_2.x = (float)(-1.0*transVects_2[0]/10.0);
	pose_info_2.y = (float)(-1.0*transVects_2[1]/10.0);
	pose_info_2.z = (float)(transVects_2[2]/10.0);
	pose_info_2.roll = (float)(EulerAngles_2[0]/PI*180.0);
	pose_info_2.pitch = (float)(EulerAngles_2[1]/PI*180.0);
	pose_info_2.yaw = (float)(EulerAngles_2[2]/PI*180.0);

	// modify roll and yaw sign and direction
	pose_info_2.roll =  (float)((pose_info_2.roll-90));
	pose_info_2.yaw =  (float)((-1*pose_info_2.yaw+90));


	marker_check[2]=true;
			
		}
	
	}
//if two marker is detect, calculate relative 6-dof
if(marker_check[1]==true && marker_check[2]==true)
	{
	   pose_info.x = pose_info_1.x-pose_info_2.x;
	   pose_info.y = pose_info_1.y-pose_info_2.y;
	   pose_info.z = pose_info_1.z-pose_info_2.z;
	   pose_info.roll = pose_info_1.roll-pose_info_2.roll;
	   pose_info.pitch = pose_info_1.pitch-pose_info_2.pitch;
	   pose_info.yaw = pose_info_1.yaw-pose_info_2.yaw;

	   count_flag++;
#if FILTER	    
		double time_interval;
		SYSTEMTIME left_time_filtered;
		GetSystemTime(&left_time_filtered);

		double pi = 3.141592;
		//float cutoff = (float)0.07;
		float rc = 1/(2*pi*CUTOFF);
		int start_filter1=0;
		float alpha;

		//initialization
		if(count_flag==1)
		{
			
   			total_time_left_filtered_pri = left_time_filtered.wHour*3600+left_time_filtered.wMinute*60+left_time_filtered.wSecond+left_time_filtered.wMilliseconds*0.001;

			pose_filter_marker_pri.x = pose_info.x;
			pose_filter_marker_pri.y = pose_info.y;
			pose_filter_marker_pri.z = pose_info.z;
			pose_filter_marker_pri.roll = pose_info.roll;
			pose_filter_marker_pri.pitch = pose_info.pitch;
			pose_filter_marker_pri.yaw = pose_info.yaw;

		}

		//low pass filter
		else if(count_flag>=2)
		{
   
			total_time_left_filtered = left_time_filtered.wHour*3600+left_time_filtered.wMinute*60+left_time_filtered.wSecond+left_time_filtered.wMilliseconds*0.001;

			time_interval=total_time_left_filtered-total_time_left_filtered_pri;

     
			alpha =  time_interval/(rc+time_interval);
            
			pose_filter_marker_after.x = pose_filter_marker_pri.x + alpha * (pose_info.x-pose_filter_marker_pri.x);
			pose_filter_marker_after.y = pose_filter_marker_pri.y + alpha * (pose_info.y-pose_filter_marker_pri.y);
			pose_filter_marker_after.z = pose_filter_marker_pri.z + alpha * (pose_info.z-pose_filter_marker_pri.z);
			pose_filter_marker_after.roll = pose_filter_marker_pri.roll + alpha * (pose_info.roll-pose_filter_marker_pri.roll);
			pose_filter_marker_after.pitch = pose_filter_marker_pri.pitch + alpha * (pose_info.pitch-pose_filter_marker_pri.pitch);
			pose_filter_marker_after.yaw = pose_filter_marker_pri.yaw + alpha * (pose_info.yaw-pose_filter_marker_pri.yaw);
			
			pose_filter_marker_pri.x = pose_filter_marker_after.x;
			pose_filter_marker_pri.y = pose_filter_marker_after.y;
			pose_filter_marker_pri.z = pose_filter_marker_after.z;
			pose_filter_marker_pri.roll = pose_filter_marker_after.roll;
			pose_filter_marker_pri.pitch = pose_filter_marker_after.pitch;
			pose_filter_marker_pri.yaw = pose_filter_marker_after.yaw;
			
     		total_time_left_filtered_pri=total_time_left_filtered;						

		}
	
#endif

	     pose_filter_marker_after.bDetect=true;

		 marker_comm();
}
else
{
	pose_filter_marker_after.x =0;
	pose_filter_marker_after.y =0;
	pose_filter_marker_after.z =0;
	pose_filter_marker_after.roll =0;
	pose_filter_marker_after.pitch =0;
	pose_filter_marker_after.yaw =0;
	pose_filter_marker_after.pose_flag=0;
	pose_filter_marker_after.bDetect=false;

	count_flag=0;
	marker_comm();

}

#ifdef WIN32_GUI
	//CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1.5, 1.5, 0, 2, 15);

	//char text[100];


	if(marker_check[1]==true && marker_check[2]==true)
	{
	    one_marker_detected=marker_check[1];
		theother_marker_detected=marker_check[2];
#if FILTER		
		sprintf(text, "X: %3.2f", pose_filter_marker_after.x);
		cvPutText (m_pre_pImage, text, cvPoint(20, 40), &font, CV_RGB(255,0,0));

		sprintf(text, "Y: %3.2f", pose_filter_marker_after.y);
		cvPutText (m_pre_pImage, text, cvPoint(20, 80), &font, CV_RGB(255,0,0));

		sprintf(text, "Z: %3.2f", pose_filter_marker_after.z);
		cvPutText (m_pre_pImage, text, cvPoint(20, 120), &font, CV_RGB(255,0,0));
	         
		sprintf(text, "ROLL: %3.2f",pose_filter_marker_after.roll);
		cvPutText (m_pre_pImage, text, cvPoint(20, 160), &font, CV_RGB(255,0,0));

		sprintf(text, "PITCH: %3.2f",pose_filter_marker_after.pitch);
		cvPutText (m_pre_pImage, text, cvPoint(20, 200), &font, CV_RGB(255,0,0));

		sprintf(text, "YAW: %3.2f", pose_filter_marker_after.yaw);
		cvPutText (m_pre_pImage, text, cvPoint(20, 240), &font, CV_RGB(255,0,0));
#endif

#if !FILTER		
		sprintf(text, "X: %3.2f", pose_info.x);
		cvPutText (m_pre_pImage, text, cvPoint(20, 40), &font, CV_RGB(255,0,0));

		sprintf(text, "Y: %3.2f", pose_info.y);
		cvPutText (m_pre_pImage, text, cvPoint(20, 80), &font, CV_RGB(255,0,0));

		sprintf(text, "Z: %3.2f", pose_info.z);
		cvPutText (m_pre_pImage, text, cvPoint(20, 120), &font, CV_RGB(255,0,0));
	         
		sprintf(text, "ROLL: %3.2f",pose_info.roll);
		cvPutText (m_pre_pImage, text, cvPoint(20, 160), &font, CV_RGB(255,0,0));

		sprintf(text, "PITCH: %3.2f",pose_info.pitch);
		cvPutText (m_pre_pImage, text, cvPoint(20, 200), &font, CV_RGB(255,0,0));

		sprintf(text, "YAW: %3.2f", pose_info.yaw);
		cvPutText (m_pre_pImage, text, cvPoint(20, 240), &font, CV_RGB(255,0,0));
#endif

		sprintf(text, "BLOCK SIZE: %3d",Variable_block);
		cvPutText (m_pre_pImage, text, cvPoint(20, 280), &font, CV_RGB(255,0,0));

		sprintf(text, "DC OFFSET: %3d", Variable_meansubtract);
		cvPutText (m_pre_pImage, text, cvPoint(20, 320), &font, CV_RGB(255,0,0));



	}

#endif /* WIN32_GUI */

	//transfer data for saving data
	pose_marker1.pose_flag = marker_flag;
	pose_marker1.x = pose_info_1.x;
	pose_marker1.y = pose_info_1.y;
	pose_marker1.z = pose_info_1.z;

	pose_marker1.roll = pose_info_1.roll;
	pose_marker1.pitch = pose_info_1.pitch;
	pose_marker1.yaw = pose_info_1.yaw;


	pose_marker2.pose_flag = marker_flag;
	pose_marker2.x = pose_info_2.x;
	pose_marker2.y = pose_info_2.y;
	pose_marker2.z = pose_info_2.z;

	pose_marker2.roll = pose_info_2.roll;
	pose_marker2.pitch = pose_info_2.pitch;
	pose_marker2.yaw = pose_info_2.yaw;

	delete [] Marker_uv;
	delete [] World_XYZ;
	delete [] Marker_uv_2;
	delete [] World_XYZ_2;

}


int CMarkerDet::GetOcamModel(OcamModel *myocam_model, const char *filename)
{
	double *pol        = myocam_model->pol;
	double *invpol     = myocam_model->invpol; 
	double *xc         = &(myocam_model->xc);
	double *yc         = &(myocam_model->yc); 
	double *c          = &(myocam_model->c);
	double *d          = &(myocam_model->d);
	double *e          = &(myocam_model->e);
	int    *width      = &(myocam_model->width);
	int    *height     = &(myocam_model->height);
	int *length_pol    = &(myocam_model->length_pol);
	int *length_invpol = &(myocam_model->length_invpol);
	FILE *f;
	char buf[CMV_MAX_BUF];
	int i;

	//Open file
	if(!(f=fopen(filename,"r")))
	{
		printf("File %s cannot be opened\n", filename);
		return -1;
	}

	//Read polynomial coefficients
	fgets(buf,CMV_MAX_BUF,f);
	fscanf(f,"\n");
	fscanf(f,"%d", length_pol);
	for (i = 0; i < *length_pol; i++)
	{
		fscanf(f," %lf",&pol[i]);
	}

	//Read inverse polynomial coefficients
	fscanf(f,"\n");
	fgets(buf,CMV_MAX_BUF,f);
	fscanf(f,"\n");
	fscanf(f,"%d", length_invpol);
	for (i = 0; i < *length_invpol; i++)
	{
		fscanf(f," %lf",&invpol[i]);
	}

	//Read center coordinates
	fscanf(f,"\n");
	fgets(buf,CMV_MAX_BUF,f);
	fscanf(f,"\n");
	fscanf(f,"%lf %lf\n", xc, yc);

	//Read affine coefficients
	fgets(buf,CMV_MAX_BUF,f);
	fscanf(f,"\n");
	fscanf(f,"%lf %lf %lf\n", c,d,e);

	//Read image size
	fgets(buf,CMV_MAX_BUF,f);
	fscanf(f,"\n");
	fscanf(f,"%d %d", height, width);

	fclose(f);

	return 0;
}

void CMarkerDet::World2Cam(double point2D[2], double point3D[3], OcamModel *myocam_model)
{
	double *invpol     = myocam_model->invpol; 
	double xc          = (myocam_model->xc);
	double yc          = (myocam_model->yc); 
	double c           = (myocam_model->c);
	double d           = (myocam_model->d);
	double e           = (myocam_model->e);
	//int    width       = (myocam_model->width);
	//int    height      = (myocam_model->height);
	int length_invpol  = (myocam_model->length_invpol);
	double norm        = sqrt(point3D[0]*point3D[0] + point3D[1]*point3D[1]);
	double theta       = atan(point3D[2]/norm);
	double t, t_i;
	double rho, x, y;
	double invnorm;
	int i;

	if (norm != 0) 
	{
		invnorm = 1/norm;
		t  = theta;
		rho = invpol[0];
		t_i = 1;

		for (i = 1; i < length_invpol; i++)
		{
			t_i *= t;
			rho += t_i*invpol[i];
		}

		x = point3D[0]*invnorm*rho;
		y = point3D[1]*invnorm*rho;

		point2D[0] = x*c + y*d + xc;
		point2D[1] = x*e + y   + yc;
	}
	else
	{
		point2D[0] = xc;
		point2D[1] = yc;
	}
}

void CMarkerDet::CreatePerspeciveUndistortionLUT(CvMat *mapx, CvMat *mapy, OcamModel *ocam_model, float sf)
{
	int i, j;
	int width = mapx->cols; //New width
	int height = mapx->rows;//New height
	float *data_mapx = mapx->data.fl;
	float *data_mapy = mapy->data.fl;
	float Nxc = (float)(height/2.0);
	float Nyc = (float)(width/2.0);
	float Nz  = -width/sf;
	double M[3];
	double m[2];

	for (i=0; i<height; i++)
	{
		for (j=0; j<width; j++)
		{
			M[0] = (i - Nxc);
			M[1] = (j - Nyc);
			M[2] = Nz;
			World2Cam(m, M, ocam_model);
			*( data_mapx + i*width+j ) = (float) m[1];
			*( data_mapy + i*width+j ) = (float) m[0];
		}
	}
}

int CMarkerDet::GetPoseInfo(float* x, float* y, float* z, float* pitch, float* roll, float* yaw)
{
	int ret = 0;

	if(pose_info_success == TRUE)
	{
		*x = pose_info.x;
		*y = pose_info.y;
		*z = pose_info.z;
		*pitch = pose_info.pitch;
		*roll = pose_info.roll;
		*yaw = pose_info.yaw;

		ret = 1;
	}

	return ret;
}

//int CMarkerDet::GetMCLInfo(float *rot, float *trns, float *flag, float *image_y)
int CMarkerDet::GetInfo(int &bDetected,float *trns,float *rot,float *filered_trns_marker,float *filtered_rot_marker)
{
	int ret = 0;

	trns[0]=0;
	trns[1]=0;
	trns[2]=0;

	rot[0]=0;
	rot[1]=0;
	rot[2]=0;
	bDetected =0;

	filered_trns_marker[0] =0;
	filered_trns_marker[1] =0;
	filered_trns_marker[2] =0;
	filtered_rot_marker[0] =0;
	filtered_rot_marker[1] =0;
	filtered_rot_marker[2] =0;

	if(marker_check[1] == TRUE && marker_check[2]==TRUE)
	{
		bDetected=1;
		trns[0] = pose_info.x ;
		trns[1] = pose_info.y ;
		trns[2] = pose_info.z ;

		rot[0] = pose_info.roll;
		rot[1] = pose_info.pitch;
		rot[2] = pose_info.yaw;
	
		filered_trns_marker[0]=pose_filter_marker_after.x;
		filered_trns_marker[1]=pose_filter_marker_after.y;
		filered_trns_marker[2]=pose_filter_marker_after.z;

		filtered_rot_marker[0]=pose_filter_marker_after.roll;
		filtered_rot_marker[1]=pose_filter_marker_after.pitch;
		filtered_rot_marker[2]=pose_filter_marker_after.yaw;

		ret = 1;


	}

	else
	{

		bDetected=0;
		trns[0]=0;
		trns[1]=0;
		trns[2]=0;
		rot[0]=0;
		rot[1]=0;
		rot[2]=0;
		
	}


	return ret;
}

int CMarkerDet::GetMCLInfo_marker1(int &bDetected_marker1,float *rot_marker1, float *trns_marker1, int &get_flag_marker1,char *totla_folder_name_marker1,float * left_marker1_point_x,float* left_marker1_point_y,float * left_marker1_trans_v,float* left_marker1_rot_v,float* left_marker1_rot_m,float* left_marker1_rot_inv_m,float *filtered_rot_marker1, float *filered_trns_marker1)
{
	int ret_marker1 = 0;

	trns_marker1[0]=0;
	trns_marker1[1]=0;
	trns_marker1[2]=0;

	rot_marker1[0]=0;
	rot_marker1[1]=0;
	rot_marker1[2]=0;
	bDetected_marker1 =0;
	int m;
	if(pose_info_success == TRUE)
	{
		bDetected_marker1=1;
		trns_marker1[0] = pose_marker1.x ;
		trns_marker1[1] = pose_marker1.y ;
		trns_marker1[2] = pose_marker1.z ;

		rot_marker1[0] = pose_marker1.roll;
		rot_marker1[1] = pose_marker1.pitch;
		rot_marker1[2] = pose_marker1.yaw;
	

		for( m=0; m < MARKER_INPUT_PTS; m++ )
		{
		    left_marker1_point_x[m]= marker1_pixel_point_u[m];
			left_marker1_point_y[m]= marker1_pixel_point_v[m];

		}

		left_marker1_trans_v[0]=marker1_trans_v[0];
        left_marker1_trans_v[1]=marker1_trans_v[1];
		left_marker1_trans_v[2]=marker1_trans_v[2];

		left_marker1_rot_v[0]=marker1_rot_v[0];
		left_marker1_rot_v[1]=marker1_rot_v[1];
		left_marker1_rot_v[2]=marker1_rot_v[2];

		for( m=0; m < 9; m++ )
		{
		    left_marker1_rot_m[m]= marker1_rot_m[m];
			left_marker1_rot_inv_m[m]= marker1_rot_inv_m[m];

		}

		
		
		filered_trns_marker1[0]=pose_filter_marker1_after.x;
		filered_trns_marker1[1]=pose_filter_marker1_after.y;
		filered_trns_marker1[2]=pose_filter_marker1_after.z;

		filtered_rot_marker1[0]=pose_filter_marker1_after.roll;
		filtered_rot_marker1[1]=pose_filter_marker1_after.pitch;
		filtered_rot_marker1[2]=pose_filter_marker1_after.yaw;

		get_flag_marker1 = pose_marker1.pose_flag;

		ret_marker1 = 1;

	}

	return ret_marker1;
}

int CMarkerDet::GetMCLInfo_marker2(int &bDetected_marker2,float *rot_marker2, float *trns_marker2, int &get_flag_marker2,char *totla_folder_name_marker2,float* left_marker2_point_x,float* left_marker2_point_y,float * left_marker2_trans_v,float* left_marker2_rot_v,float* left_marker2_rot_m,float* left_marker2_rot_inv_m,float *filtered_rot_marker2, float *filered_trns_marker2)
{
	int ret_marker2 = 0;

	trns_marker2[0]=0;
	trns_marker2[1]=0;
	trns_marker2[2]=0;

	rot_marker2[0]=0;
	rot_marker2[1]=0;
	rot_marker2[2]=0;
	bDetected_marker2 =0;

	int m;

	if(pose_info_success == TRUE)
	{
		bDetected_marker2=1;
		trns_marker2[0] = pose_marker2.x ;
		trns_marker2[1] = pose_marker2.y ;
		trns_marker2[2] = pose_marker2.z ;

		rot_marker2[0] = pose_marker2.roll;
		rot_marker2[1] = pose_marker2.pitch;
		rot_marker2[2] = pose_marker2.yaw;

		for( m=0; m < MARKER_INPUT_PTS; m++ )
		{
		    left_marker2_point_x[m]= marker2_pixel_point_u[m];
			left_marker2_point_y[m]= marker2_pixel_point_v[m];

		}

		left_marker2_trans_v[0]=marker2_trans_v[0];
        left_marker2_trans_v[1]=marker2_trans_v[1];
		left_marker2_trans_v[2]=marker2_trans_v[2];

		left_marker2_rot_v[0]=marker2_rot_v[0];
		left_marker2_rot_v[1]=marker2_rot_v[1];
		left_marker2_rot_v[2]=marker2_rot_v[2];
	
		
		for( m=0; m < 9; m++ )
		{
		    left_marker2_rot_m[m]= marker1_rot_m[m];
			left_marker2_rot_inv_m[m]= marker1_rot_inv_m[m];

		}

		filered_trns_marker2[0]=pose_filter_marker2_after.x;
		filered_trns_marker2[1]=pose_filter_marker2_after.y;
		filered_trns_marker2[2]=pose_filter_marker2_after.z;

		filtered_rot_marker2[0]=pose_filter_marker2_after.roll;
		filtered_rot_marker2[1]=pose_filter_marker2_after.pitch;
		filtered_rot_marker2[2]=pose_filter_marker2_after.yaw;
		
		get_flag_marker2 = pose_marker2.pose_flag;

		ret_marker2 = 1;
	}
	return ret_marker2;
}

void CMarkerDet::CreateReMapLUT(void)
{
	IplImage* temp_Image = cvCreateImage( cvSize(m_ReMapLUT->width, m_ReMapLUT->height), 8, 3 );
	unsigned long val = 0;
	unsigned char* img_pt = (unsigned char*)temp_Image->imageData;
	int i, j;

	for( j = 0; j < temp_Image->height; j++ )
	{
		for( i = 0; i < temp_Image->width;  i++ )
		{
			img_pt[0] = (unsigned char)(val);
			img_pt[1] = (unsigned char)(val>>8);
			img_pt[2] = (unsigned char)(val>>16);

			img_pt+=3;
			val++;
		}
	}

	cvRemap( temp_Image, m_ReMapLUT, m_mapx_persp, m_mapy_persp, CV_WARP_FILL_OUTLIERS, cvScalarAll(0) );

	cvReleaseImage(&temp_Image);
}

void CMarkerDet::CreateInvGrayThreshold_LUT(void)
{
	for(int i = 0; i<255*3; i++)
	{
		if(i < CAM_IMG_THRESHOLD*3)
			m_InvGrayThreshold_LUT[i] = 255;
		else
			m_InvGrayThreshold_LUT[i] = 0;
	}
}

void CMarkerDet::DoReMapWithLUT(IplImage* src, IplImage* dst)
{
	int i, j;
	unsigned long idx;
	unsigned char* LUT_pt = (unsigned char*)m_ReMapLUT->imageData;
	unsigned char* dst_pt = (unsigned char*)dst->imageData;

	src->imageData[0] = 0x00;

	for( j = 0; j < dst->height; j++ )
	{
		for( i = 0; i < dst->width;  i++ )
		{
			idx = LUT_pt[0] + (LUT_pt[1]<<8) + (LUT_pt[2]<<16);

			dst_pt[0] = src->imageData[idx];
			//dst_pt[0] = src->imageData[j*dst->width+i];

			LUT_pt+=3;
			dst_pt++;
		}
	}
}

void CMarkerDet::InvGrayThreshold(IplImage* src, IplImage* dst)
{
	int i, j;
	unsigned int color_val;
	unsigned char* src_pt = (unsigned char*)src->imageData;
	unsigned char* dst_pt = (unsigned char*)dst->imageData;

	for( j = 0; j < dst->height; j++ )
	{
		for( i = 0; i < dst->width;  i++ )
		{
			color_val = src_pt[0] + src_pt[1] + src_pt[2];

			dst_pt[0] = m_InvGrayThreshold_LUT[color_val];

			src_pt+=3;
			dst_pt++;
		}
	}
}

void CMarkerDet::CvtGray(IplImage* src, IplImage* dst)
{
	int i, j;
	unsigned char* src_pt = (unsigned char*)src->imageData;
	unsigned char* dst_pt = (unsigned char*)dst->imageData;

	for( j = 0; j < dst->height; j++ )
	{
		for( i = 0; i < dst->width;  i++ )
		{
			dst_pt[0] = (unsigned char)((src_pt[0] + src_pt[1] + src_pt[2])/3);

			src_pt+=3;
			dst_pt++;
		}
	}
}

void CMarkerDet::GrayInverse(IplImage* src)
{
	int i, j;
	unsigned char* src_pt = (unsigned char*)src->imageData;

	for( j = 0; j < src->height; j++ )
		for( i = 0; i < src->widthStep;  i++ )
			*(src_pt++) ^= 0xFF;
}

void CMarkerDet::CreateAdaptiveThreshold_LUT(void)
{
	for(int i = 0; i<511; i++)
		AThr_LUT[i] = i > (-CAM_ADAP_TH_PARM1+255) ? 0 : 255;
}

void CMarkerDet::AdaptiveThreshold(IplImage* src)
{
	int i, j;
	IplImage* box_filter;
	unsigned char* src_pt = (unsigned char*)src->imageData;
	unsigned char* filter_pt;

	box_filter = cvCreateImage( cvSize(src->width, src->height), 8, 1 );

	filter_pt = (unsigned char*)(box_filter->imageData);

	cvSmooth(src, box_filter, CV_BLUR, CAM_ADAP_TH_BLOCK_VALUE);

	for( j = 0; j < src->height; j++ )
		for( i = 0; i < src->width;  i++ )
			*(src_pt++) = AThr_LUT[(*src_pt) - *(filter_pt++) + 255];

	cvReleaseImage(&box_filter);
}

void CMarkerDet::release()
{
	if(m_pCapture)
		cvReleaseCapture(&m_pCapture);

}


MatrixXf CMarkerDet::MatFormation_4x4(MatrixXf Array)
{
	float x=Array(0,0), y=Array(1,0), z =Array(2,0), q1=Array(3,0), q2=Array(4,0), q3=Array(5,0);
	MatrixXf tmp(4,4);

	float s_q1, s_q2, s_q3, c_q1, c_q2, c_q3;

	s_q1=sin(q1);
	s_q2=sin(q2);
	s_q3=sin(q3);
	c_q1=cos(q1);
	c_q2=cos(q2);
	c_q3=cos(q3);

	////XYZ angles: 
	//tmp(0,0) = c_q2*c_q3;
	//tmp(1,0) = s_q1*s_q2*c_q3+c_q1*s_q3;
	//tmp(2,0) = -c_q1*s_q2*c_q3+s_q1*s_q3;
	//tmp(3,0) = 0;

	//tmp(0,1) = -c_q2*s_q3;
	//tmp(1,1) = -s_q1*s_q2*s_q3+c_q1*c_q3;
	//tmp(2,1) = c_q1*s_q2*s_q3+s_q1*c_q3;
	//tmp(3,1) = 0;

	//tmp(0,2) = s_q2;
	//tmp(1,2) = -s_q1*c_q2;
	//tmp(2,2) = c_q1*c_q2;
	//tmp(3,2) = 0;

	//tmp(0,3) = x;
	//tmp(1,3) = y;
	//tmp(2,3) = z;
	//tmp(3,3) = 1;

	//ZYX angles:
	tmp(0,0) = c_q2*c_q3;
	tmp(1,0) = c_q2*s_q3;
	tmp(2,0) = -s_q2;
	tmp(3,0) = 0;

	tmp(0,1) = s_q1*s_q2*c_q3-c_q1*s_q3;
	tmp(1,1) = s_q1*s_q2*s_q3+c_q1*c_q3;
	tmp(2,1) = s_q1*c_q2;
	tmp(3,1) = 0;

	tmp(0,2) = c_q1*s_q2*c_q3+s_q1*s_q3;
	tmp(1,2) = c_q1*s_q2*s_q3-s_q1*c_q3;
	tmp(2,2) = c_q1*c_q2;
	tmp(3,2) = 0;

	tmp(0,3) = x;
	tmp(1,3) = y;
	tmp(2,3) = z;
	tmp(3,3) = 1;


	if(m_bFirstCheck==TRUE)
	{
		dist = z;
	}

	return tmp;
}

MatrixXf CMarkerDet::MatFormation_3x4_inverse(MatrixXf Array)
{
	float x=Array(0,0), y=Array(1,0), z =Array(2,0), q1=Array(3,0), q2=Array(4,0), q3=Array(5,0);
	MatrixXf tmp(3,3);
	MatrixXf tmp_inverse(3,3);
	MatrixXf tmp1(3,4);

	float s_q1, s_q2, s_q3, c_q1, c_q2, c_q3;

	s_q1=sin(q1);
	s_q2=sin(q2);
	s_q3=sin(q3);
	c_q1=cos(q1);
	c_q2=cos(q2);
	c_q3=cos(q3);

	tmp(0,0) = c_q2*c_q3;
	tmp(1,0) = s_q1*s_q2*c_q3+c_q1*s_q3;
	tmp(2,0) = -c_q1*s_q2*c_q3+s_q1*s_q3;

	tmp(0,1) = -c_q2*s_q3;
	tmp(1,1) = -s_q1*s_q2*s_q3+c_q1*c_q3;
	tmp(2,1) = c_q1*s_q2*s_q3+s_q1*c_q3;

	tmp(0,2) = s_q2;
	tmp(1,2) = -s_q1*c_q2;
	tmp(2,2) = c_q1*c_q2;

	tmp_inverse = tmp.inverse();

	tmp1(0,0) = tmp_inverse(0,0);
	tmp1(1,0) = tmp_inverse(1,0);
	tmp1(2,0) = tmp_inverse(2,0);

	tmp1(0,1) = tmp_inverse(0,1);
	tmp1(1,1) = tmp_inverse(1,1);
	tmp1(2,1) = tmp_inverse(2,1);

	tmp1(0,2) = tmp_inverse(0,2);
	tmp1(1,2) = tmp_inverse(1,2);
	tmp1(2,2) = tmp_inverse(2,2);

	tmp1(0,3) = x;
	tmp1(1,3) = y;
	tmp1(2,3) = z;



	if(m_bFirstCheck==TRUE)
	{
		dist = z;
	}

	return tmp1;
}

MatrixXf CMarkerDet::MatFormation_3x4(MatrixXf Array)
{
	float x=Array(0,0), y=Array(1,0), z =Array(2,0), q1=Array(3,0), q2=Array(4,0), q3=Array(5,0);
	MatrixXf tmp(3,4);

	float s_q1, s_q2, s_q3, c_q1, c_q2, c_q3;

	s_q1=sin(q1);
	s_q2=sin(q2);
	s_q3=sin(q3);
	c_q1=cos(q1);
	c_q2=cos(q2);
	c_q3=cos(q3);

	////XYZ angles: 
	//tmp(0,0) = c_q2*c_q3;
	//tmp(1,0) = s_q1*s_q2*c_q3+c_q1*s_q3;
	//tmp(2,0) = -c_q1*s_q2*c_q3+s_q1*s_q3;

	//tmp(0,1) = -c_q2*s_q3;
	//tmp(1,1) = -s_q1*s_q2*s_q3+c_q1*c_q3;
	//tmp(2,1) = c_q1*s_q2*s_q3+s_q1*c_q3;

	//tmp(0,2) = s_q2;
	//tmp(1,2) = -s_q1*c_q2;
	//tmp(2,2) = c_q1*c_q2;

	//tmp(0,3) = x;
	//tmp(1,3) = y;
	//tmp(2,3) = z;

	//ZYX angles:
	tmp(0,0) = c_q2*c_q3;
	tmp(1,0) = c_q2*s_q3;
	tmp(2,0) = -s_q2;
	
	tmp(0,1) = s_q1*s_q2*c_q3-c_q1*s_q3;
	tmp(1,1) = s_q1*s_q2*s_q3+c_q1*c_q3;
	tmp(2,1) = s_q1*c_q2;

	tmp(0,2) = c_q1*s_q2*c_q3+s_q1*s_q3;
	tmp(1,2) = c_q1*s_q2*s_q3-s_q1*c_q3;
	tmp(2,2) = c_q1*c_q2;

	tmp(0,3) = x;
	tmp(1,3) = y;
	tmp(2,3) = z;


	if(m_bFirstCheck==TRUE)
	{
		dist = z;
	}

	return tmp;
}

MatrixXf CMarkerDet::MatFormation_3x4_rodrigue(MatrixXf array_rodrigue)
{
	float r11=array_rodrigue(0,0), r12=array_rodrigue(1,0), r13 =array_rodrigue(2,0), 
		  r21=array_rodrigue(3,0), r22=array_rodrigue(4,0), r23=array_rodrigue(5,0), 
		  r31=array_rodrigue(6,0), r32=array_rodrigue(7,0), r33=array_rodrigue(8,0),
		  t1=array_rodrigue(9,0), t2=array_rodrigue(10,0), t3=array_rodrigue(11,0);

	MatrixXf tmp(3,4);


	//ZYX angles:
	tmp(0,0) = r11;
	tmp(1,0) = r21;
	tmp(2,0) = r31;

	tmp(0,1) = r12;
	tmp(1,1) = r22;
	tmp(2,1) = r32;

	tmp(0,2) = r13;
	tmp(1,2) = r23;
	tmp(2,2) = r33;

	tmp(0,3) = t1;
	tmp(1,3) = t2;
	tmp(2,3) = t3;


	if(m_bFirstCheck==TRUE)
	{
		dist = t3;
	}

	return tmp;
}


vector<double> SystemSolution(vector<vector<double> > A,vector<double> b)
{
    //Determine and test size of a matrix
    int n = A.size();
    for(int i = 0; i < n; i++)
        if(n != A[i].size())
            throw "Error! Number of rows and columns of matrix must be equal!";

    vector<double> x (b.size());
 //vector x is a vector of solutions (x1,x2,x3...xn)

	
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            //Finding pivot
            double pivot = A[i][i];
            int index = i;
            for(int k = i+1; k < n; k++)
            {
                if(pivot > abs(A[k][i]))
                {
                    index = k;
                    pivot = A[k][i];
                }
            }

            //Row exchange
            for(int k = 0; k < n; k++)
            {
                double tmp = A[i][k];
                A[i][k] = A[index][k];
                A[index][k] = tmp;
            }

            //Elimination
            double coefficient = -(A[j][i]/A[i][i]);
            for(int k = i; k < n; k++)
            {
                A[j][k] += coefficient*A[i][k];
            }

            b[j] += coefficient*b[i];
        }
    }

    //Back-substitution
    x[n-1] = b[n-1]/A[n-1][n-1];
    for(int i = n-2; i>=0; i--)
    {
        double sum = 0;
        for(int j = i; j < n; j++)
        {
            sum += x[j]*A[i][j];
        }
        x[i] = (b[i]-sum)/A[i][i];
    }

    return x;
}


void PrintVector(const vector<double> &b)
{
    for(int i = 0; i < b.size(); i++)
        cout << setiosflags(ios::showpoint | ios::fixed | ios::right)
        << setprecision(4)
        << setw(8) << b[i]<<endl;
}

void PrintMatrix(const vector<vector<double> > &A)
{
    for ( int i = 0; i < A.size(); i++)
    {
        for ( int j = 0; j < A[i].size(); j++)
            cout << setiosflags(ios::showpoint | ios::fixed | ios::right)
                 << setprecision(4)
                 << setw(8) << A[i][j];
        cout << endl;
    }
}



void CMarkerDet::OnOpenPort(WPARAM wParam, LPARAM lParam)
{
	pCSerialPort = (CSerialPort*)wParam;

	if (OpenPort() == TRUE) {
						
	} else {
		ClosePort();
	}
}

BOOL CMarkerDet::OpenPort() 
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

void CMarkerDet::ClosePort() 
{
	
	if ( pCSerialPort->ClosePort() ) {
		isConnected = FALSE;
	} 	
}


void CMarkerDet::marker_comm()
{

	stx_lower_row[0] = (char)STX_LOWER_ROW1;
	stx_lower_row[1] = (char)STX_LOWER_ROW2;
	stx_lower_row[2] = (char)STX_LOWER_ROW3;
	stx_lower_row[3] = (char)STX_LOWER_ROW4;
	int temp_trans_x;
	int temp_trans_y;
	int temp_trans_z;
	int temp_trans_roll;
	int temp_trans_pitch;
	int temp_trans_yaw;
	Pose_Info marker_data_commu;

#if !FILTER
	marker_data_commu.x= pose_info.x;
	marker_data_commu.y= pose_info.y;
	marker_data_commu.z= pose_info.z;
	marker_data_commu.roll= pose_info.roll;
	marker_data_commu.pitch= pose_info.pitch;
	marker_data_commu.yaw= pose_info.yaw;
#endif

#if FILTER
	marker_data_commu.x= pose_filter_marker_after.x;
	marker_data_commu.y= pose_filter_marker_after.y;
	marker_data_commu.z= pose_filter_marker_after.z;
	marker_data_commu.roll= pose_filter_marker_after.roll;
	marker_data_commu.pitch= pose_filter_marker_after.pitch;
	marker_data_commu.yaw= pose_filter_marker_after.yaw;
#endif

	//marker id 1,2
	// if the value is negative, 1 is added in 8th bit
	if(marker_count_id[0]==1 || marker_count_id[1]==2)
	{   
		if(marker_data_commu.x<0)
		{
			
			temp_trans_x = 128;
			marker_data_commu.x = fabs(marker_data_commu.x);

		}
		else
			temp_trans_x = 0;

		if(marker_data_commu.y<0)
		{

			temp_trans_y = 128;
			marker_data_commu.y = fabs(marker_data_commu.y);
		}
		else
			temp_trans_y = 0;

		if(marker_data_commu.z<0)
		{

			temp_trans_z = 128;
			marker_data_commu.z = fabs(marker_data_commu.z);
		}
		else
			temp_trans_z = 0;

		
		if(marker_data_commu.roll<0)
		{

			temp_trans_roll = 128;
			marker_data_commu.roll = fabs(marker_data_commu.roll);
		}
		else
			temp_trans_roll = 0;

		if(marker_data_commu.pitch<0)
		{

			temp_trans_pitch = 128;
			marker_data_commu.pitch = fabs(marker_data_commu.pitch);
		}
		else
			temp_trans_pitch = 0;

		if(marker_data_commu.yaw<0)
		{

			temp_trans_yaw = 128;
			marker_data_commu.yaw = fabs(marker_data_commu.yaw);
		}
		else
			temp_trans_yaw = 0;
		//trasnfor the data to bit
		trans_x[0]=(char)((((int)(marker_data_commu.x*1000))/65536) + temp_trans_x);
		trans_x[1]=(char)((((int)(marker_data_commu.x*1000))%65536)/256);
		trans_x[2]=(char)((((int)(marker_data_commu.x*1000))%65536)%256);
		
		trans_y[0]=(char)((((int)(marker_data_commu.y*1000))/65536) + temp_trans_y);
		trans_y[1]=(char)((((int)(marker_data_commu.y*1000))%65536)/256);
		trans_y[2]=(char)((((int)(marker_data_commu.y*1000))%65536)%256);

		trans_z[0]=(char)((((int)(marker_data_commu.z*1000))/65536) + temp_trans_z);
		trans_z[1]=(char)((((int)(marker_data_commu.z*1000))%65536)/256);
		trans_z[2]=(char)((((int)(marker_data_commu.z*1000))%65536)%256);

		trans_roll[0]=(char)((((int)(marker_data_commu.roll*100))/65536)+ temp_trans_roll);
		trans_roll[1]=(char)((((int)(marker_data_commu.roll*100))%65536)/256);
		trans_roll[2]=(char)((((int)(marker_data_commu.roll*100))%65536)%256);

		trans_pitch[0]=(char)((((int)(marker_data_commu.pitch*100))/65536)+ temp_trans_pitch);
		trans_pitch[1]=(char)((((int)(marker_data_commu.pitch*100))%65536)/256);
		trans_pitch[2]=(char)((((int)(marker_data_commu.pitch*100))%65536)%256);

		trans_yaw[0]=(char)((((int)(marker_data_commu.yaw*100))/65536)+ temp_trans_yaw);
		trans_yaw[1]=(char)((((int)(marker_data_commu.yaw*100))%65536)/256);
		trans_yaw[2]=(char)((((int)(marker_data_commu.yaw*100))%65536)%256);


		for ( int i=0;i<ROW_COMM_NUMBER;i++)
		{
			GetSystemTime(&t);
			
			sec = t.wSecond;
		
			msec = t.wMilliseconds;

			time_comb = sec*1000+msec;
			//time
			trans_time_upper[i]= char(time_comb/256);

			trans_time_lower[i]= char(time_comb%256);

			if(i==ROW_COMM_NUMBER-1)

			{

						time_comb_save = sec + msec*0.001;
			
			}

			
	       if(i==0)
		   {    // transfer data string using bluetooh
		        BYTE buf1[ONE_LINE_LENGTH] = {STX_UPPER,stx_lower_row[i],trans_time_upper[i],trans_time_lower[i],\
				trans_x[0],trans_x[1],trans_x[2],\
				trans_y[0],trans_y[1],trans_y[2],\
				trans_z[0],trans_z[1],trans_z[2],\
				ETX_UPPER,ETX_LOWER};

				WriteComm(buf1,ONE_LINE_LENGTH);

		   }

		   else if(i==1)
		   {

			    BYTE buf1[ONE_LINE_LENGTH] = {STX_UPPER,stx_lower_row[i],trans_time_upper[i],trans_time_lower[i],\
				trans_roll[0],trans_roll[1],trans_roll[2],\
				trans_pitch[0],trans_pitch[1],trans_pitch[2],\
				trans_yaw[0],trans_yaw[1],trans_yaw[2],\
				ETX_UPPER,ETX_LOWER};

				WriteComm(buf1,ONE_LINE_LENGTH);

		   }

		}



	}
	//marker id 3,4
	else if((marker_count_id[0]==3 || marker_count_id[1]==4))
	{

		if(marker_data_commu.x<0)
		{

			temp_trans_x = 128;
			marker_data_commu.x = fabs(marker_data_commu.x);
		}
		else
			temp_trans_x = 0;

		if(marker_data_commu.y<0)
		{

			temp_trans_y = 128;
			marker_data_commu.y = fabs(marker_data_commu.y);
		}
		else
			temp_trans_y = 0;

		if(marker_data_commu.z<0)
		{

			temp_trans_z = 128;
			marker_data_commu.z = fabs(marker_data_commu.z);
		}
		else
			temp_trans_z = 0;

		if(marker_data_commu.roll<0)
		{

			temp_trans_roll = 128;
			marker_data_commu.roll = fabs(marker_data_commu.roll);
		}
		else
			temp_trans_roll = 0;

		if(marker_data_commu.pitch<0)
		{

			temp_trans_pitch = 128;
			marker_data_commu.pitch = fabs(marker_data_commu.pitch);
		}
		else
			temp_trans_pitch = 0;

		if(marker_data_commu.yaw<0)
		{

			temp_trans_yaw = 128;
			marker_data_commu.yaw = fabs(marker_data_commu.yaw);
		}
		else
			temp_trans_yaw = 0;

		trans_x[0]=(char)((((int)(marker_data_commu.x*1000))/65536) + temp_trans_x);
		trans_x[1]=(char)((((int)(marker_data_commu.x*1000))%65536)/256);
		trans_x[2]=(char)((((int)(marker_data_commu.x*1000))%65536)%256);
		
		trans_y[0]=(char)((((int)(marker_data_commu.y*1000))/65536) + temp_trans_y);
		trans_y[1]=(char)((((int)(marker_data_commu.y*1000))%65536)/256);
		trans_y[2]=(char)((((int)(marker_data_commu.y*1000))%65536)%256);

		trans_z[0]=(char)((((int)(marker_data_commu.z*1000))/65536) + temp_trans_z);
		trans_z[1]=(char)((((int)(marker_data_commu.z*1000))%65536)/256);
		trans_z[2]=(char)((((int)(marker_data_commu.z*1000))%65536)%256);

		trans_roll[0]=(char)((((int)(marker_data_commu.roll*100))/65536)+ temp_trans_roll);
		trans_roll[1]=(char)((((int)(marker_data_commu.roll*100))%65536)/256);
		trans_roll[2]=(char)((((int)(marker_data_commu.roll*100))%65536)%256);

		trans_pitch[0]=(char)((((int)(marker_data_commu.pitch*100))/65536)+ temp_trans_pitch);
		trans_pitch[1]=(char)((((int)(marker_data_commu.pitch*100))%65536)/256);
		trans_pitch[2]=(char)((((int)(marker_data_commu.pitch*100))%65536)%256);

		trans_yaw[0]=(char)((((int)(marker_data_commu.yaw*100))/65536)+ temp_trans_yaw);
		trans_yaw[1]=(char)((((int)(marker_data_commu.yaw*100))%65536)/256);
		trans_yaw[2]=(char)((((int)(marker_data_commu.yaw*100))%65536)%256);
	
			int k=0;

		for ( int i=0;i<ROW_COMM_NUMBER;i++)
		{
			GetSystemTime(&t);
			
			sec = t.wSecond;
		
			msec = t.wMilliseconds;

			time_comb = sec*1000+msec;

			trans_time_upper[i]= char(time_comb/256);

			trans_time_lower[i]= char(time_comb%256);

			if(i==ROW_COMM_NUMBER-1)

			{

						time_comb_save = sec + msec*0.001;
			
			}

			
	       if(i==0)
		   {
		        BYTE buf1[ONE_LINE_LENGTH] = {STX_UPPER,stx_lower_row[i+2],trans_time_upper[i],trans_time_lower[i],\
				trans_x[0],trans_x[1],trans_x[2],\
				trans_y[0],trans_y[1],trans_y[2],\
				trans_z[0],trans_z[1],trans_z[2],\
				ETX_UPPER,ETX_LOWER};
		 					
			    WriteComm(buf1,ONE_LINE_LENGTH);
		   }

		   else if(i==1)
		   {

			    BYTE buf1[ONE_LINE_LENGTH] = {STX_UPPER,stx_lower_row[i+2],trans_time_upper[i],trans_time_lower[i],\
				trans_roll[0],trans_roll[1],trans_roll[2],\
				trans_pitch[0],trans_pitch[1],trans_pitch[2],\
				trans_yaw[0],trans_yaw[1],trans_yaw[2],\
				ETX_UPPER,ETX_LOWER};

				WriteComm(buf1,ONE_LINE_LENGTH);

		   }



			/*TRACE("STX_UPPER = %02X\n",STX_UPPER);
			TRACE("STX_LOWER_OUTER = %02X\n",stx_lower_row[0]);

			TRACE("trans_time_upper[0] = %02X\n",trans_time_upper[0]);
			TRACE("trans_time_lower[0] = %02X\n",trans_time_lower[0]);

		    TRACE("trans_point_x[0][0] = %02X\n",trans_point_x[0][0]);
			TRACE("trans_point_x[0][1] = %02X\n",trans_point_x[0][1]);
			TRACE("trans_point_x[0][2] = %02X\n",trans_point_x[0][2]);

			TRACE("trans_point_y[0][0] = %02X\n",trans_point_y[0][0]);
			TRACE("trans_point_y[0][1] = %02X\n",trans_point_y[0][1]);
			TRACE("trans_point_y[0][2] = %02X\n",trans_point_y[0][2]);

			TRACE("trans_point_x[1][0] = %02X\n",trans_point_x[1][0]);
			TRACE("trans_point_x[1][1] = %02X\n",trans_point_x[1][1]);
			TRACE("trans_point_x[1][2] = %02X\n",trans_point_x[1][2]);

			TRACE("trans_point_y[1][0] = %02X\n",trans_point_y[1][0]);
			TRACE("trans_point_y[1][1] = %02X\n",trans_point_y[1][1]);
			TRACE("trans_point_y[1][2] = %02X\n",trans_point_y[1][2]);


			TRACE("ETX_UPPER = %02X\n",ETX_UPPER);
			TRACE("ETX_LOWER = %02X\n",ETX_LOWER);*/



		}

	}

	





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	

	
}


DWORD CMarkerDet::WriteComm(BYTE *pBuff, DWORD bufferSize)
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


void CMarkerDet::Marker_detect_end(void)
{

	marker_check[1]=false;
	marker_check[2]=false;


}
