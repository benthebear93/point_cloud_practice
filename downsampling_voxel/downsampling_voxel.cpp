#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_gird.h>

int
main (int argc, char** argv)
{
  pcl::PLCPointCloud2::Ptr cloud (new pcl::PLCPointCloud2 ());
  pcl::PLCPointCloud2::Ptr cloud_filtered (new pcl::PLCPointCloud2 ());

  pcl::io::loadPCDFile ("/home/benlee/Desktop/pc_practice/normal_estimation_using_integral_image/table_scene_mug_stereo_textured.pcd", *cloud);
  pcl::VoxelGrid<pcl::PLCPointCloud2> sor;
  sor.setInputCloud (cloud);
  sor.setLeafSize (0.01f, 0.01f, 0.01f);
  sor.filter (*cloud_filtered)

  std::cerr << "Point cloud after filtering" << cloud_filtered->width * cloud_filtered->height << "data points (" << pcl::getFieldList (*cloud_filtered) <<")."<<std::endl;
    
}