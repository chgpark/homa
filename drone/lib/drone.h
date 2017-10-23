#ifndef DRONE_H
#define DRONE_H

#include <ros/ros.h>
#include <termios.h>
#include "conf.h"
#include "UTM.h"

#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/HomePosition.h>
#include <mavros_msgs/AttitudeTarget.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>

using namespace	ros;
using namespace	std;

class	drone
{
	public:
		struct attitude {
			float			roll;
			float			pitch;
			float			yaw;
		};
		float				dest_lat;
		float				dest_lon;
		float				dest_alt;
		int				check;
		mavros_msgs::HomePosition       hp;
		NodeHandle			nh_drone;
		Subscriber			hp_sub;
		Publisher			local_pub;
		Publisher			pub_atti;
		attitude			get_attitude();
		attitude			attitude_now;
		drone();
		~drone();

		void	hp_set();
		void	local_set();
		void	local_move();
		void	local_pub_func();
		void	pub_atti_func();
		void	set_atti(char type,float value);
		void	pub_atti_now();
		void	init_trgt_atti();
		void	arming_now();
		void	display_status();
		bool	check_offboard();
		bool	check_connected();

	private:
		float				yaw_trgt;
		float				pitch_trgt;
		float				yaw_now;
		float				pitch_now;

		float				local_x;
		float				local_y;
		float				hp_x;
		float				hp_y;

		tf::Matrix3x3			obs_mat;
		tf::Quaternion			q_tf;

		ServiceClient			arming_client;
		Subscriber			local_sub;
		Subscriber			sub_state;
		Subscriber			sub_imu;

		mavros_msgs::State		current_state;
		mavros_msgs::AttitudeTarget	atti_target;
		sensor_msgs::NavSatFix		global_now;
		geometry_msgs::Pose		local_now;
		geometry_msgs::PoseStamped	local_mv;
		geometry_msgs::TwistStamped	current_vel;
		std_msgs::Float64		comp_now;

		void	callback_state(const mavros_msgs::State::ConstPtr& msg);
		void	callback_imu(const sensor_msgs::Imu msg);

		void	HP_Callback(const mavros_msgs::HomePosition::ConstPtr &msg);
		void	global_Callback(const sensor_msgs::NavSatFix::ConstPtr &msg);
		void	local_Callback(const nav_msgs::Odometry::ConstPtr &msg);
		void	comp_Callback(const std_msgs::Float64::ConstPtr &msg);
		void	gpsvel_Callback(const geometry_msgs::TwistStamped::ConstPtr &msg);
};
#endif
