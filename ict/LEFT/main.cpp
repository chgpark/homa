#include "MarkerDet.h"
#include "MCL.h"
#include "SerialPort.h"
#include <stdio.h>
#include <pthread.h>
#include <time.h>

CMakerDet			MarkerDet1;
int				thread1 = 0;
CSerialPort			CSPort;
	
char				total_folder_name[50];
int				thread1_flag = 0;
unsigned			
char				save_direct[50];
				*save_file;
int				detected;
float				trns[3];
float				rot[3];
float				trns_filtered[3];
float				rot_filtered[3];
float				trns_compen_filtered[3];
float				rot_compen_filtered[3];

int		main(int ac, char **av)
{
	tm			time;
	GetSystemTime
	sprintf(total_folder_name, "./FIELDTEST_data/%02d%02d%02d", time.wHour, time.wMinute, time.wSecond);
	mkdir(total_folder_name);
	sprintf(save_direct. "%s/result.txt", total_folder_name);
	save_file = fopen(save_direct, "wt");

	MarkerDet1.CmarkerDetInit();

	MarkerDet1.CameraPowerOn(1, NULL);

	int			check_thread1[2] = {0, };
	unsigned		ThreadID1;
	void			*hThread1 = (void *) beginthread(NULL, 0, MyThread1, (void *)&check_thread1, 0, &ThreadID1);
	cSerialPort.portNumber = "COM7";
	cSerialPort.baudrate = CBR_115200;
	cSerialPort.dataBits = 8;
	cSerialPort.stopBits = ONESTOPBIT;
	cSerialPort.parity = NOPARITY;

	MarkerDet1.OnOpenPort((unsigned int)&cSerialPort, NULL);

	while (1)
	{
		
