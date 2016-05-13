cmake_minimum_required( VERSION 2.8 )

# Eigen
find_package( PkgConfig )
pkg_check_modules( EIGEN REQUIRED eigen3 )
include_directories( ${EIGEN_INCLUDE_DIRS} )

add_executable( rotation_difference_liberty rotation_difference_liberty.cpp )
set_target_properties( rotation_difference_liberty PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin ) 
