import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import time


class SynchroData:
    def __init__(self):
        self.imu_data_path = './20181229-140634.27928'
        self.log_path = "./5/logcam1.csv"
        self.log_x_path = "./4/logcam1.csv"

        self.fig1, (self.ax1, self.ax2, self. ax3) = plt.subplots(nrows=3, ncols=1)
        self.fig2, (self.ax4, self.ax5, self. ax6, self.ax7) = plt.subplots(nrows=4, ncols=1)
        self.fig3, (self.ax8, self.ax9, self. ax10) = plt.subplots(nrows=3, ncols=1)

        self._set_imu_data_(self.imu_data_path)
        self._set_log_data_(self.log_path)

        self.pd_log_x = pd.read_csv(self.log_x_path, header=None)
        self.pd_log_x = pd.DataFrame(self.pd_log_x.iloc[:][0].str.split('_', 2).tolist()).astype(float)
        self.pd_log_x = self.pd_log_x.iloc[:][0] + self.pd_log_x.iloc[:][1] / 1000

    def _set_imu_data_(self, file_path):
        self.pd_imu = self._read_file_(file_path)
        self.pd_imu_x = pd.DataFrame(self.pd_imu.iloc[:][0].str.split(']', 2).tolist())

    def _set_log_data_(self, file_path):
        self.pd_log = self._read_file_(file_path)

    def _read_file_(self, file_path):
        return pd.read_csv(file_path, header=None)


    def filter_data(self):
        x1 = self.pd_imu_x > self.pd_log_x.iloc[1]
        x2 = self.pd_imu_x < self.pd_log_x.iloc[-1]
        x = self.pd_imu_x[x1][x2]


        self.cal_difference()
        data = self.pd_imu.iloc[:][7][x1][x2].iloc[:]
        self.imu1 = data.iloc[2:].values - data.iloc[0:-2].values
        self.imu1[self.imu1.argmax()] = 0
        self.imu1[self.imu1.argmax()] = 0
        self.imu1[self.imu1.argmin()] = 0
        self.imu1[self.imu1.argmin()] = 0
        self.ax8.plot(x[2:], self.imu1)

        data = self.pd_log.iloc[:][1][2:].values - self.pd_log.iloc[:][1][0:-2].values
        self.log1 = data
        self.ax9.plot(self.pd_log_x[3:], self.log1[1:])


    def cal_difference(self):
        # print(self.imu1)
        print()

    def show_imu(self):
        self.pd_imu_x =self.pd_imu_x.iloc[:][1].astype(float)
        self.pd_imu_x.iloc[209174]=1546064137.1
        x = self.pd_imu_x.iloc[:]
        self.ax1.plot(x, self.pd_imu.iloc[:][7])
        print(x.iloc[self.pd_imu.iloc[:][7].argmax()])
        self.ax2.plot(x, self.pd_imu.iloc[:][8])
        self.ax3.plot(x, self.pd_imu.iloc[:][9])

    def show_log(self):
        x = self.pd_log_x
        self.ax4.plot(x, self.pd_log.iloc[:][1])
        self.ax5.plot(x, self.pd_log.iloc[:][2])
        self.ax6.plot(x, self.pd_log.iloc[:][3])
        self.ax10.plot(x, self.pd_log.iloc[:][4])

if __name__ == '__main__':
    sd = SynchroData()
    sd.show_imu()
    sd.show_log()
    sd.filter_data()
    plt.show()
