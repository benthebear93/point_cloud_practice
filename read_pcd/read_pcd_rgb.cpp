#include<iostream>
#include<vector>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/features/normal_3d.h>

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/region_growing.h>

using namespace pcl;
using namespace std;
int user_data;

int main(){
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile ("/home/benlee/Desktop/pc_practice/pcd_files/data/region_growing_tutorial.pcd", *cloud);
    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    
    viewer.showCloud(cloud);
    while (!viewer.wasStopped ())
    {
     user_data++;
    }
    return 0;
}
