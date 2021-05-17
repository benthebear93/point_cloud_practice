#include <pcl/point_cloud.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/normal_3d.h>

#include <iostream>
#include <vector>
#include <ctime>
#include <math.h>

int main (int argc, char** argv)
{
  std::cout <<" running " << std::endl;
    // *.PCD 파일 읽기 (https://raw.githubusercontent.com/adioshun/gitBook_Tutorial_PCL/master/Intermediate/sample/cloud_cluster_0.pcd)
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);    
  pcl::io::loadPCDFile<pcl::PointXYZRGB>("/home/benlee/catkin_ws/src/Direct_machining_with_manipulator/test_bed/pcd_data/pass_pc_rgb.pcd", *cloud);
  std::cout << "input cloud size: " << cloud->points.size() << std::endl;
  
  // 시각적 확인을 위해 색상 통일 (255,255,255)
  for (size_t i = 0; i < cloud->points.size(); ++i){
  cloud->points[i].r = 255;
  cloud->points[i].g = 255;
  cloud->points[i].b = 255;
  }

  //KdTree 오브젝트 생성 
  pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;
  kdtree.setInputCloud (cloud);    //입력 

     pcl::PointXYZRGB searchPoint;
     searchPoint.x = 0.059;
     searchPoint.y = 0.094;
     searchPoint.z = 0.512;
  // pcl::PointXYZRGB searchPoint = cloud->points[3000]; 

  //기준점 좌표 출력 
  std::cout << "searchPoint :" << searchPoint.x << " " << searchPoint.y << " " << searchPoint.z  << std::endl;


  //기준점에서 가까운 순서중 K번째까지의 포인트 탐색 (K nearest neighbor search)
  // int K = 10;   // 탐색할 포인트 수 설정 
  // std::vector<int> pointIdxNKNSearch(K);
  // std::vector<float> pointNKNSquaredDistance(K);

  // if ( kdtree.nearestKSearch (searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0 )
  // {
  //   //시각적 확인을 위하여 색상 변경 (0,255,0)
  //   for (size_t i = 0; i < pointIdxNKNSearch.size (); ++i)
  //   {
  //     cloud->points[pointIdxNKNSearch[i]].r = 0;
  //     cloud->points[pointIdxNKNSearch[i]].g = 255;
  //     cloud->points[pointIdxNKNSearch[i]].b = 0;
  //   }
  // }

  // // 탐색된 점의 수 출력 
  // std::cout << "K = 10 ：" << pointIdxNKNSearch.size() << std::endl;


  // 기준점에서 지정된 반경내 포인트 탐색 (Neighbor search within radius)
  float radius = 0.02; //탐색할 반경 설정(Set the search radius)
  std::vector<int> pointIdxRadiusSearch;
  std::vector<float> pointRadiusSquaredDistance;

  if ( kdtree.radiusSearch (searchPoint, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0 )
  {
    //시각적 확인을 위하여 색상 변경 (0,0,255)
    for (size_t i = 0; i < pointIdxRadiusSearch.size (); ++i)
      for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i)
        {
        cloud->points[pointIdxRadiusSearch[i]].r = 0;
        cloud->points[pointIdxRadiusSearch[i]].g = 0;
        cloud->points[pointIdxRadiusSearch[i]].b = 255;
        }
  }

  // 탐색된 점의 수 출력 
  std::cout << "Radius 0.02 nearest neighbors: " << pointIdxRadiusSearch.size() << std::endl;
  float curvature;
  Eigen::Vector4f plane_parameters; 
  computePointNormal(*cloud,pointIdxRadiusSearch,plane_parameters,curvature); 
  std::cout << "plane param : \n"<< plane_parameters[1] << std::endl;
  std::cout << "curvature : "<< curvature << std::endl;

  return 0;
}