import matplotlib.pyplot as plt
import numpy as np
import time
import os
import cv2
import rospy

from geometry_msgs.msg import Vector3

class IMUtalker:
    def __init__(self):
        rospy.init_node('imu_talker_node')
        self.pub = rospy.Publisher('imu_talker', Vector3, queue_size=10)
        self.rate = rospy.Rate(10)
        self.msg = Vector3()

    def run(self):
        datadir = '/home/data1/Sx/SxMultiCamCalib/data/stitching/Log_181229/Log_2_181229'
        filename = '20181229-140634.27928'
        imgname_base = "SxImageInfo_1_18415794-"

        filepath = os.path.join(datadir, filename)

        file = open(filepath, 'r')

        for i in range(0, 5):
            temp = file.readline()
        # loop to update the data
        for line in file.readlines():
            try:
                dataline = line.split(' ')
                field = dataline[4].strip().split('\t')

                time = field[0]
                self.msg.x = float(field[7])
                self.msg.y = float(field[8])
                self.msg.z = float(field[9])
                self.pub.publish(self.msg)
                self.rate.sleep()

            except KeyboardInterrupt:
                break


if __name__ =='__main__':
    ital = IMUtalker()
    ital.run()


