#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/conditional_removal.h>
#include <vector>

int user_data = 0;
int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::io::loadPCDFile ("/home/benlee/Desktop/pc_practice/normal_estimation_using_integral_image/table_scene_mug_stereo_textured.pcd", *cloud);
  if (!cloud->is_dense)
  {
    cloud->is_dense = false;
    std::vector<int> indices;
    pcl::removeNaNFromPointCloud(*cloud,*cloud, indices);
  }
  pcl::ConditionAnd<pcl::PointXYZ>::Ptr range_cond (new pcl::ConditionAnd<pcl::PointXYZ> ());
  range_cond->addComparison (pcl::FieldComparison<pcl::PointXYZ>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZ> ("z", pcl::ComparisonOps::GT, 0.0)));
  range_cond->addComparison (pcl::FieldComparison<pcl::PointXYZ>::ConstPtr (new pcl::FieldComparison<pcl::PointXYZ> ("z", pcl::ComparisonOps::LT, 0.8)));
  pcl::ConditionalRemoval<pcl::PointXYZ> condrem;
  condrem.setCondition (range_cond);
  condrem.setInputCloud (cloud);
  condrem.setKeepOrganized(true);
  condrem.filter(*cloud_filtered);
  pcl::visualization::CloudViewer viewer("Cloud Viewer");
  viewer.showCloud(cloud_filtered);
  while (!viewer.wasStopped ())
  {
      user_data++;
  }
  return 0;
}