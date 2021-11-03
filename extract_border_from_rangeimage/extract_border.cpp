#include <pcl/range_image/range_image.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/range_image_visualizer.h>
#include <pcl/common/common_headers.h>
#include <pcl/visualization/point_cloud_color_handlers.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/features/range_image_border_extractor.h>
#include <pcl/console/parse.h>
#include <pcl/common/file_io.h> // for getFilenameWithoutExtension
#include <string>

typedef pcl::PointXYZ PointType;

float angular_resolution= 0.01f;
pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;
bool setUnseenToMaxRange = false;

int main (int argc, char** argv) {
	std::string filepath = "/home/benlee/Desktop/git/point_cloud_practice/extract_border_from_rangeimage"; // basic file path

	float angular_resolution= 0.5f;
	angular_resolution = pcl::deg2rad (angular_resolution);

	bool setUnseenToMaxRange = false;
	setUnseenToMaxRange = true;
	int tmp_coordinate_frame;

	typedef pcl::PointXYZ PointType;
	pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;

	pcl::PointCloud<PointType>::Ptr point_cloud_ptr (new pcl::PointCloud<PointType>); // making point cloUd
	pcl::PointCloud<PointType>& point_cloud = *point_cloud_ptr; // getting address
	pcl::PointCloud<pcl::PointWithViewpoint> far_ranges; // set range

	Eigen::Affine3f scene_sensor_pose (Eigen::Affine3f::Identity ()); // set sensor pose
	std::string filename = filepath + "/new_cluster4.pcd";

	pcl::io::loadPCDFile (filename, point_cloud);
	scene_sensor_pose = Eigen::Affine3f (Eigen::Translation3f (0.678,
	                                                         0.0535,
	                                                        -0.252) ) *
	                  Eigen::Affine3f ( Eigen::Quaternionf(0.00002, 0.707, 0.000058, 0.7071));
	std::cout<< "sensor origin: cmake ? "<< point_cloud.sensor_origin_[0] << point_cloud.sensor_origin_[1] << point_cloud.sensor_origin_[2] << std::endl;

	//std::string far_ranges_filename = pcl::getFilenameWithoutExtension (filename)+"_far_ranges.pcd";

	float noise_level = 0.0;
	float min_range = 0.0f;
	int border_size = 1;
	pcl::RangeImage::Ptr range_image_ptr (new pcl::RangeImage);
	pcl::RangeImage& range_image = *range_image_ptr;   
	range_image.createFromPointCloud (point_cloud, angular_resolution, pcl::deg2rad (360.0f), pcl::deg2rad (180.0f),
	                               scene_sensor_pose, coordinate_frame, noise_level, min_range, border_size);
  	range_image.integrateFarRanges (far_ranges);
	if (setUnseenToMaxRange)
	range_image.setUnseenToMaxRange ();

	pcl::visualization::PCLVisualizer viewer ("3D Viewer");
	viewer.setBackgroundColor (1, 1, 1);
	viewer.addCoordinateSystem (1.0f, "global");
	pcl::visualization::PointCloudColorHandlerCustom<PointType> point_cloud_color_handler (point_cloud_ptr, 0, 0, 0);
	viewer.addPointCloud (point_cloud_ptr, point_cloud_color_handler, "original point cloud");

	// Extract borders  
	pcl::RangeImageBorderExtractor border_extractor (&range_image);
	pcl::PointCloud<pcl::BorderDescription> border_descriptions;
	border_extractor.compute (border_descriptions);
	//std::cout << border_descriptions <<std::endl;

	// Show points in 3D viewer
	pcl::PointCloud<pcl::PointWithRange>::Ptr border_points_ptr(new pcl::PointCloud<pcl::PointWithRange>),
	                                        veil_points_ptr(new pcl::PointCloud<pcl::PointWithRange>),
	                                        shadow_points_ptr(new pcl::PointCloud<pcl::PointWithRange>);
	pcl::PointCloud<pcl::PointWithRange>& border_points = *border_points_ptr,
	                                  & veil_points = * veil_points_ptr,
	                                  & shadow_points = *shadow_points_ptr;
	for (int y=0; y< (int)range_image.height; ++y)
	{
		for (int x=0; x< (int)range_image.width; ++x)
		{
		  if (border_descriptions[y*range_image.width + x].traits[pcl::BORDER_TRAIT__OBSTACLE_BORDER])
		    border_points.points.push_back (range_image[y*range_image.width + x]);
		  if (border_descriptions[y*range_image.width + x].traits[pcl::BORDER_TRAIT__VEIL_POINT])
		    veil_points.points.push_back (range_image[y*range_image.width + x]);
		  if (border_descriptions[y*range_image.width + x].traits[pcl::BORDER_TRAIT__SHADOW_BORDER])
		    shadow_points.points.push_back (range_image[y*range_image.width + x]);
		}
	}

	std::cout << border_points.points.size()<<std::endl;
	for (int i =0; i<border_points.points.size(); i++){
		std::cout << int(border_points.points[i].x * 1000)<<" ";
		std::cout << int(border_points.points[i].y * 1000)<< std::endl;
	}

	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> border_points_color_handler (border_points_ptr, 0, 255, 0);
	viewer.addPointCloud<pcl::PointWithRange> (border_points_ptr, border_points_color_handler, "border points");
	viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 7, "border points");
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> veil_points_color_handler (veil_points_ptr, 255, 0, 0);
	viewer.addPointCloud<pcl::PointWithRange> (veil_points_ptr, veil_points_color_handler, "veil points");
	viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 7, "veil points");
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointWithRange> shadow_points_color_handler (shadow_points_ptr, 0, 255, 255);
	viewer.addPointCloud<pcl::PointWithRange> (shadow_points_ptr, shadow_points_color_handler, "shadow points");
	viewer.setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 7, "shadow points");

	//-------------------------------------
	// -----Show points on range image-----
	// ------------------------------------
	pcl::visualization::RangeImageVisualizer* range_image_borders_widget = NULL;
	range_image_borders_widget =
	pcl::visualization::RangeImageVisualizer::getRangeImageBordersWidget (range_image, -std::numeric_limits<float>::infinity (), std::numeric_limits<float>::infinity (), false,
																			border_descriptions, "Range image with borders");
	// -------------------------------------
	
  while (!viewer.wasStopped ())
  {
    range_image_borders_widget->spinOnce ();
    viewer.spinOnce ();
    pcl_sleep(0.01);
  }
}