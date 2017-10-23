#include "lib/drone.h"

#define TAKEOFF_ALT 2
#define LATITUDE 47.397742
#define LONGITUDE 8.545594
#define ALTITUDE 4
#define SITL

#ifdef SITL
#include "mavros_msgs/SetMode.h"
#endif
using namespace ros;

char	getch();

int	main(int argc, char **argv)
{

	init(argc, argv, "los");
	drone				drone_class = drone();
	char				input_keyboard;
	Time				last_request;
	Rate				loop_rate(20.0);

	drone_class.check = 1;
	while (ok() && !drone_class.check_connected() && drone_class.check)
	{
		ROS_INFO("1");
		spinOnce();
		loop_rate.sleep();
	}
	drone_class.hp_sub.shutdown();
	last_request = Time::now();
	drone_class.hp_set();
#ifdef SITL
	ServiceClient set_mode_client = drone_class.nh_drone.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
	mavros_msgs::SetMode offb_set_mode;
	offb_set_mode.request.custom_mode = "OFFBOARD";
#endif
	while (ok())
	{
		if (!drone_class.check_offboard() && (Time::now() - last_request > Duration(5.0)))
		{
			ROS_INFO("Current Mode isn't OFFBOARD");
			last_request = Time::now();

#ifdef SITL
			if (set_mode_client.call(offb_set_mode))
			{
				ROS_INFO("Offboard enabled");
				ROS_INFO("Wait For Data Receive");
				sleep(10);
				drone_class.init_trgt_atti();
				ROS_INFO("Target Attitude Reset Finish");
			}
#endif

		}
		input_keyboard = getch();
		if (input_keyboard!=0)
		{
			switch (input_keyboard)
			{
				case '1':
					drone_class.local_pub.shutdown();
					break;
				case '2':
					drone_class.pub_atti.shutdown();
					break;
				case 'z':
					drone_class.arming_now();
					break;
				case 't':
					drone_class.dest_lat = drone_class.hp.geo.latitude;
					drone_class.dest_lon = drone_class.hp.geo.longitude;
					drone_class.dest_alt = drone_class.hp.geo.altitude + TAKEOFF_ALT;
					drone_class.attitude_now.roll = 0;
					drone_class.attitude_now.pitch = 0;
					drone_class.attitude_now.yaw = 0;
					drone_class.local_set();
					drone_class.local_move();
					break;
				case 'g':
					drone_class.dest_lat = LATITUDE;
					drone_class.dest_lon = LONGITUDE;
					drone_class.dest_alt = drone_class.hp.geo.altitude + ALTITUDE;
					drone_class.attitude_now.roll = 0;
					drone_class.attitude_now.pitch = 0;
					drone_class.attitude_now.yaw = 0;
					drone_class.local_set();
					drone_class.local_move();
					break;
				case 'l' :
					while (input_keyboard != 'x')
					{
						input_keyboard = getch();
						if (input_keyboard != 0)
						{
							switch (input_keyboard)
							{
								case 'e' :
									drone_class.set_atti('T',0.01);
									break;
								case 'c' :
									drone_class.set_atti('T',-0.01);
									break;
								case 'w' :
									drone_class.set_atti('P',0.05);
									break;
								case 's' :
									drone_class.set_atti('P',-0.05);
									break;
								case 'a' :
									drone_class.set_atti('Y',-0.1);
									break;
								case 'd' :
									drone_class.set_atti('Y',0.1);
									break;
								case 'i':
									drone_class.display_status();
									break;
								case '[':
									drone_class.init_trgt_atti();
									ROS_INFO("Target Attitude Reset Finish");
									break;
								default :
									break;
							}
						}
						drone_class.pub_atti_now();
						spinOnce();
						loop_rate.sleep();
					}
					break;
				default :
					break;
			}
		}
		drone_class.local_move();
		spinOnce();
		loop_rate.sleep();
	}
	return 0;
}

char	getch()
{
	fd_set set;
	struct timeval timeout;
	int rv;
	char buff = 0;
	int len = 1;
	int filedesc = 0;
	FD_ZERO(&set);
	FD_SET(filedesc, &set);

	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;

	rv = select(filedesc + 1, &set, NULL, NULL, &timeout);

	struct termios old = {0};
	if (tcgetattr(filedesc, &old) < 0)
		ROS_ERROR("tcsetattr()");
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(filedesc, TCSANOW, &old) < 0)
		ROS_ERROR("tcsetattr ICANON");

	if(rv == -1)
		ROS_ERROR("select");
	//else if(rv == 0)
	//ROS_INFO("no_key_pressed");
	else if(rv != 0)
		read(filedesc, &buff, len );

	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
		ROS_ERROR ("tcsetattr ~ICANON");
	return (buff);
}
