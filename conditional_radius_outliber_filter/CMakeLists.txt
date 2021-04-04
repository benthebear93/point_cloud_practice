cmake_minimum_required( VERSION 2.8 )
project(conditional_radius_outliber_filter)
 
set( CMAKE_BUILD_TYPE Release )
set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

# eigen 
include_directories( "/usr/include/eigen3/" )
 
# pcl 
find_package( PCL 1.8 REQUIRED)
include_directories( "/usr/include/pcl-1.8/" )
#add_definitions( "/usr/share/pcl-1.8/" )
link_directories("/usr/lib/libpcl_common.so" "/usr/lib/libpcl_io.so")
list (REMOVE_ITEM PCL_LIBRARIES "vtkproj4")

add_executable( conditional_filter conditional_filter.cpp )
target_link_libraries( conditional_filter ${PCL_LIBRARIES} )
add_executable( radius_outlier_filter radius_outlier_filter.cpp )
target_link_libraries( radius_outlier_filter ${PCL_LIBRARIES} )
