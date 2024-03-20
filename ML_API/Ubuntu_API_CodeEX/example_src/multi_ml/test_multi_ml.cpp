// test_multi_ml.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<iostream>

#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingFreeType);

#include "pcl/point_cloud.h"
#include "pcl/point_types.h"
#include "pcl/visualization/pcl_visualizer.h"

#include"vtkRenderWindow.h"

typedef pcl::PointXYZRGB PointT;
typedef pcl::PointCloud<PointT> PointCloudT;


#include "ml/libsoslab_ml.h"

size_t color_vector[4][3] = { {255,255,255},
							  {255,0,0},
							  {0,255,0},
							  {0,0,255} };


void keyboardEventOccurred(const pcl::visualization::KeyboardEvent& event, void* viewer_void)
{
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer = *static_cast<boost::shared_ptr<pcl::visualization::PCLVisualizer> *>(viewer_void);
	if (event.getKeySym() == "r" && event.keyDown())
		std::cout << "'r' was pressed" << std::endl;
	if (event.getKeySym() == "h" && event.keyDown())
		std::cout << "'h' was pressed" << std::endl;
	if (event.getKeySym() == "x" && event.keyDown()) {
		std::cout << "'x' was pressed" << std::endl;
	}
}


int main()
{
	bool success = true;

	/* LidarML 수를 지정합니다.(default = 1) */
	int num_lidar = 1;
	
	std::vector<std::shared_ptr<SOSLAB::LidarMl>> lidar_ml_list(num_lidar);

	int standard_port = 2000;
	for (int i = 0; i < num_lidar; i++) {
		/* LidarML 객체를 생성합니다. */
		lidar_ml_list[i] = std::shared_ptr<SOSLAB::LidarMl>(new SOSLAB::LidarMl);
		
		/* 연결 정보를 활용하여 장치에 연결합니다. */
		SOSLAB::ip_settings_t ip_settings_pc;
		SOSLAB::ip_settings_t ip_settings_device;

		ip_settings_pc.ip_address = "192.168.1.15";
		ip_settings_pc.port_number = standard_port + i;
		ip_settings_device.ip_address = "192.168.1.1" + std::to_string(i);
		ip_settings_device.port_number = standard_port;
		std::cout<<"LiDAR ML #"+ std::to_string(i) + " :: ip/port information\n";
		std::cout<<"pc ip/port : "<<ip_settings_pc.ip_address<<", "<<ip_settings_pc.port_number<<std::endl;
		std::cout<<"device ip/port : "<<ip_settings_device.ip_address<<", "<<ip_settings_device.port_number<<std::endl;
		success = lidar_ml_list[i]->connect(ip_settings_device, ip_settings_pc);
		if (!success) {
			std::cerr << "LiDAR ML #" + std::to_string(i) + " :: connection failed" << std::endl;
			return 0;
		}
	}
	
	/* 데이터 스트리밍을 시작 합니다. */

	for (int i = 0; i < num_lidar; i++) {
		success &= lidar_ml_list[i]->tcp_device_run();
		if (!success) {
			std::cerr << "LiDAR ML #" + std::to_string(i) + " :: start failed" << std::endl;
			return 0;
		}
	}

	std::cout << "LiDAR ML :: Streaming started!" << std::endl;

	std::string grey_viz_name = "Grey Image";
	std::string depth_viz_name = "Depth Image";
	std::string intensity_viz_name = "Intensity Image";

	pcl::visualization::PCLVisualizer::Ptr pclviz_(new pcl::visualization::PCLVisualizer("ML Viewer"));
	PointCloudT::Ptr cloud_;

	pclviz_->registerKeyboardCallback(keyboardEventOccurred, (void*)pclviz_.get());
	pclviz_->addCoordinateSystem(1.0);
	pclviz_->initCameraParameters();

	cloud_.reset(new PointCloudT);

	bool initialize = true;
	bool streaming_start = false;	

	std::vector<std::size_t> size_list(num_lidar+1);
	std::vector<std::size_t> clouds_start_points(num_lidar);
	clouds_start_points[0] = 0;
	
	int points_size = 0;

	while (!pclviz_->wasStopped()) {
		SOSLAB::LidarMl::scene_t scene;
		/* Stream FIFO로부터 한 프레임씩 Lidar data를 가져옵니다. */
		for (int i = 0; i < num_lidar; i++) {
			if (lidar_ml_list[i]->get_scene(scene)) {
				std::size_t height = scene.rows;	// Lidar frame의 height 정보입니다.
				std::size_t width = scene.cols;		// Lidar frame의 width 정보입니다.
				if (initialize) size_list[i+1] = height * width;

				if (!scene.pointcloud.empty() && streaming_start) {
					for (int j = 0; j < size_list[i+1]; j++) {
						PointT point;
						point.x = scene.pointcloud[j].xyz.x / 1000.0f;
						point.y = scene.pointcloud[j].xyz.y / 1000.0f;
						point.z = scene.pointcloud[j].xyz.z / 1000.0f;
						point.r = uint8_t(color_vector[i][0]);
						point.g = uint8_t(color_vector[i][1]);
						point.b = uint8_t(color_vector[i][2]);
						cloud_->points[j+ clouds_start_points[i]] = point;
					}
				}
			}
		}

		if (initialize && !streaming_start) {
			bool check_points_size = true;
			for (int i = 1; i < size_list.size(); i++) {
				check_points_size &= bool(size_list[i]);
				points_size += size_list[i];
				clouds_start_points[i] = size_list[i] + clouds_start_points[i - 1];
			}
			if (check_points_size) {
				cloud_->clear();
				cloud_->points.resize(points_size, PointT());
		
				initialize = false;
				streaming_start = true;
			}
		}

		if (!pclviz_->updatePointCloud(cloud_, "cloud")) {
			pclviz_->addPointCloud(cloud_, "cloud");
			pclviz_->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "cloud");
			//pclviz_->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");
		}
		pclviz_->spinOnce(1);

	}
	
	/* 스트리밍을 종료 합니다. */

	for (int i = 0; i < num_lidar; i++) {
		lidar_ml_list[i]->tcp_device_stop();
	}
	
	std::cout << "Streaming stopped!" << std::endl;

	/* 장치 연결을 해제합니다. */

	for (int i = 0; i < num_lidar; i++) {
		lidar_ml_list[i]->disconnect();
	}

	for (int i = 0; i < num_lidar; i++) {
		lidar_ml_list[i].reset();
	}

	std::cout << "Done." << std::endl;
}
