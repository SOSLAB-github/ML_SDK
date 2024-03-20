cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(multi_ml)
find_package(PCL 1.8 REQUIRED)
find_package(VTK REQUIRED)

set(ML_INCLUDE_DIRS ../../include)
set(ML_LIBRARY_DIRS ../../include)


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(multi_ml test_multi_ml.cpp)
target_link_libraries(multi_ml ${PCL_LIBRARIES})

SET(COMPILE_FLAGS "-std=c++11")
add_definitions(${COMPILE_FLAGS})
