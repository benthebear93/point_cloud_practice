#include <pcl/visualization/cloud_viewer.h>
#include <iostream>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/integral_image_normal.h>
    
int 
main ()
{
    // load point cloud
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile ("/home/benlee/Desktop/git/point_cloud_practice/normal_estimation_using_integral_image/table_scene_mug_stereo_textured.pcd", *cloud);
    
    // estimate normals
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);

    pcl::IntegralImageNormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
    ne.setNormalEstimationMethod (ne.AVERAGE_3D_GRADIENT);
    ne.setMaxDepthChangeFactor(0.02f);
    ne.setNormalSmoothingSize(10.0f);
    ne.setInputCloud(cloud);
    ne.compute(*normals);

    std::cout <<"normals: \n"<< *normals << std::endl;
    // visualize normals
    pcl::visualization::PCLVisualizer viewer("PCL Viewer");
    viewer.setBackgroundColor (0.0, 0.0, 0.5);
    viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(cloud, normals);
    while (!viewer.wasStopped())
        viewer.spinOnce();
    // std::cerr << "Normal Estimation: " << std::endl;
    // for (size_t i = 0; i < normals->points.size (); ++i){
    //     std::cerr << "    " << normals->points[i].normal[0]  << " "
    //                 << normals->points[i].normal[1] << " "
    //             << normals->points[i].normal[2] << std::endl;
    // }
    return 0;
}
