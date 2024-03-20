cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(test_multi_ml)
find_package(PCL 1.8 REQUIRED)
find_package(VTK REQUIRED)

set(ML_SOURCE_DIRS ../example_src/multi_ml/test_multi_ml.cpp)
set(ML_INCLUDE_DIRS ../libsoslab/include)
set(ML_LIBRARY_DIRS ../libsoslab/bin)


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
include_directories(${ML_INCLUDE_DIRS})
find_library( ML_CORE_LIBRARY NAMES libsoslab_core.so
	HINTS ${ML_LIBRARY_DIRS} REQUIRED)
find_library( ML_LIBRARY NAMES libsoslab_ml.so
	HINTS ${ML_LIBRARY_DIRS} REQUIRED)

add_definitions(${PCL_DEFINITIONS})

add_executable(test_multi_ml ${ML_SOURCE_DIRS})
target_link_libraries(test_multi_ml ${PCL_LIBRARIES})
target_link_libraries(test_multi_ml ${ML_CORE_LIBRARY})
target_link_libraries(test_multi_ml ${ML_LIBRARY})

SET(COMPILE_FLAGS "-std=c++11")
add_definitions(${COMPILE_FLAGS})
