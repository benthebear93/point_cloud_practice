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
    passfiltered_pcd = do_pass_through_filtering(profile_pcd)
    visualize(passfiltered_pcd)

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

def do_pass_through_filtering(pc_data):
	print("passthroguh start")
	passthrough = pc_data.make_passthrough_filter()
	passthrough.set_filter_field_name("z")
	passthrough.set_filter_limits(0.03, 0.04)

	return passthrough.filter()

if __name__=="__main__":
    read_pcd()