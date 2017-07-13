#ifndef MCL_H_
#define MCL_H_
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "MarkerDet.h"
#include <direct.h>
#include <iostream>
#include <fstream>
#include <time.h>

#define VISUAL_ODOMETRY 1
#define CONSTANT_VELOCITY 0

//information about construction member (distance btw two sub-systems)
#define OFFSET_LEFT_X		4500
#define OFFSET_LEFT_Y		0
#define OFFSET_LEFT_Z		0
#define OFFSET_RIGHT_X		4500
#define OFFSET_RIGHT_Y		0
#define OFFSET_RIGHT_Z		0


#define NUM_PARTICLE 100 // all particle number
#define NUM_PARTICLE_RESAMPLED 10 
#define RATIO_GLOBAL_PARTICLE 0.2 // ex) 0.1 = 10%

//distribution tune
#define X_STDV_INITIAL 500
#define Y_STDY_INITIAL 500
#define Z_STDY_INITIAL 500
#define PITCH_STDY_INITIAL 1
#define ROLL_STDY_INITIAL 1
#define YAW_STDY_INITIAL 1
//distribution tune - regeneration
#define GLOGAL_PARTICLE_DISTRIBUTION 0.3  // rate compared to diff_centerofparticle_and_measurement
#define LOCAL_PARTICLE_DISTRIBUTION 0.5 // rate compared to average distance of re sampled particle


#define VISUALIZATION_WIDTH 10000
#define VISUALIZATION_HEIGHT 10000



typedef struct MarkerDataVector_ 
{
	float rotvect1[3]; 
	float trnsvect1[3]; 
	float imagecoodinate1_x[MARKER_INPUT_PTS];
	float imagecoodinate1_y[MARKER_INPUT_PTS];

	float rotvect2[3]; 
	float trnsvect2[3];
	float imagecoodinate2_x[MARKER_INPUT_PTS];
	float imagecoodinate2_y[MARKER_INPUT_PTS];
}MarkerDataVector;


typedef struct Pose3D_info_
{
	float x; 
	float y;
	float z;
	float pitch;
	float roll;
	float yaw;
}Pose3D_info;


typedef struct Particle_info_
{

	float distance;
	float weight;
	float t_vector0;
	float t_vector1;
	float t_vector2;

	float r_vector0;
	float r_vector1;
	float r_vector2;

}Particle_info;


typedef struct MeasureResults_
{
	float dist_diff; 
	float angle_diff;
}MeasureResults;




class CMCL_Core
{
public:
	CMCL_Core(void);
	~CMCL_Core(void);

	//float PI;

	//flags

	int flag_for_particle_initialization;


	// transformation matrix
	MatrixXf intrinsicmetrix;
	MatrixXf lowermember_origin;
	MatrixXf lowercenter2leftmarker;
	MatrixXf lowercenter2rightmarker;
	MatrixXf leftcam2uppercenter;
	MatrixXf rightcam2uppercenter;

	// particle initiate (for data input)
	float rot_1[3];
	float trns_1[3];
	float image_1_x[12];
	float image_1_y[12];

	float rot_2[3];
	float trns_2[3];
	float image_2_x[12];
	float image_2_y[12];

	// initial particle generation
	Particle_info best_particle_left, best_particle_right, best_particle_;
	MarkerDataVector markerdata_vector;


	//particle evaluation 
	float resampled_particle_distance_aver;

	float center_of_particle_t_vec[3];
	float center_of_particle_r_vec[3];
	float aver_of_distance_t_vec;
	float aver_of_distance_r_vec;
	float diff_centerofparticle_and_measurement_t_vec;
	float diff_centerofparticle_and_measurement_r_vec;
	//particle regeneration
	float new_tvect_global_stdv;
	float new_rvect_global_stdv;
	float new_tvect_local_stdv;
	float new_rvect_local_stdv;

	float current_tvect_global_stdv;
	float current_rvect_global_stdv;
	float current_tvect_local_stdv;
	float current_rvect_local_stdv;


	FILE *fp;

	FILE *total_result;

	WORD hour,minute,sec,msec;
	SYSTEMTIME t;


private:

	std::vector<Particle_info_> best_pose_;

	MatrixXf MatFormation_4x4(MatrixXf Array);
	MatrixXf MatFormation_3x4_rodrigue(MatrixXf array_rodrigue);

	MatrixXf MatFormation_4x4_rodrigue(MatrixXf array_rodrigue);
	Particle_info VecFormation_from4x4(MatrixXf array_rodrigue);
	MatrixXf MatFormation_4x4fromVector(Particle_info matrix_4x4);
	MatrixXf MatFormation_from4x4_to3x4(MatrixXf matrix_4x4);

	//float calculate_stv(Particle_info resampled);


	Particle_info particle_[NUM_PARTICLE];
	Particle_info particle_resampled[NUM_PARTICLE_RESAMPLED];



	void MCL_particle_calcuation(void);
	IplImage*	particle_image;



public:
//	void get_data(float *rot_1, float *trns_1, float *image_1_x, float *image_1_y, float *rot_2, float *trns_2, float *image_2_x, float *image_2_y);
	void get_data(float *rot_1, float *trns_1, int &get_1_flag, float *rot_2, float *trns_2,int get_2_flag,char* total_save_direct);
	void DO_MCL(void);
	void MCL_initailization(void);
	void particle_initiate(void);
	void particle_evaluate(void);
	void particle_resample(void);
	void particle_regenerate(void);
	
	
	
	void particle_predict_(void);
	void measure_update_(void);
	void MCL_particle_regeneration(void);
	void particle_weight_normal_(void);
	void MCL_visualization(void);


};

#endif /* MCL_H_ */