#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
    
int user_data;

int main ()
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

    pcl::io::loadPCDFile ("/home/benlee/Desktop/git/point_cloud_practice/pcd_files/data/scan.pcd", *cloud);

    // Create the filtering object
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName ("z");
    pass.setFilterLimitsNegative(false); // option 
    pass.setFilterLimits (0.2, 0.35);

    pass.filter (*cloud_filtered);
    pcl::io::savePCDFile ("/home/benlee/Desktop/git/point_cloud_practice/pcd_files/data/scan.pcd", *cloud_filtered);

    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    viewer.showCloud(cloud_filtered);
    while (!viewer.wasStopped ())
    {
        user_data++;
    }
    return 0;
}
