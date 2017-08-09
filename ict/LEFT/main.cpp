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
	
