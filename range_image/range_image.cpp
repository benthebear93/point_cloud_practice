#include <pcl/range_image/range_image.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/common/common_headers.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
typedef pcl::PointXYZ PointType;

void 
setViewerPose (pcl::visualization::PCLVisualizer& viewer, const Eigen::Affine3f& viewer_pose)
{
  Eigen::Vector3f pos_vector = viewer_pose * Eigen::Vector3f(0, 0, 0);
  Eigen::Vector3f look_at_vector = viewer_pose.rotation () * Eigen::Vector3f(0, 0, 1) + pos_vector;
  Eigen::Vector3f up_vector = viewer_pose.rotation () * Eigen::Vector3f(0, -1, 0);
  viewer.setCameraPosition (pos_vector[0], pos_vector[1], pos_vector[2],
                            look_at_vector[0], look_at_vector[1], look_at_vector[2],
                            up_vector[0], up_vector[1], up_vector[2]);
}

int main (int argc, char** argv) {
  pcl::PointCloud<pcl::PointXYZ> pointCloud;
  //pcl::PointCloud<PointType>::Ptr pointCloud (new pcl::PointCloud<pcl::PointXYZ>);
  //pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::io::loadPCDFile (  "/home/benlee/Desktop/pc_practice/pcd_files/data/table_scene_lms400.pcd", pointCloud);

  // Generate the data
  // for (float y=-0.5f; y<=0.5f; y+=0.01f) {
  //   for (float z=-0.5f; z<=0.5f; z+=0.01f) {
  //     pcl::PointXYZ point;
  //     point.x = 2.0f - y;
  //     point.y = y;
  //     point.z = z;
  //     pointCloud.points.push_back(point);
  //   }
  // }
  // pointCloud.width = pointCloud.size();
  // pointCloud.height = 1;
  
  // We now want to create a range image from the above point cloud, with a 1deg angular resolution
  float angularResolution = (float) (  1.0f * (M_PI/180.0f));  //   1.0 degree in radians
  float maxAngleWidth     = (float) (360.0f * (M_PI/180.0f));  // 360.0 degree in radians
  float maxAngleHeight    = (float) (180.0f * (M_PI/180.0f));  // 180.0 degree in radians
  Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);
  pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;
  float noiseLevel=0.00;
  float minRange = 0.0f;
  int borderSize = 1;
  std::cout << "cal" <<std::endl;
  
  pcl::RangeImage rangeImage;
  rangeImage.createFromPointCloud(pointCloud, angularResolution, maxAngleWidth, maxAngleHeight,
                                  sensorPose, coordinate_frame, noiseLevel, minRange, borderSize);
  
  std::cout << rangeImage << "\n";

    //visualize point cloud
  boost::shared_ptr<pcl::RangeImage> range_image_ptr(&rangeImage);
  pcl::PointCloud<pcl::PointXYZ>::Ptr point_cloud_ptr (&pointCloud);
  std::cout << "here?" <<std::endl;
  pcl::visualization::PCLVisualizer viewer ("3D viewer");
  viewer.setBackgroundColor(1,1,1);
  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> range_image_color_handler (range_image_ptr, 0, 0, 0); 
  viewer.addPointCloud(range_image_ptr, range_image_color_handler, "range image");
  viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "range image");

  //viewer.addCoordinateSystem(1.0f);
  //pcl::visualization::PointCloudColorHandlerCustom<PointType> point_cloud_color_handler (point_cloud_ptr, 150, 150, 150);
  //viewer.addPointCloud (point_cloud_ptr, point_cloud_color_handler, "original point cloud");


  viewer.initCameraParameters();
  setViewerPose(viewer, rangeImage.getTransformationToWorldSystem());

  pcl::visualization::RangeImageVisualizer widget("please work");
  widget.showRangeImage(rangeImage);
  widget.setSize(500, 500);

  while (!viewer.wasStopped()){
      widget.spinOnce();
      viewer.spinOnce();
      pcl_sleep(.01);
  }  

}