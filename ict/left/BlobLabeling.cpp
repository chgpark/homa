
#include "BlobLabeling.h"

#define _DEF_MAX_BLOBS		10000
#define _DEF_MAX_LABEL		  100

CBlobLabeling::CBlobLabeling(void)
{
	m_nThreshold	= 0;
	m_nBlobs		= _DEF_MAX_BLOBS;
	m_Image			= NULL;

	m_recBlobs		= NULL;
	m_intBlobs		= NULL;		/* 레이블링 된 인덱스 저장 */
}

CBlobLabeling::~CBlobLabeling(void)
{
	if( m_Image != NULL )	cvReleaseImage( &m_Image );	

	if( m_recBlobs != NULL )
	{
		delete m_recBlobs;
		m_recBlobs = NULL;
	}

	if( m_intBlobs != NULL )
	{
		delete m_intBlobs;
		m_intBlobs = NULL;
	}
}

void CBlobLabeling::SetParam(IplImage* image, int nThreshold, Visited* mem)
{
	if( m_recBlobs != NULL )
	{
		delete m_recBlobs;

		m_recBlobs	= NULL;
		m_nBlobs	= _DEF_MAX_BLOBS;
	}

	if( m_intBlobs != NULL )
	{
		delete m_intBlobs;

		m_intBlobs	= NULL;
		m_nBlobs	= _DEF_MAX_BLOBS;
	}

	if( m_Image != NULL )	cvReleaseImage( &m_Image );

	m_Image			= cvCloneImage( image );

	m_nThreshold	= nThreshold;

	m_vPoint		= mem;
}

void CBlobLabeling::DoLabeling()
{
	m_nBlobs = Labeling(m_Image, m_nThreshold);
}

int CBlobLabeling::Labeling(IplImage* image, int nThreshold)
{
	if( image->nChannels != 1 ) 	return 0;

	int nNumber;
	
	int nWidth	= image->width;
	int nHeight = image->height;
	int nWidthStep = image->widthStep;
	
	unsigned char* tmpBuf;

	tmpBuf = (unsigned char*)image->imageData;

	// 레이블링을 위한 포인트 초기화
	InitvPoint(nWidth, nHeight);

	// 레이블링
	nNumber = _Labeling(tmpBuf, nWidthStep, nWidth, nHeight, nThreshold);

	// 포인트 메모리 해제
	//DeletevPoint();

	if( nNumber != _DEF_MAX_BLOBS )		m_recBlobs = new CvRect [nNumber];

	if( nNumber != _DEF_MAX_BLOBS )		m_intBlobs = new int [nNumber];

	if( nNumber != 0 )	DetectLabelingRegion(nNumber, tmpBuf, nWidthStep, nWidth, nHeight);

	return nNumber;
}

// m_vPoint 초기화 함수
void CBlobLabeling::InitvPoint(int nWidth, int nHeight)
{
	int nX, nY;

	//m_vPoint = new Visited [nWidth * nHeight];

	for(nY = 0; nY < nHeight; nY++)
	{
		for(nX = 0; nX < nWidth; nX++)
		{
			m_vPoint[nY * nWidth + nX].bVisitedFlag		= FALSE;
			m_vPoint[nY * nWidth + nX].ptReturnPoint.x	= nX;
			m_vPoint[nY * nWidth + nX].ptReturnPoint.y	= nY;
		}
	}
}

void CBlobLabeling::DeletevPoint()
{
	//delete m_vPoint;
}

// Size가 nWidth이고 nHeight인 DataBuf에서 
// nThreshold보다 작은 영역을 제외한 나머지를 blob으로 획득
int CBlobLabeling::_Labeling(unsigned char *DataBuf, int nWidthStep, int nWidth, int nHeight, int nThreshold)
{
	int /*Index = 0,*/ num = 0;
	int nX, nY, k, l;
	int StartX , StartY, EndX , EndY;
	
	// Find connected components
	for(nY = 0; nY < nHeight; nY++)
	{
		for(nX = 0; nX < nWidth; nX++)
		{
			if(DataBuf[nY * nWidthStep + nX] == 255)		// Is this a new component?, 255 == Object
			{
				num++;

				DataBuf[nY * nWidthStep + nX] = num;
				
				StartX = nX, StartY = nY, EndX = nX, EndY= nY;

				__NRFIndNeighbor(DataBuf, nWidthStep, nWidth, nHeight, nX, nY, &StartX, &StartY, &EndX, &EndY);

				if(__Area(DataBuf, nWidthStep, StartX, StartY, EndX, EndY, nWidth, num) < nThreshold)
				{
		 			for(k = StartY; k <= EndY; k++)
					{
						for(l = StartX; l <= EndX; l++)
						{
							if(DataBuf[k * nWidthStep + l] == num)
								DataBuf[k * nWidthStep + l] = 0;
						}
					}
					--num;

					if(num > 500)//250
						return  0;
				}
			}
		}
	}

	return num;	
}

// Blob labeling해서 얻어진 결과의 rec을 얻어냄 
void CBlobLabeling::DetectLabelingRegion(int nLabelNumber, unsigned char *DataBuf, int nWidthStep, int nWidth, int nHeight)
{
	int nX, nY;
	int nLabelIndex ;

	bool bFirstFlag[255] = {FALSE,};
	
	for(nY = 1; nY < nHeight - 1; nY++)
	{
		for(nX = 1; nX < nWidth - 1; nX++)
		{
			nLabelIndex = DataBuf[nY * nWidthStep + nX];

			if(nLabelIndex != 0)	// Is this a new component?, 255 == Object
			{
				if(bFirstFlag[nLabelIndex] == FALSE)
				{
					m_recBlobs[nLabelIndex-1].x			= nX;
					m_recBlobs[nLabelIndex-1].y			= nY;
					m_recBlobs[nLabelIndex-1].width		= 0;
					m_recBlobs[nLabelIndex-1].height	= 0;
				
					bFirstFlag[nLabelIndex] = TRUE;
				}
				else
				{
					int left	= m_recBlobs[nLabelIndex-1].x;
					int right	= left + m_recBlobs[nLabelIndex-1].width;
					int top		= m_recBlobs[nLabelIndex-1].y;
					int bottom	= top + m_recBlobs[nLabelIndex-1].height;

					if( left   >= nX )	left	= nX;
					if( right  <= nX )	right	= nX;
					if( top    >= nY )	top		= nY;
					if( bottom <= nY )	bottom	= nY;

					m_recBlobs[nLabelIndex-1].x			= left;
					m_recBlobs[nLabelIndex-1].y			= top;
					m_recBlobs[nLabelIndex-1].width		= right - left;
					m_recBlobs[nLabelIndex-1].height	= bottom - top;

					m_intBlobs[nLabelIndex-1]			= nLabelIndex;
				}
			}
				
		}
	}
	
}

// Blob Labeling을 실제 행하는 function
int CBlobLabeling::__NRFIndNeighbor(unsigned char *DataBuf, int nWidthStep, int nWidth, int nHeight, int nPosX, int nPosY, int *StartX, int *StartY, int *EndX, int *EndY )
{
	CvPoint CurrentPoint;
	
	CurrentPoint.x = nPosX;
	CurrentPoint.y = nPosY;

	m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x].bVisitedFlag    = TRUE;
	m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x].ptReturnPoint.x = nPosX;
	m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x].ptReturnPoint.y = nPosY;
			
	while(1)
	{
		if( (CurrentPoint.x != 0) && (DataBuf[CurrentPoint.y * nWidthStep + CurrentPoint.x - 1] == 255) )   // -X 방향
		{
			if( m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x - 1].bVisitedFlag == FALSE )
			{
				DataBuf[CurrentPoint.y  * nWidthStep + CurrentPoint.x  - 1]					= DataBuf[CurrentPoint.y * nWidthStep + CurrentPoint.x];	// If so, mark it
				m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x - 1].bVisitedFlag	= TRUE;
				m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x - 1].ptReturnPoint	= CurrentPoint;
				CurrentPoint.x--;
				
				if(CurrentPoint.x <= 0)
					CurrentPoint.x = 0;

				if(*StartX >= CurrentPoint.x)
					*StartX = CurrentPoint.x;

				continue;
			}
		}

		if( (CurrentPoint.x != nWidth - 1) && (DataBuf[CurrentPoint.y * nWidthStep + CurrentPoint.x + 1] == 255) )   // -X 방향
		{
			if( m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x + 1].bVisitedFlag == FALSE )
			{
				DataBuf[CurrentPoint.y * nWidthStep + CurrentPoint.x + 1]					= DataBuf[CurrentPoint.y * nWidthStep + CurrentPoint.x];	// If so, mark it
				m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x + 1].bVisitedFlag	= TRUE;
				m_vPoint[CurrentPoint.y * nWidth +  CurrentPoint.x + 1].ptReturnPoint	= CurrentPoint;
				CurrentPoint.x++;

				if(CurrentPoint.x >= nWidth - 1)
					CurrentPoint.x = nWidth - 1;
				
				if(*EndX <= CurrentPoint.x)
					*EndX = CurrentPoint.x;

				continue;
			}
		}

		if( (CurrentPoint.y != 0) && (DataBuf[(CurrentPoint.y - 1) * nWidthStep + CurrentPoint.x] == 255) )   // -X 방향
		{
			if( m_vPoint[(CurrentPoint.y - 1) * nWidth +  CurrentPoint.x].bVisitedFlag == FALSE )
			{
				DataBuf[(CurrentPoint.y - 1) * nWidthStep + CurrentPoint.x]					= DataBuf[CurrentPoint.y * nWidthStep + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y - 1) * nWidth +  CurrentPoint.x].bVisitedFlag	= TRUE;
				m_vPoint[(CurrentPoint.y - 1) * nWidth +  CurrentPoint.x].ptReturnPoint = CurrentPoint;
				CurrentPoint.y--;

				if(CurrentPoint.y <= 0)
					CurrentPoint.y = 0;

				if(*StartY >= CurrentPoint.y)
					*StartY = CurrentPoint.y;

				continue;
			}
		}
	
		if( (CurrentPoint.y != nHeight - 1) && (DataBuf[(CurrentPoint.y + 1) * nWidthStep + CurrentPoint.x] == 255) )   // -X 방향
		{
			if( m_vPoint[(CurrentPoint.y + 1) * nWidth +  CurrentPoint.x].bVisitedFlag == FALSE )
			{
				DataBuf[(CurrentPoint.y + 1) * nWidthStep + CurrentPoint.x]					= DataBuf[CurrentPoint.y * nWidthStep + CurrentPoint.x];	// If so, mark it
				m_vPoint[(CurrentPoint.y + 1) * nWidth +  CurrentPoint.x].bVisitedFlag	= TRUE;
				m_vPoint[(CurrentPoint.y + 1) * nWidth +  CurrentPoint.x].ptReturnPoint = CurrentPoint;
				CurrentPoint.y++;

				if(CurrentPoint.y >= nHeight - 1)
					CurrentPoint.y = nHeight - 1;

				if(*EndY <= CurrentPoint.y)
					*EndY = CurrentPoint.y;

				continue;
			}
		}
		
		if(		(CurrentPoint.x == m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint.x) 
			&&	(CurrentPoint.y == m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint.y) )
		{
			break;
		}
		else
		{
			CurrentPoint = m_vPoint[CurrentPoint.y * nWidth + CurrentPoint.x].ptReturnPoint;
		}
	}

	return 0;
}

// 영역중 실제 blob의 칼라를 가진 영역의 크기를 획득
int CBlobLabeling::__Area(unsigned char *DataBuf, int nWidthStep, int StartX, int StartY, int EndX, int EndY, int nWidth, int nLevel)
{
	int nArea = 0;
	int nX, nY;

	for (nY = StartY; nY < EndY; nY++)
		for (nX = StartX; nX < EndX; nX++)
			if (DataBuf[nY * nWidthStep + nX] == nLevel)
				++nArea;

	return nArea;
}

/******************************************************************************************************/

// nWidth와 nHeight보다 작은 rec을 모두 삭제
void CBlobLabeling::BlobSmallSizeConstraint(int nWidth, int nHeight)
{
	_BlobSmallSizeConstraint(nWidth, nHeight, m_recBlobs, m_intBlobs, &m_nBlobs);
}

void CBlobLabeling::_BlobSmallSizeConstraint(int nWidth, int nHeight, CvRect* rect, int* label, int *nRecNumber)
{
	if(*nRecNumber == 0)	return;

	int nX;
	int ntempRec = 0;

	CvRect* temp = new CvRect[*nRecNumber];
	int* labeled = new int[*nRecNumber];

	for(nX = 0; nX < *nRecNumber; nX++)
	{
		temp[nX]	= rect[nX];
		labeled[nX] = label[nX];
	}

	for(nX = 0; nX < *nRecNumber; nX++)
	{
		if( (rect[nX].width > nWidth) && (rect[nX].height > nHeight) )
		{
			temp[ntempRec] = rect[nX];
			labeled[ntempRec] = label[nX];

			ntempRec++;
		}
	}

	*nRecNumber = ntempRec;

	for(nX = 0; nX < *nRecNumber; nX++)
	{
		rect[nX] = temp[nX];
		label[nX] = labeled[nX];
	}

	delete temp;
	delete labeled;
}

// nWidth와 nHeight보다 큰 rec을 모두 삭제
void CBlobLabeling::BlobBigSizeConstraint(int nWidth, int nHeight)
{
	_BlobBigSizeConstraint(nWidth, nHeight, m_recBlobs, m_intBlobs, &m_nBlobs);
}

void CBlobLabeling::_BlobBigSizeConstraint(int nWidth, int nHeight, CvRect* rect, int* label, int* nRecNumber)
{
	if(*nRecNumber == 0)	return;

	int nX;
	int ntempRec = 0;

	CvRect* temp = new CvRect [*nRecNumber];
	int* labeled = new int [*nRecNumber];

	for(nX = 0; nX < *nRecNumber; nX++)
	{
		temp[nX] = rect[nX];
		labeled[nX] = label[nX];
	}

	for(nX = 0; nX < *nRecNumber; nX++)
	{
		if( (rect[nX].width < nWidth) && (rect[nX].height < nHeight) )
		{
			temp[ntempRec] = rect[nX];
			labeled[ntempRec] = label[nX];

			ntempRec++;
		}
	}

	*nRecNumber = ntempRec;

	for(nX = 0; nX < *nRecNumber; nX++)
	{
		rect[nX] = temp[nX];
		label[nX] = labeled[nX];
	}

	delete temp;
	delete labeled;
}

///////////////////////////////////////////////////////////////////////////////////
// 원하는 블롭의 이미지 정보만 가져온다.
void CBlobLabeling::GetBlobImage(IplImage* dest, int nLabel)
{
	cvSetZero( dest );

	CvRect rect = m_recBlobs[ nLabel ];
	int nNum	= m_intBlobs[ nLabel ];

	for( int j = 0; j < rect.height; j++ )
	for( int i = 0; i < rect.width;  i++ )
	{
		unsigned char val = (unsigned char)m_Image->imageData[ (j + rect.y) * m_Image->widthStep + (i + rect.x) ];

		if( val == nNum )	dest->imageData[ j * dest->widthStep + i ] = (unsigned char)255;			
	}	
}
