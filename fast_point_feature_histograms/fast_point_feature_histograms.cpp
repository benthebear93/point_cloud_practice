#include <pcl/point_types.h>
#include <pcl/features/fpfh.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

int main()
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal> ());
  pcl::io::loadPCDFile ("/home/benlee/Desktop/pc_practice/pcd_files/data/table_scene_lms400.pcd", *cloud);

  pcl::FPFHEstimation<pcl::PointXYZ, pcl::Normal, pcl::FPFHSignature33> fpfh;
  fpfh.setInputCloud (cloud);
  fpfh.setInputNormals (normals);

  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
  fpfh.setSearchMethod (tree);


  pcl::PointCloud<pcl::FPFHSignature33>::Ptr fpfhs (new pcl::PointCloud<pcl::FPFHSignature33> ());

  fpfh.setRadiusSearch (0.05);

  fpfh.compute (*fpfhs);
}