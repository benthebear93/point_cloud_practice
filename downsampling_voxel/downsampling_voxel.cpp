#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/cloud_viewer.h>

int user_data = 0;
int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::io::loadPCDFile ("/home/benlee/Desktop/pc_practice/normal_estimation_using_integral_image/table_scene_mug_stereo_textured.pcd", *cloud);
  pcl::VoxelGrid<pcl::PointXYZ> sor;
  sor.setInputCloud (cloud);
  sor.setLeafSize (0.05f, 0.05f, 0.05f);
  sor.filter (*cloud_filtered);
  
    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    viewer.showCloud(cloud_filtered);
    while (!viewer.wasStopped ())
    {
        user_data++;
    }
    return 0;
}