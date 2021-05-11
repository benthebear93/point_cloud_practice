#!/usr/bin/env python2
import pcl
import pcl.pcl_visualization
import numpy as np

import rospy
from sensor_msgs.msg import PointCloud2
import sensor_msgs.point_cloud2 as pc2

file_path = '/home/benlee/Desktop/git/point_cloud_practice/pcd_files/data'

class pc2img():
    def __init__(self):
        self.pc_data = 0
        self.pc_size = 0
        self.img_x = []
        self.img_y = []
        self.img_z = []
        self.img_xy = []
        
    def read_pcd(self):
        print("read pcd")
        #profile_np = np.load(file_path + '/bun000.npy')
        profile_pcd = pcl.load(file_path + '/passfilter_pc.pcd')
        self.pc_data = profile_pcd
        self.pc_size = profile_pcd.size
        #visualize(profile_pcd)
        # print("type : ", type(profile_pcd))
        print("size : ", profile_pcd.size)
        # print("x : ", profile_pcd[0])
    
    def xyz2xy(self):
        for i in range(self.pc_size):
            self.img_x.append(self.pc_data[i][0])
            self.img_y.append(self.pc_data[i][1])
            self.img_z.append(self.pc_data[i][2])
        # print(self.img_x)
        print(" max x value : ", round(max(self.img_x),5))
        print(" min x value : ", round(min(self.img_x),5))
        print(" max y value : ", round(max(self.img_y),5))
        print(" min y value : ", round(min(self.img_y),5))
        print(" max z value : ", round(max(self.img_z),5))
        print(" min z value : ", round(min(self.img_z),5))

    def visualize(self):
        print("visualize start")
        #centred = pc_data - np.mean(pc_data, 0)
        #pc_centred = pcl.PointCloud()
        #pc_centred.from_array(centred)

        visual = pcl.pcl_visualization.CloudViewing()
        visual.ShowMonochromeCloud(self.pc_data,b'pc_data')
        v = True
        while v:
            v = not(visual.WasStopped())

if __name__=="__main__":
    test = pc2img()
    test.read_pcd()
    test.xyz2xy()
    #test.visualize()
    # read_pcd()