cmake_minimum_required( VERSION 2.8 )
project(passthrough_filter)
 
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

add_executable(passthrough_filter passthrough_filter.cpp )
target_link_libraries(passthrough_filter ${PCL_LIBRARIES} )

