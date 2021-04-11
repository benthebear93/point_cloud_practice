#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/openni_grabber.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>

class SimpleOpenNIViewer
{
  public:
  SimpleOpenNIViewer():
  viewer("point cloud compression ex")
  {

  }
  void cloud_cd_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
  {
    if(!viewer.wasStopped())
    {
      std::stringstream compressedData;
      // output pointcloud
      pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloudOut (new pcl::PointCloud<pcl::PointXYZRGBA> ());
      PointCloudEncoder->encodePointCloud (cloud, compressedData);
      PointCloudDecoder->decodePointCloud (compressedData, cloudOut);
      viewer.showCloud(cloudOut);
    }
  }
  
  void run()
  {
    bool showStatistics = true;
    pcl::io::compression_Profiles_e compressionProfile = pcl::io::MED_RES_ONLINE_COMPRESSION_WITH_COLOR;
    PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA> (compressionProfile, showStatistics);
    PointCloudDecoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA> ();

  }
}