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

    pcl::io::loadPCDFile ("/home/benlee/Desktop/pc_practice/bunny/data/bun000.pcd", *cloud);

    // Create the filtering object
    pcl::PassThrough<pcl::PointXYZ> pass;
    pass.setInputCloud (cloud);
    pass.setFilterFieldName ("z");
    pass.setFilterLimits (0.03, 0.04);

    pass.filter (*cloud_filtered);

    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    viewer.showCloud(cloud_filtered);
    while (!viewer.wasStopped ())
    {
        user_data++;
    }
    return 0;
}
