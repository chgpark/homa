//  Ŭ���� : CBlobLabeling

#pragma once



#include "opencv2\opencv.hpp"
#include "opencv\cv.h"
#include "opencv\cxcore.h"
#include "opencv\highgui.h"
#include "opencv2\imgproc\imgproc_c.h"
#include "opencv2\legacy\compat.hpp"
#include "Eigen/Dense"



#include "MarkerDet_Conf.h"

typedef struct 
{
	bool	bVisitedFlag;
	CvPoint ptReturnPoint;
} Visited;

class  CBlobLabeling
{
public:
	CBlobLabeling(void);
	~CBlobLabeling(void);

	IplImage* m_Image;				// ���̺��� ���� �̹���
	int m_nThreshold;				// ���̺� ������Ȧ�� ��
	Visited* m_vPoint;				// ���̺��� �湮����
	int	m_nBlobs;					// ���̺��� ����
	CvRect* m_recBlobs;				// �� ���̺� ����
	int* m_intBlobs;				// �� ���̺� �ε���
	void SetParam(IplImage* image, int nThreshold, Visited* mem); 	    // ���̺� �̹��� ����
	void DoLabeling(); 	        	// ���̺�(����)

private:
	int Labeling(IplImage* image, int nThreshold);	    // ���̺�(����)
	void InitvPoint(int nWidth, int nHeight);       	// ����Ʈ �ʱ�ȭ
	void DeletevPoint();
	void DetectLabelingRegion(int nLabelNumber, unsigned char *DataBuf, int nWidthStep, int nWidth, int nHeight); 	// ���̺� ��� ���
	int	_Labeling(unsigned char *DataBuf, int nWidthStep, int nWidth, int nHeight, int nThreshold); 	            // ���̺�(���� �˰���)
	// _Labling ���� ��� �Լ�
	int	__NRFIndNeighbor(unsigned char *DataBuf, int nWidthStep, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY );
	int __Area(unsigned char *DataBuf, int nWidthStep, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel);

	/******************************************************************/

	// ����, ���� ũ�Ⱑ �񱳰� ���� ���� ���̺� ����
public:
	void BlobSmallSizeConstraint(int nWidth, int nHeight);
private:
	void _BlobSmallSizeConstraint(int nWidth, int nHeight, CvRect* rect, int* label, int* nRecNumber);

	// ����, ���� ũ�Ⱑ �񱳰� ���� ū ���̺� ����
public:
	void BlobBigSizeConstraint(int nWidth, int nHeight);
private:
	void _BlobBigSizeConstraint(int nWidth, int nHeight, CvRect* rect, int* label, int* nRecNumber);

	/******************************************************************/
	// ���ϴ� ����� �̹��� ������ �����´�.
public:
	void GetBlobImage(IplImage* dest, int nLabel);
};