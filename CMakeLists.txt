cmake_minimum_required(VERSION 2.8)
 
project(cell2point)
 
find_package(VTK REQUIRED)

include(${VTK_USE_FILE})


add_executable(cell2point cell2point.cxx)
target_link_libraries(cell2point ${VTK_LIBRARIES})