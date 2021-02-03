#!/usr/bin/env python2
import pcl
import pcl.pcl_visualization
import numpy as np

import rospy
from sensor_msgs.msg import PointCloud2
import sensor_msgs.point_cloud2 as pc2

file_path = '/home/benlee/Desktop/pc_practice/pcd_files/data'
def read_pcd():
    print("read pcd")
    #profile_np = np.load(file_path + '/table_scene_lms400.npy')
    profile_pcd = pcl.load(file_path + '/table_scene_lms400.pcd')
    in_statistical_outlier_filter_pcd, out_statistical_outlier_filter_pcd = do_statistical_outlier_filter(profile_pcd, 50, 1.0)
    visualize(out_statistical_outlier_filter_pcd)

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

def do_statistical_outlier_filter(pc_data, mean, std):
	print("do statistical outlier filter")
	fil = pc_data.make_statistical_outlier_filter()
	#gaussian setting
	fil.set_mean_k(mean)
	fil.set_std_dev_mul_thresh(std)

	outlier_filtered = fil.filter() 

	fil.set_negative(True)
	inliter_filtered = fil.filter()
	return inliter_filtered, outlier_filtered

if __name__=="__main__":
    read_pcd()