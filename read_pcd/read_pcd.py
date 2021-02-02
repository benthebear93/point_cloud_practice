#!/usr/bin/env python2
import pcl
import pcl.pcl_visualization
import numpy as np

import rospy
from sensor_msgs.msg import PointCloud2
import sensor_msgs.point_cloud2 as pc2

file_path = '/home/benlee/Desktop/pc_practice/bunny/data'
def read_pcd():
    print("read pcd")
    #profile_np = np.load(file_path + '/bun000.npy')
    profile_pcd = pcl.load(file_path + '/bun000.pcd')
    visualize(profile_pcd)

def visualize(pc_data):
    print("visualize start")
    #centred = pc_data - np.mean(pc_data, 0)
    #pc_centred = pcl.PointCloud()
    #pc_centred.from_array(centred)

    visual = pcl.pcl_visualization.CloudViewing()
    visual.ShowMonochromeCloud(pc_data,b'pc_data')
    v = True
    while v:
        v = not(visual.WasStopped())

if __name__=="__main__":
    read_pcd()