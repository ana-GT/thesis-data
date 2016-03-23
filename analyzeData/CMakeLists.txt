cmake_minimum_required( VERSION 2.8 )

set( CMAKE_CXX_FLAGS "-std=c++11" )

find_package( DART )


include_directories( ${DART_INCLUDE_DIRS} )
include_directories( /usr/include/eigen3 )
include_directories( /home/ana/Research/Code/GM )
link_directories( /home/ana/Research/Code/GM/lib )

add_executable( analyzeData analyzeData.cpp )
target_link_libraries( analyzeData aoi grasp ${DART_LIBRARIES} dart-core )

