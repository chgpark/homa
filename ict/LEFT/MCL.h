#ifndef MCL_H_
#define MCL_H_
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <direct.h>
#include "MarkerDet.h"

#define	VISUAL_ODOMETRY			1
#define	CONSTANT_VELOCITY		0

#define	OFFSET_LEFT_X			4500
#define	OFFSET_LEFT_Y			0
#define	OFFSET_LEFT_Z			0
#define	OFFSET_RIGHT_X			4500
#define	OFFSET_RIGHT_Y			0
#define	OFFSET_RIGHT_Z			0


#define	NUM_PARTICLE			100 // all particle number
#define	NUM_PARTICLE_RESAMPLED		10 
#define	RATIO_GLOBAL_PARTICLE		0.2 // ex) 0.1 = 10%

//distribution tune
#define	X_STDV_INITIAL			500
#define	Y_STDY_INITIAL			500
#define	Z_STDY_INITIAL			500
#define	PITCH_STDY_INITIAL		1
#define	ROLL_STDY_INITIAL		1
#define	YAW_STDY_INITIAL		1
//distribution tune - regeneration
#define	GLOGAL_PARTICLE_DISTRIBUTION	0.3  // rate compared to diff_centerofparticle_and_measurement
#define	LOCAL_PARTICLE_DISTRIBUTION	0.5 // rate compared to average distance of re sampled particle


#define	VISUALIZATION_WIDTH		10000
#define	VISUALIZATION_HEIGHT		10000



typedef struct	s_MarkerDataVector 
{
	float	rotvect1[3]; 
	float	trnsvect1[3]; 
	float	imagecoodinate1_x[MARKER_INPUT_PTS];
	float	imagecoodinate1_y[MARKER_INPUT_PTS];

	float	rotvect2[3]; 
	float	trnsvect2[3];
	float	imagecoodinate2_x[MARKER_INPUT_PTS];
	float	imagecoodinate2_y[MARKER_INPUT_PTS];
}		MarkerDataVector;


typedef struct	s_Pose3D_info
{
	float	x; 
	float	y;
	float	z;
	float	pitch;
	float	roll;
	float	yaw;
}		Pose3D_info;


typedef struct	s_Particle_info
{
	float	distance;
	float	weight;
	float	t_vector0;
	float	t_vector1;
	float	t_vector2;

	float	r_vector0;
	float	r_vector1;
	float	r_vector2;
}		Particle_info;


typedef struct	s_MeasureResults
{
	float	dist_diff; 
	float	angle_diff;
}		MeasureResults;
