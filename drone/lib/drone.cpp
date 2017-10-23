#include "drone.h"

drone::drone()
{
	sub_state = nh_drone.subscribe<mavros_msgs::State>("mavros/state", 10, &drone::callback_state, this);
	sub_imu = nh_drone.subscribe<sensor_msgs::Imu>("mavros/imu/data",10, &drone::callback_imu, this);
	hp_sub = nh_drone.subscribe<mavros_msgs::HomePosition>("mavros/home_position/home", 100, &drone::HP_Callback, this);
	local_sub = nh_drone.subscribe<nav_msgs::Odometry>("mavros/global_position/local", 100, &drone::local_Callback, this);
	arming_client = nh_drone.serviceClient<mavros_msgs::CommandBool>("/mavros/cmd/arming");
	ROS_INFO("ENDRUN CLASS INITIALIZED");
	local_pub = nh_drone.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 100);
	pub_atti = nh_drone.advertise<mavros_msgs::AttitudeTarget>("/mavros/setpoint_raw/attitude", 100);
}

drone::~drone()
{
}

void drone::init_trgt_atti()
{
	yaw_trgt = attitude_now.yaw;
	pitch_trgt = attitude_now.pitch;
}

bool drone::check_offboard()
{
	return (current_state.mode == "OFFBOARD");
}

bool drone::check_connected()
{
	return current_state.connected;
}
void drone::set_atti(char type,float value)
{
	// TYPE : ['T'hrust, 'P'itch , 'Y'aw]
	switch(type)
	{
		case 'T':
			atti_target.thrust = atti_target.thrust + value;
			cout<<"Thrust : "<< atti_target.thrust<<endl;
			break;
		case 'P':
			pitch_trgt = pitch_trgt + value;
			cout<<"Pitch angle : " << pitch_trgt/3.141592*180 << endl;
			break;
		case 'Y' :
			yaw_trgt = yaw_trgt + value;
			cout<<"Yaw angle : " << yaw_trgt/3.141592*180 <<endl;
			break;
		case 'A':
			pitch_trgt = value;
			cout<<"Pitch angle : " << pitch_trgt/3.141592*180 << endl;
			break;
		case 'B':
			atti_target.thrust = value;
			cout<<"Thrust : "<< atti_target.thrust<<endl;
			break;
		case 'C':
			yaw_trgt = value;
			cout<<"Yaw angle : " << yaw_trgt/3.141592*180 << endl;
			break;
		default : break;
	}
	geometry_msgs::Pose pose_temp = url_common::CVT_mat2geoPose(url_common::CVT_xyzrpy2mat(0,0,0,0,pitch_trgt,yaw_trgt));
	atti_target.orientation = pose_temp.orientation;
}

void	drone::hp_set()
{
	LatLonToUTMXY(hp.geo.latitude, hp.geo.longitude, 0, hp_x, hp_y);
}

void	drone::local_set()
{
	LatLonToUTMXY(dest_lat, dest_lon, 0, local_x, local_y);
	obs_mat.setEulerYPR(attitude_now.roll, attitude_now.pitch, attitude_now.yaw);
	obs_mat.getRotation(q_tf);
	local_mv.pose.position.x = local_x - hp_x;
	local_mv.pose.position.y = local_y - hp_y;
	local_mv.pose.position.z = dest_alt - hp.geo.altitude;

	local_mv.pose.orientation.x = q_tf.getX();
	local_mv.pose.orientation.y = q_tf.getY();
	local_mv.pose.orientation.z = q_tf.getZ();
	local_mv.pose.orientation.w = q_tf.getW();
}

void	drone::local_move()
{
	local_pub.publish(local_mv);
}

void drone::display_status()
{
	cout<<"Yaw : " << attitude_now.yaw / 3.141592 * 180 <<
		" , Pitch : "<< attitude_now.pitch / 3.141592 * 180 <<endl;
	cout<<"Yaw_Target : " << yaw_trgt  / 3.141592 * 180 <<
		" , Pitch_Target : "<< pitch_trgt / 3.141592 * 180 <<endl;
}

void endrun::pub_atti_now()
{
	pub_atti.publish(atti_target);
}

void endrun::arming_now()
{
	mavros_msgs::CommandBool arm_cmd;
	arm_cmd.request.value = true;
	arming_client.call(arm_cmd);
}

endrun::attitude endrun::get_attitude()
{
	return attitude_now;
}

void	endrun::HP_Callback(const mavros_msgs::HomePosition::ConstPtr &msg)
{
	hp.geo = msg->geo;
	/*
	hp.latitude = msg->latitude;
	hp.longitude = msg->longitude;
	hp.altitude = msg->altitude;
	*/
	check = 0;
}

void	endrun::global_Callback(const sensor_msgs::NavSatFix::ConstPtr &msg)
{
	global_now.latitude = msg->latitude;
	global_now.longitude = msg->longitude;
	global_now.altitude = msg->altitude;
}

void	endrun::local_Callback(const nav_msgs::Odometry::ConstPtr &msg)
{
	local_now.position.x = msg->pose.pose.position.x;
	local_now.position.y = msg->pose.pose.position.y;
	local_now.position.z = msg->pose.pose.position.z;
}

void	endrun::comp_Callback(const std_msgs::Float64::ConstPtr &msg)
{
	comp_now = *msg;
}

void endrun::callback_state(const mavros_msgs::State::ConstPtr& msg)
{
	current_state = *msg;
}

void endrun::callback_imu(const sensor_msgs::Imu msg)
{
	float x_imu,y_imu,z_imu,r_imu,p_imu,yaw_imu;
	url_common::CVT_mat2xyzrpy(url_common::CVT_q2mat(msg.orientation.x,msg.orientation.y,msg.orientation.z,msg.orientation.w), &x_imu,&y_imu,&z_imu,&attitude_now.roll,&attitude_now.pitch,&attitude_now.yaw);
}
