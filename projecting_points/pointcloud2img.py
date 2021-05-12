#!/usr/bin/env python2
import pcl
import pcl.pcl_visualization
import numpy as np
import math
import rospy
from sensor_msgs.msg import PointCloud2
import sensor_msgs.point_cloud2 as pc2

file_path = '/home/benlee/Desktop/git/point_cloud_practice/pcd_files/data'

class pc2img():
    def __init__(self):
        self.pc_data = 0
        self.cloud_projected = pcl.PointCloud()
        self.pc_size = 0
        self.img_x_size = 0
        self.img_y_size = 0
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
        max_x = round(max(self.img_x),5)
        min_x = round(min(self.img_x),5)
        max_y = round(max(self.img_y),5)
        min_y = round(min(self.img_y),5)
        max_z = round(max(self.img_z),5)
        min_z = round(min(self.img_z),5)
        # print(self.img_x)
        print(" max x value : ", max_x)
        print(" min x value : ", min_x)
        print(" max y value : ", max_y)
        print(" min y value : ", min_y)
        print(" max z value : ", max_z)
        print(" min z value : ", min_z)
        self.img_x_size = max_x - min_x
        self.img_y_size = max_y - min_y 
        print("range x :", max_x - min_x)
        print("range x :", max_y - min_y)
        print("range x :", max_z - min_z)
        
    def visualize(self, pc_data):
        print("visualize start")
        #centred = pc_data - np.mean(pc_data, 0)
        #pc_centred = pcl.PointCloud()
        #pc_centred.from_array(centred)

        visual = pcl.pcl_visualization.CloudViewing()
        visual.ShowMonochromeCloud(pc_data,b'pc_data')
        v = True
        while v:
            v = not(visual.WasStopped())

    def projection_z(self):
        print("Cloud projecting to Z")
        proj = self.pc_data.make_ProjectInliers()
        proj.set_model_type(pcl.SACMODEL_PLANE)
        self.cloud_projected = proj.filter()
        print('Cloud after projection: ')
        print("type :", type(self.cloud_projected))
        print("size :", self.cloud_projected.size)
        print("img size :", round(self.img_x_size*1000,0), round(self.img_y_size*1000))
        imgfinal_x_size = round(self.img_x_size*1000)
        imgfinal_z_size = round(self.img_y_size*1000)
        print("image size :", round(math.sqrt(self.cloud_projected.size)))
        #self.visualize(cloud_projected)

if __name__=="__main__":
    test = pc2img()
    test.read_pcd()
    test.xyz2xy()
    test.projection_z()
    #test.visualize()
    # read_pcd()