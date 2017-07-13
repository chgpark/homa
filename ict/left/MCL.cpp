#include "MCL.h"
#include <math.h>
#include <random>

char folder_name[50];
char mcl_name[50];

CMCL_Core::CMCL_Core(void)
{
	flag_for_particle_initialization = 0;
	

//	PI = (float)(3.14159265358979);
//	cvNamedWindow("Particle", 0);
//	cvResizeWindow("Particle", 1200, 1200);

	//fp = fopen("mulitmarker.txt","w");

	intrinsicmetrix = MatrixXf::Matrix(3,3);
	lowermember_origin = MatrixXf::Matrix(4,4);
	lowercenter2leftmarker = MatrixXf::Matrix(4,4);
	lowercenter2rightmarker = MatrixXf::Matrix(4,4);
	leftcam2uppercenter = MatrixXf::Matrix(4,4);
	rightcam2uppercenter = MatrixXf::Matrix(4,4);

	//set intrinsic matrix
	intrinsicmetrix(0,0) = CamParm_focal[0];
	intrinsicmetrix(0,1) = 0;
	intrinsicmetrix(0,2) = CamParm_principal[0];
	intrinsicmetrix(1,0) = 0;
	intrinsicmetrix(1,1) = -CamParm_focal[1];
	intrinsicmetrix(1,2) = CamParm_principal[1];
	intrinsicmetrix(2,0) = 0;
	intrinsicmetrix(2,1) = 0;
	intrinsicmetrix(2,2) = 1;

	//set origin 
	lowermember_origin.setZero(); // Lower Member's center position is set to (0,0,0) and rotation is set to (0,0,0)
	lowermember_origin(0,0)=1; 
	lowermember_origin(1,1)=1;
	lowermember_origin(2,2)=1;
	lowermember_origin(3,3)=1;

	// make transformation matrix 
	lowercenter2leftmarker.setZero();
	//set rotation
	lowercenter2leftmarker(0,0)=1; 
	lowercenter2leftmarker(1,1)=1;
	lowercenter2leftmarker(2,2)=1;
	lowercenter2leftmarker(3,3)=1;
	//set translation
	lowercenter2leftmarker(0,3)= OFFSET_LEFT_X; //--x
	lowercenter2leftmarker(1,3)= OFFSET_LEFT_Y; //--y
	lowercenter2leftmarker(2,3)= OFFSET_LEFT_Z; //--z

	
	lowercenter2rightmarker.setZero();
	//set rotation
	lowercenter2rightmarker(0,0)=1; 
	lowercenter2rightmarker(1,1)=1;
	lowercenter2rightmarker(2,2)=1;
	lowercenter2rightmarker(3,3)=1;
	//set translation
	lowercenter2rightmarker(0,3)= -OFFSET_RIGHT_X; //--x
	lowercenter2rightmarker(1,3)= OFFSET_RIGHT_Y; //--y
	lowercenter2rightmarker(2,3)= OFFSET_RIGHT_Z; //--z

	
	leftcam2uppercenter.setZero();
	//set rotation
	leftcam2uppercenter(0,0)=1; 
	leftcam2uppercenter(1,1)=1;
	leftcam2uppercenter(2,2)=1;
	leftcam2uppercenter(3,3)=1;
	//set translation
	leftcam2uppercenter(0,3)= -OFFSET_LEFT_X; //--x
	leftcam2uppercenter(1,3)= OFFSET_LEFT_Y; //--y
	leftcam2uppercenter(2,3)= OFFSET_LEFT_Z; //--z


	rightcam2uppercenter.setZero();
	//set rotation
	rightcam2uppercenter(0,0)=1; 
	rightcam2uppercenter(1,1)=1;
	rightcam2uppercenter(2,2)=1;
	rightcam2uppercenter(3,3)=1;
	//set translation
	rightcam2uppercenter(0,3)= OFFSET_RIGHT_X; //--x
	rightcam2uppercenter(1,3)= OFFSET_RIGHT_Y; //--y
	rightcam2uppercenter(2,3)= OFFSET_RIGHT_Z; //--z


}

CMCL_Core::~CMCL_Core(void)
{
//	fclose(total_result);
}





void CMCL_Core::MCL_initailization(void)
{



}



void CMCL_Core::get_data(float *rot_1, float *trns_1, int &get_1_flag, float *rot_2, float *trns_2,int get_2_flag,char* total_save_direct)
{

	
	//fprintf(total_result, "%d,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f\n", get_1_flag,trns_1[0],trns_1[1],trns_1[2],rot_1[0],rot_1[1],rot_1[2],get_2_flag,trns_2[0],trns_2[1],trns_2[2],rot_2[0],rot_2[1],rot_2[2]);

	

	////input data (vector and image coordinate)
	//for(int i=0; i<3; i++)
	//{
	//	markerdata_vector.rotvect1[i] = rot_1[i];
	//	markerdata_vector.trnsvect1[i] = trns_1[i];
	//	markerdata_vector.rotvect2[i] = rot_2[i];
	//	markerdata_vector.trnsvect2[i] = trns_2[i];
	//}

	//for(int i=0; i<12; i++)
	//{
	//	markerdata_vector.imagecoodinate1_x[i] = image_1_x[i];
	//	markerdata_vector.imagecoodinate1_y[i] = image_1_y[i];
	//	markerdata_vector.imagecoodinate2_x[i] = image_2_x[i];
	//	markerdata_vector.imagecoodinate2_y[i] = image_2_y[i];
	//}


	////transform rotation vector to rotation matrix
	//float rotMat1[9];
	//CvMat srcMat1 = cvMat(3, 1, CV_32F, markerdata_vector.rotvect1);
	//CvMat dstMat1 = cvMat(3, 3, CV_32F, rotMat1);
	//cvRodrigues2(&srcMat1, &dstMat1);

	//float rotMat2[9];
	//CvMat srcMat2 = cvMat(3, 1, CV_32F, markerdata_vector.rotvect2);
	//CvMat dstMat2 = cvMat(3, 3, CV_32F, rotMat2);
	//cvRodrigues2(&srcMat2, &dstMat2);


	////transformation matrix (marker to cam)
	//MatrixXf leftmarker2cam(4,4);
	//MatrixXf leftmarker2cam_array;
	//leftmarker2cam_array = MatrixXf::Matrix(12,1);
	//leftmarker2cam_array(0,0) = rotMat1[0];
	//leftmarker2cam_array(1,0) = rotMat1[1];
	//leftmarker2cam_array(2,0) = rotMat1[2];
	//leftmarker2cam_array(3,0) = rotMat1[3];
	//leftmarker2cam_array(4,0) = rotMat1[4];
	//leftmarker2cam_array(5,0) = rotMat1[5];
	//leftmarker2cam_array(6,0) = rotMat1[6];
	//leftmarker2cam_array(7,0) = rotMat1[7];
	//leftmarker2cam_array(8,0) = rotMat1[8];
	//leftmarker2cam_array(9,0) = markerdata_vector.trnsvect1[0];
	//leftmarker2cam_array(10,0) = markerdata_vector.trnsvect1[1];
	//leftmarker2cam_array(11,0) = markerdata_vector.trnsvect1[2];
	//leftmarker2cam = MatFormation_4x4_rodrigue(leftmarker2cam_array);

	//MatrixXf rightmarker2cam(4,4);
	//MatrixXf rightmarker2cam_array;
	//rightmarker2cam_array = MatrixXf::Matrix(12,1);
	//rightmarker2cam_array(0,0) = rotMat2[0];
	//rightmarker2cam_array(1,0) = rotMat2[1];
	//rightmarker2cam_array(2,0) = rotMat2[2];
	//rightmarker2cam_array(3,0) = rotMat2[3];
	//rightmarker2cam_array(4,0) = rotMat2[4];
	//rightmarker2cam_array(5,0) = rotMat2[5];
	//rightmarker2cam_array(6,0) = rotMat2[6];
	//rightmarker2cam_array(7,0) = rotMat2[7];
	//rightmarker2cam_array(8,0) = rotMat2[8];
	//rightmarker2cam_array(9,0) = markerdata_vector.trnsvect2[0];
	//rightmarker2cam_array(10,0) = markerdata_vector.trnsvect2[1];
	//rightmarker2cam_array(11,0) = markerdata_vector.trnsvect2[2];
	//rightmarker2cam = MatFormation_4x4_rodrigue(rightmarker2cam_array);


	////approximate upper member pose (vector)
	//MatrixXf uppermember_origin_fromleft(4,4);
	//uppermember_origin_fromleft = lowermember_origin*lowercenter2leftmarker*leftmarker2cam*leftcam2uppercenter; //transformation matrix
	//best_particle_left = VecFormation_from4x4(uppermember_origin_fromleft);




	//MatrixXf uppermember_origin_fromright(4,4);
	//uppermember_origin_fromright = lowermember_origin*lowercenter2rightmarker*rightmarker2cam*rightcam2uppercenter; //transformation matrix	
	//best_particle_right = VecFormation_from4x4(uppermember_origin_fromright);

	//////center point check
	////float EulerAngles[3];
	////EulerAngles[0] = atan2(uppermember_origin_fromleft(1,0), uppermember_origin_fromleft(0,0));
	////EulerAngles[1] = asin(-uppermember_origin_fromleft(2,0));
	////EulerAngles[2] = atan2(uppermember_origin_fromleft(2,1), uppermember_origin_fromleft(2,2));
	////pose_info_left.x = (float)(uppermember_origin_fromleft(0,3)/10.0);
	////pose_info_left.y = (float)(uppermember_origin_fromleft(1,3)/10.0);
	////pose_info_left.z = (float)(uppermember_origin_fromleft(2,3)/10.0);
	////pose_info_left.roll = (float)(EulerAngles[0]/PI*180.0);
	////pose_info_left.pitch = (float)(EulerAngles[1]/PI*180.0);
	////pose_info_left.yaw = (float)(EulerAngles[2]/PI*180.0);

	////EulerAngles[0] = atan2(uppermember_origin_fromright(1,0), uppermember_origin_fromright(0,0));
	////EulerAngles[1] = asin(-uppermember_origin_fromright(2,0));
	////EulerAngles[2] = atan2(uppermember_origin_fromright(2,1), uppermember_origin_fromright(2,2));
	////pose_info_right.x = (float)(uppermember_origin_fromright(0,3)/10.0);
	////pose_info_right.y = (float)(uppermember_origin_fromright(1,3)/10.0);
	////pose_info_right.z = (float)(uppermember_origin_fromright(2,3)/10.0);
	////pose_info_right.roll = (float)(EulerAngles[0]/PI*180.0);
	////pose_info_right.pitch = (float)(EulerAngles[1]/PI*180.0);
	////pose_info_right.yaw = (float)(EulerAngles[2]/PI*180.0);


	//best_particle_.t_vector0 = (best_particle_left.t_vector0 + best_particle_right.t_vector0)/2;
	//best_particle_.t_vector1 = (best_particle_left.t_vector1 + best_particle_right.t_vector1)/2;
	//best_particle_.t_vector2 = (best_particle_left.t_vector2 + best_particle_right.t_vector2)/2;
	//best_particle_.r_vector0 = (best_particle_left.r_vector0 + best_particle_right.r_vector0)/2;
	//best_particle_.r_vector1 = (best_particle_left.r_vector1 + best_particle_right.r_vector1)/2;
	//best_particle_.r_vector2 = (best_particle_left.r_vector2 + best_particle_right.r_vector2)/2;

	//best_particle_.weight = 0;


}

void CMCL_Core::DO_MCL(void)
{
	
	MCL_initailization();
	if(flag_for_particle_initialization<5)
	{
		particle_initiate();
	}
	particle_evaluate();
	particle_resample();
	particle_regenerate();
	MCL_visualization();
}


void CMCL_Core::particle_initiate(void)
{



	best_pose_.push_back(best_particle_);

	//distribution(noise) generation
	cv::Mat normal_num_tvect0(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(normal_num_tvect0, cv::Scalar(0.0), cv::Scalar(X_STDV_INITIAL));
	cv::Mat normal_num_tvect1(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(normal_num_tvect1, cv::Scalar(0.0), cv::Scalar(Y_STDY_INITIAL));
	cv::Mat normal_num_tvect2(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(normal_num_tvect2, cv::Scalar(0.0), cv::Scalar(Z_STDY_INITIAL));

	cv::Mat normal_num_rvect0(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(normal_num_rvect0, cv::Scalar(0.0), cv::Scalar(PITCH_STDY_INITIAL));
	cv::Mat normal_num_rvect1(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(normal_num_rvect1, cv::Scalar(0.0), cv::Scalar(ROLL_STDY_INITIAL));
	cv::Mat normal_num_rvect2(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(normal_num_rvect2, cv::Scalar(0.0), cv::Scalar(YAW_STDY_INITIAL));

	for(int i = 0; i < (int)NUM_PARTICLE; i++)
	{
		particle_[i].t_vector0 = best_particle_.t_vector0 + normal_num_tvect0.at<double>(0,i);
		particle_[i].t_vector1 = best_particle_.t_vector1 + normal_num_tvect1.at<double>(0,i);
		particle_[i].t_vector2 = best_particle_.t_vector2 + normal_num_tvect2.at<double>(0,i);
		particle_[i].r_vector0 = best_particle_.r_vector0 + normal_num_rvect0.at<double>(0,i);
		particle_[i].r_vector1 = best_particle_.r_vector1 + normal_num_rvect1.at<double>(0,i);
		particle_[i].r_vector2 = best_particle_.r_vector2 + normal_num_rvect2.at<double>(0,i);
		particle_[i].weight = 0.0;
	}
	char buff_projection1[30];
	FILE *projection1;
	//sprintf(buff_projection1, "particle.txt");
	//projection1 = fopen(buff_projection1,"w");


	//for(int i = 0; i < (int)NUM_PARTICLE; i++)
	//{
	//	fprintf(projection1, "%f %f %f %f %f %f\n", particle_[i].t_vector0, particle_[i].t_vector1, particle_[i].t_vector2, particle_[i].r_vector0, particle_[i].r_vector1, particle_[i].r_vector2);
	//}
	flag_for_particle_initialization++;
}





void CMCL_Core::particle_evaluate(void)
{
	//char buff_projection[30];
	//FILE *projection;
	//sprintf(buff_projection, "match.txt");
	//projection = fopen(buff_projection,"w");


	for(int i = 0; i < (int)NUM_PARTICLE; i++) // i = particles
	{

		MatrixXf projection_to_2D_left(3,1);
		MatrixXf projection_to_2D_right(3,1);
		MatrixXf origin2uppermembercenter(4,4); //particle
		MatrixXf markercoordinate(4,1);

		origin2uppermembercenter = MatFormation_4x4fromVector(particle_[i]); //from particle
		//origin2uppermembercenter = MatFormation_4x4fromVector(best_particle_left); //from particle

		//left
		MatrixXf left_extrinsicparm_generated_from_particle_4x4(4,4); //4x4
		MatrixXf left_extrinsicparm_generated_from_particle_3x4(3,4); //3x4
		left_extrinsicparm_generated_from_particle_4x4 = lowercenter2leftmarker.inverse()*origin2uppermembercenter*leftcam2uppercenter.inverse();
		left_extrinsicparm_generated_from_particle_3x4 = MatFormation_from4x4_to3x4(left_extrinsicparm_generated_from_particle_4x4);
		//right
		MatrixXf right_extrinsicparm_generated_from_particle_4x4(4,4);
		MatrixXf right_extrinsicparm_generated_from_particle_3x4(3,4);
		right_extrinsicparm_generated_from_particle_4x4 = lowercenter2rightmarker.inverse()*origin2uppermembercenter*rightcam2uppercenter.inverse();
		right_extrinsicparm_generated_from_particle_3x4 = MatFormation_from4x4_to3x4(right_extrinsicparm_generated_from_particle_4x4);


		float dist_temp =0;

		float check_projected_x_left;
		float check_projected_y_left;
		float check_projected_x_right;
		float check_projected_y_right;

		float check_image_x_left;
		float check_image_y_left;
		float check_image_right;
		float check_image_y_right;

		//fprintf(projection, "particle%d\n", i);
	

		for(int j = 0; j<(int)MARKER_INPUT_PTS; j++) // j = 12 edge points
		{
			markercoordinate(0,0) = World_XYZ_data[0][j][0]; //x
			markercoordinate(1,0) = World_XYZ_data[0][j][1]; //y
			markercoordinate(2,0) = World_XYZ_data[0][j][2]; //z
			markercoordinate(3,0) = 1;

			//left
			projection_to_2D_left = intrinsicmetrix*left_extrinsicparm_generated_from_particle_3x4*markercoordinate;
			projection_to_2D_left(0,0) = projection_to_2D_left(0,0)/projection_to_2D_left(2,0);
			projection_to_2D_left(1,0) = projection_to_2D_left(1,0)/projection_to_2D_left(2,0);
			//right
			projection_to_2D_right = intrinsicmetrix*right_extrinsicparm_generated_from_particle_3x4*markercoordinate;
			projection_to_2D_right(0,0) = projection_to_2D_right(0,0)/projection_to_2D_right(2,0);
			projection_to_2D_right(1,0) = projection_to_2D_right(1,0)/projection_to_2D_right(2,0);


			 
			//distance calculation and its sum
			dist_temp = dist_temp + sqrt((projection_to_2D_left(0,0) - markerdata_vector.imagecoodinate1_x[j])*(projection_to_2D_left(0,0) - markerdata_vector.imagecoodinate1_x[j]) + 
										 (projection_to_2D_left(1,0) - markerdata_vector.imagecoodinate1_y[j])*(projection_to_2D_left(1,0) - markerdata_vector.imagecoodinate1_y[j])) +
									sqrt((projection_to_2D_right(0,0) - markerdata_vector.imagecoodinate1_x[j])*(projection_to_2D_right(0,0) - markerdata_vector.imagecoodinate1_x[j]) + 
									     (projection_to_2D_right(1,0) - markerdata_vector.imagecoodinate1_y[j])*(projection_to_2D_right(1,0) - markerdata_vector.imagecoodinate1_y[j]));


			//fprintf(projection, "Point number %d: %f %f %f %f %f %f %f %f\n", j, projection_to_2D_left(0,0), markerdata_vector.imagecoodinate1_x[j], projection_to_2D_left(1,0), markerdata_vector.imagecoodinate1_y[j], projection_to_2D_right(0,0),markerdata_vector.imagecoodinate1_x[j], projection_to_2D_right(1,0), markerdata_vector.imagecoodinate1_y[j]);

		}
		//distance average
		particle_[i].distance = dist_temp/((int)MARKER_INPUT_PTS *2);
	}


	//fclose (projection);
}






void CMCL_Core::particle_resample(void)
{
	float sum_of_resampled_particle_distance = 0;
	
	for(int i=0; i<(int)NUM_PARTICLE_RESAMPLED; i++)
	{
		int k=0;
		for(int j=0; j<(int)NUM_PARTICLE; j++)
		{

			if(particle_[k].distance > particle_[j].distance)
			{
				k=j;
			}
		}
		//// give weight according to distance 
		//particle_[k].weight = (int)NUM_PARTICLE_DISTANCE;
		printf("%d_%d_%d\n", i,  k, (int)particle_[k].distance);

		
		particle_resampled[i] = particle_[k];
		sum_of_resampled_particle_distance = sum_of_resampled_particle_distance+ particle_resampled[i].distance;
		//now k-th is the best
		particle_[k].distance = 1000000000; //erase best one to re compare
	}
	
	resampled_particle_distance_aver = sum_of_resampled_particle_distance / (int)NUM_PARTICLE_RESAMPLED;
	

	
	//re sampled particle analysis for regeneration

	// center of vector
	float sum_of_particle_t_vec[3] = {0,};
	float sum_of_particle_r_vec[3] = {0,};

	for(int i=0; i<(int)NUM_PARTICLE_RESAMPLED; i++)
	{
		sum_of_particle_t_vec[0] = sum_of_particle_t_vec[0] + particle_resampled[i].t_vector0;
		sum_of_particle_t_vec[1] = sum_of_particle_t_vec[1] + particle_resampled[i].t_vector1;
		sum_of_particle_t_vec[2] = sum_of_particle_t_vec[2] + particle_resampled[i].t_vector2;

		sum_of_particle_r_vec[0] = sum_of_particle_r_vec[0] + particle_resampled[i].r_vector0;
		sum_of_particle_r_vec[1] = sum_of_particle_r_vec[1] + particle_resampled[i].r_vector1;
		sum_of_particle_r_vec[2] = sum_of_particle_r_vec[2] + particle_resampled[i].r_vector2;
	}
	for(int i=0; i<3; i++)
	{
	center_of_particle_t_vec[i] = sum_of_particle_t_vec[i]/(int)NUM_PARTICLE_RESAMPLED;
	center_of_particle_r_vec[i] = sum_of_particle_r_vec[i]/(int)NUM_PARTICLE_RESAMPLED;
	}
	// average of vector distance 
	float sum_of_distance_t_vec = 0;
	float sum_of_distance_r_vec = 0;

	for(int i=0; i<(int)NUM_PARTICLE_RESAMPLED; i++)
	{
		sum_of_distance_t_vec = sum_of_distance_t_vec + sqrt(
		(center_of_particle_t_vec[0] - particle_resampled[i].t_vector0)*(center_of_particle_t_vec[0] - particle_resampled[i].t_vector0) + 
		(center_of_particle_t_vec[1] - particle_resampled[i].t_vector1)*(center_of_particle_t_vec[1] - particle_resampled[i].t_vector1) +
		(center_of_particle_t_vec[2] - particle_resampled[i].t_vector2)*(center_of_particle_t_vec[2] - particle_resampled[i].t_vector2) );

		sum_of_distance_r_vec = sum_of_distance_r_vec + sqrt(
		(center_of_particle_r_vec[0] - particle_resampled[i].r_vector0)*(center_of_particle_r_vec[0] - particle_resampled[i].r_vector0) + 
		(center_of_particle_r_vec[1] - particle_resampled[i].r_vector1)*(center_of_particle_r_vec[1] - particle_resampled[i].r_vector1) +
		(center_of_particle_r_vec[2] - particle_resampled[i].r_vector2)*(center_of_particle_r_vec[2] - particle_resampled[i].r_vector2) );
	}
	aver_of_distance_t_vec = sum_of_distance_t_vec/(int)NUM_PARTICLE_RESAMPLED;
	aver_of_distance_r_vec = sum_of_distance_r_vec/(int)NUM_PARTICLE_RESAMPLED;

	diff_centerofparticle_and_measurement_t_vec = sqrt((center_of_particle_t_vec[0] -  best_particle_.t_vector0)*(center_of_particle_t_vec[0] -  best_particle_.t_vector0)+
													   (center_of_particle_t_vec[1] -  best_particle_.t_vector1)*(center_of_particle_t_vec[1] -  best_particle_.t_vector1)+
													   (center_of_particle_t_vec[2] -  best_particle_.t_vector2)*(center_of_particle_t_vec[2] -  best_particle_.t_vector2));
	diff_centerofparticle_and_measurement_r_vec = sqrt((center_of_particle_r_vec[0] -  best_particle_.r_vector0)*(center_of_particle_r_vec[0] -  best_particle_.r_vector0)+
													   (center_of_particle_r_vec[1] -  best_particle_.r_vector1)*(center_of_particle_r_vec[1] -  best_particle_.r_vector1)+
													   (center_of_particle_r_vec[2] -  best_particle_.r_vector2)*(center_of_particle_r_vec[2] -  best_particle_.r_vector2));



	printf("\n\n");
}



void CMCL_Core::particle_regenerate(void)
{
	//assign global/local particle
	int num_global_particle = (int)NUM_PARTICLE * (float)RATIO_GLOBAL_PARTICLE;
	int num_local_particle = (int)NUM_PARTICLE - num_global_particle;

	//global particle generation//
	//global distribution set
	float global_distribution_tvect = diff_centerofparticle_and_measurement_t_vec*(float)GLOGAL_PARTICLE_DISTRIBUTION;
	float global_distribution_rvect = diff_centerofparticle_and_measurement_r_vec*(float)GLOGAL_PARTICLE_DISTRIBUTION;

	//global distribution(noise) generation
	cv::Mat global_tvect0(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(global_tvect0, cv::Scalar(0.0), cv::Scalar(global_distribution_tvect));
	cv::Mat global_tvect1(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(global_tvect1, cv::Scalar(0.0), cv::Scalar(global_distribution_tvect));
	cv::Mat global_tvect2(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(global_tvect2, cv::Scalar(0.0), cv::Scalar(global_distribution_tvect));

	cv::Mat global_rvect0(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(global_rvect0, cv::Scalar(0.0), cv::Scalar(global_distribution_rvect));
	cv::Mat global_rvect1(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(global_rvect1, cv::Scalar(0.0), cv::Scalar(global_distribution_rvect));
	cv::Mat global_rvect2(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(global_rvect2, cv::Scalar(0.0), cv::Scalar(global_distribution_rvect));

	for(int i = 0; i < num_global_particle; i++)
	{
		particle_[i].t_vector0 = center_of_particle_t_vec[0] + global_tvect0.at<double>(0,i);
		particle_[i].t_vector1 = center_of_particle_t_vec[1] + global_tvect1.at<double>(0,i);
		particle_[i].t_vector2 = center_of_particle_t_vec[2] + global_tvect2.at<double>(0,i);
		particle_[i].r_vector0 = center_of_particle_r_vec[0] + global_rvect0.at<double>(0,i);
		particle_[i].r_vector1 = center_of_particle_r_vec[1] + global_rvect1.at<double>(0,i);
		particle_[i].r_vector2 = center_of_particle_r_vec[2] + global_rvect2.at<double>(0,i);
		particle_[i].weight = 0.0;
	}

	//local particle generation//
	//local distribution set
	float local_distribution_tvect = aver_of_distance_t_vec*(float)LOCAL_PARTICLE_DISTRIBUTION;
	float local_distribution_rvect = aver_of_distance_r_vec*(float)LOCAL_PARTICLE_DISTRIBUTION;

	//local distribution(noise) generation
	cv::Mat local_tvect0(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(local_tvect0, cv::Scalar(0.0), cv::Scalar(local_distribution_tvect));
	cv::Mat local_tvect1(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(local_tvect1, cv::Scalar(0.0), cv::Scalar(local_distribution_tvect));
	cv::Mat local_tvect2(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(local_tvect2, cv::Scalar(0.0), cv::Scalar(local_distribution_tvect));

	cv::Mat local_rvect0(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(local_rvect0, cv::Scalar(0.0), cv::Scalar(local_distribution_rvect));
	cv::Mat local_rvect1(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(local_rvect1, cv::Scalar(0.0), cv::Scalar(local_distribution_rvect));
	cv::Mat local_rvect2(1, NUM_PARTICLE, CV_64FC1);
	cv::randn(local_rvect2, cv::Scalar(0.0), cv::Scalar(local_distribution_rvect));


	
	int num_particle_division = num_local_particle / (int)NUM_PARTICLE_RESAMPLED;


	int j = 0; // for division
	int k;
	for(int i = 0; i<num_local_particle; i++)
	{
		k = i + num_global_particle;

		particle_[k].t_vector0 = particle_resampled[j].t_vector0 + local_tvect0.at<double>(0,i);
		particle_[k].t_vector1 = particle_resampled[j].t_vector1 + local_tvect1.at<double>(0,i);
		particle_[k].t_vector2 = particle_resampled[j].t_vector2 + local_tvect2.at<double>(0,i);
		particle_[k].r_vector0 = particle_resampled[j].r_vector0 + local_rvect0.at<double>(0,i);
		particle_[k].r_vector1 = particle_resampled[j].r_vector1 + local_rvect1.at<double>(0,i);
		particle_[k].r_vector2 = particle_resampled[j].r_vector2 + local_rvect2.at<double>(0,i);
		particle_[k].weight = 0.0;

		if(i%num_particle_division == 0) 
		{
			if(i==0)
				j++;
		}
	}


}




void CMCL_Core::MCL_visualization(void)
{


	particle_image = cvCreateImage(cvSize((int)VISUALIZATION_WIDTH, (int)VISUALIZATION_HEIGHT),IPL_DEPTH_8U, 3);
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 1, 1, 0, 2, 15);

	char num1[30];



	//image size 10000x10000
	//-------------- x-y view --------------//
	int imagecenter_x = 5000;
	int imagecenter_y = 2500;
	int imagecenter_lower_y = 9500;
	int memberdemension_x = 9000; 
	int memberdemension_y = 3000; 

	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 5, 5, 0, 5, 15);
	//cvPutText (particle_image, "CENTER", cvPoint((int)particle_[0].x+imagecenter_x, (int)particle_[0].y+2000), &font, CV_RGB(0,255,0));


	// normal distribution
	for(int i=0; i<NUM_PARTICLE; i++)
	{
		cvCircle(particle_image,cvPoint((int)particle_[i].t_vector0 +imagecenter_x, (int)particle_[i].t_vector1 +imagecenter_y), 30, CV_RGB(0, 255, 0), 1, 8, 0);  
		cvCircle(particle_image,cvPoint((int)particle_[i].t_vector0 +imagecenter_x, imagecenter_lower_y -(int)particle_[i].t_vector2), 30, CV_RGB(0, 255, 0), 1, 8, 0); 
	}

	cvCircle(particle_image,cvPoint((int)best_particle_.t_vector0 +imagecenter_x, (int)best_particle_.t_vector1 +imagecenter_y), 30, CV_RGB(0, 0, 255), 10, 8, 0);  
	cvCircle(particle_image,cvPoint((int)best_particle_.t_vector0 +imagecenter_x, imagecenter_lower_y -best_particle_.t_vector2), 30, CV_RGB(0, 0, 255), 10, 8, 0);







	cvLine(particle_image, cvPoint(imagecenter_x-memberdemension_x/2, imagecenter_y-memberdemension_y/2),cvPoint(imagecenter_x+memberdemension_x/2, imagecenter_y-memberdemension_y/2), CV_RGB(255, 255, 255), 10, 8, 0);
	cvLine(particle_image, cvPoint(imagecenter_x+memberdemension_x/2, imagecenter_y-memberdemension_y/2),cvPoint(imagecenter_x+memberdemension_x/2, imagecenter_y+memberdemension_y/2), CV_RGB(255, 255, 255), 10, 8, 0);
	cvLine(particle_image, cvPoint(imagecenter_x+memberdemension_x/2, imagecenter_y+memberdemension_y/2),cvPoint(imagecenter_x-memberdemension_x/2, imagecenter_y+memberdemension_y/2), CV_RGB(255, 255, 255), 10, 8, 0);
	cvLine(particle_image, cvPoint(imagecenter_x-memberdemension_x/2, imagecenter_y+memberdemension_y/2),cvPoint(imagecenter_x-memberdemension_x/2, imagecenter_y-memberdemension_y/2), CV_RGB(255, 255, 255), 10, 8, 0);

	cvShowImage("Particle", particle_image); //15000, 5000 
	cvSetZero(particle_image);


	//-------------- x-z view --------------//

	cvLine(particle_image, cvPoint(imagecenter_x-memberdemension_x/2, imagecenter_lower_y),cvPoint(imagecenter_x+memberdemension_x/2, imagecenter_lower_y), CV_RGB(255, 255, 255), 10, 8, 0);
	cvLine(particle_image, cvPoint(imagecenter_x-memberdemension_x/2, imagecenter_lower_y),cvPoint(imagecenter_x-memberdemension_x/2, 5500), CV_RGB(255, 255, 255), 10, 8, 0);


	cvReleaseImage(&particle_image);



}


MatrixXf CMCL_Core::MatFormation_4x4(MatrixXf Array)
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

	tmp(0,0) = c_q2*c_q3;
	tmp(1,0) = s_q1*s_q2*c_q3+c_q1*s_q3;
	tmp(2,0) = -c_q1*s_q2*c_q3+s_q1*s_q3;
	tmp(3,0) = 0;

	tmp(0,1) = -c_q2*s_q3;
	tmp(1,1) = -s_q1*s_q2*s_q3+c_q1*c_q3;
	tmp(2,1) = c_q1*s_q2*s_q3+s_q1*c_q3;
	tmp(3,1) = 0;

	tmp(0,2) = s_q2;
	tmp(1,2) = -s_q1*c_q2;
	tmp(2,2) = c_q1*c_q2;
	tmp(3,2) = 0;

	tmp(0,3) = x;
	tmp(1,3) = y;
	tmp(2,3) = z;
	tmp(3,3) = 1;


	return tmp;
}



MatrixXf CMCL_Core::MatFormation_3x4_rodrigue(MatrixXf array_rodrigue)
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


	return tmp;
}



MatrixXf CMCL_Core::MatFormation_4x4_rodrigue(MatrixXf array_rodrigue)
{
	float r11=array_rodrigue(0,0), r12=array_rodrigue(1,0), r13 =array_rodrigue(2,0), 
		r21=array_rodrigue(3,0), r22=array_rodrigue(4,0), r23=array_rodrigue(5,0), 
		r31=array_rodrigue(6,0), r32=array_rodrigue(7,0), r33=array_rodrigue(8,0),
		t1=array_rodrigue(9,0), t2=array_rodrigue(10,0), t3=array_rodrigue(11,0);

	MatrixXf tmp(4,4);


	//ZYX angles:
	tmp(0,0) = r11;
	tmp(1,0) = r21;
	tmp(2,0) = r31;
	tmp(3,0) = 0;

	tmp(0,1) = r12;
	tmp(1,1) = r22;
	tmp(2,1) = r32;
	tmp(3,1) = 0;

	tmp(0,2) = r13;
	tmp(1,2) = r23;
	tmp(2,2) = r33;
	tmp(3,2) = 0;

	tmp(0,3) = t1;
	tmp(1,3) = t2;
	tmp(2,3) = t3;
	tmp(3,3) = 1;


	return tmp;
}

Particle_info CMCL_Core::VecFormation_from4x4(MatrixXf matrix_4x4)
{
	float r00=matrix_4x4(0,0), r01=matrix_4x4(0,1), r02=matrix_4x4(0,2), t03 =matrix_4x4(0,3),
		r10=matrix_4x4(1,0), r11=matrix_4x4(1,1), r12=matrix_4x4(1,2), t13 =matrix_4x4(1,3),
		r20=matrix_4x4(2,0), r21=matrix_4x4(2,1), r22=matrix_4x4(2,2), t23 =matrix_4x4(2,3),
		r30=matrix_4x4(3,0), t31=matrix_4x4(3,1), t32=matrix_4x4(3,2), t33 =matrix_4x4(3,3);

	float rotVet_temp[3];
	float rotMat_temp[9];

	rotMat_temp[0] = r00; rotMat_temp[1] = r01; rotMat_temp[2] = r02;
	rotMat_temp[3] = r10; rotMat_temp[4] = r11; rotMat_temp[5] = r12;
	rotMat_temp[6] = r20; rotMat_temp[7] = r21; rotMat_temp[8] = r22;


	CvMat srcMat_temp = cvMat(3, 3, CV_32F, rotMat_temp);
	CvMat dstVec_temp = cvMat(3, 1, CV_32F, rotVet_temp);

	cvRodrigues2(&srcMat_temp, &dstVec_temp);

	Particle_info temp;

	temp.t_vector0 = t03;
	temp.t_vector1 = t13;
	temp.t_vector2 = t23;
	temp.r_vector0 = rotVet_temp[0];
	temp.r_vector1 = rotVet_temp[1];
	temp.r_vector2 = rotVet_temp[2];
	temp.weight = 0;

	return temp;
}

MatrixXf CMCL_Core::MatFormation_4x4fromVector(Particle_info particle_vectors)
{
	float rotVet_temp[3];
	float rotMat_temp[9];
	MatrixXf temp(4,4);

	rotVet_temp[0] = particle_vectors.r_vector0;
	rotVet_temp[1] = particle_vectors.r_vector1;
	rotVet_temp[2] = particle_vectors.r_vector2;


	CvMat srcVec_temp = cvMat(3, 1, CV_32F, rotVet_temp);
	CvMat dstMat_temp = cvMat(3, 3, CV_32F, rotMat_temp);

	cvRodrigues2(&srcVec_temp, &dstMat_temp);


	temp(0,0) = rotMat_temp[0];
	temp(1,0) = rotMat_temp[3];
	temp(2,0) = rotMat_temp[6];
	temp(3,0) = 0;

	temp(0,1) = rotMat_temp[1];
	temp(1,1) = rotMat_temp[4];
	temp(2,1) = rotMat_temp[7];
	temp(3,1) = 0;

	temp(0,2) = rotMat_temp[2];
	temp(1,2) = rotMat_temp[5];
	temp(2,2) = rotMat_temp[8];
	temp(3,2) = 0;

	temp(0,3) = particle_vectors.t_vector0;
	temp(1,3) = particle_vectors.t_vector1;
	temp(2,3) = particle_vectors.t_vector2;
	temp(3,3) = 1;


	return temp;
}


MatrixXf CMCL_Core::MatFormation_from4x4_to3x4(MatrixXf matrix_4x4)
{
	MatrixXf temp(3,4);

	temp(0,0) = matrix_4x4(0,0); 
	temp(1,0) = matrix_4x4(1,0); 
	temp(2,0) = matrix_4x4(2,0); 

	temp(0,1) = matrix_4x4(0,1); 
	temp(1,1) = matrix_4x4(1,1); 
	temp(2,1) = matrix_4x4(2,1); 

	temp(0,2) = matrix_4x4(0,2); 
	temp(1,2) = matrix_4x4(1,2); 
	temp(2,2) = matrix_4x4(2,2); 

	temp(0,3) = matrix_4x4(0,3); 
	temp(1,3) = matrix_4x4(1,3); 
	temp(2,3) = matrix_4x4(2,3); 

	return temp;
}


//float CMCL_Core::calculate_stv(Particle_info resampled)
//{
//	int n = sizeof(array), i;
//	float sum_of_array = 0, mean_of_array, var_of_array;
//	for(i=0;i<n;i++)
//	{
//		sum_of_array = array[i];
//	}
//	mean_of_array = sum_of_array/n;
//
//	sum_of_array = 0;
//	for(i=0;i<n;i++)
//	{
//		sum_of_array = sum_of_array + (array[i]-mean_of_array)*(array[i]-mean_of_array);
//	}
//	var_of_array = sum_of_array/(n-1);
//
//	return sqrt(var_of_array);
//}