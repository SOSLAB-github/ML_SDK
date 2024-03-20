// test_ml.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

#include "ml/libsoslab_ml.h"
#include "opencv2/opencv.hpp"

cv::Point picking_point_(0, 0);
static void onMouse(int event, int x, int y, int, void*)
{
	switch (event) {
	case cv::EVENT_LBUTTONUP:
		picking_point_.x = x;
		picking_point_.y = y;
		break;

	default:
		break;
	}
}

bool keyinput_checker(char kb_input)
{
	bool retval = true;

	switch (kb_input) {
	case 'q':
	case 'Q':
		retval = false;
		break;
	default:
		break;
	}

	return retval;
}

int main()
{
	bool success;
	/* LidarML 객체를 생성합니다. */
	std::shared_ptr<SOSLAB::LidarMl> lidar_ml(new SOSLAB::LidarMl);

	/* 연결 정보를 활용하여 장치에 연결합니다. */
	SOSLAB::ip_settings_t ip_settings_device;
	SOSLAB::ip_settings_t ip_settings_pc;
	ip_settings_pc.ip_address = "0.0.0.0";
	ip_settings_pc.port_number = 0;
	ip_settings_device.ip_address = "192.168.1.10";
	ip_settings_device.port_number = 2000;
	success = lidar_ml->connect(ip_settings_device, ip_settings_pc);
	if (!success) {
		std::cerr << "LiDAR ML :: connection failed." << std::endl;
		return 0;
	}

	/* 데이터 스트리밍을 시작 합니다. */
	success = lidar_ml->tcp_device_run();
	if (!success) {
		std::cerr << "LiDAR ML :: start failed." << std::endl;
		return 0;
	}
	std::cout << "LiDAR ML :: Streaming started!" << std::endl;

	std::string grey_viz_name = "Grey Image";
	std::string depth_viz_name = "Depth Image";
	std::string intensity_viz_name = "Intensity Image";

	cv::namedWindow(grey_viz_name, cv::WINDOW_GUI_NORMAL);
	cv::namedWindow(depth_viz_name, cv::WINDOW_GUI_NORMAL);
	cv::namedWindow(intensity_viz_name, cv::WINDOW_GUI_NORMAL);

	cv::setMouseCallback(depth_viz_name, onMouse, 0);

	while (keyinput_checker(cv::waitKey(1))) {
		SOSLAB::LidarMl::scene_t scene;
		/* Stream FIFO로부터 한 프레임씩 Lidar data를 가져옵니다. */
		if (lidar_ml->get_scene(scene)) {
			std::size_t height = scene.rows;	// Lidar frame의 height 정보입니다.
			std::size_t width = scene.cols;		// Lidar frame의 width 정보입니다.

			/* Grey Image */
			/* 측정 된 모든 빛을 표현 한 데이터 입니다. */
			cv::Mat grey_image_raw(height, width, CV_16UC1, scene.grey_image.data());

			/* normalize (min-max) */
			cv::Mat grey_image_norm;
			cv::normalize(grey_image_raw, grey_image_norm, 0, 255, cv::NORM_MINMAX);

			cv::Mat grey_norm_8b;
			grey_image_norm.convertTo(grey_norm_8b, CV_8U);

			cv::imshow(grey_viz_name, grey_norm_8b);

			/* Depth Image */
			/* 원점(Lidar)로부터의 거리 정보입니다. (unit: mm) */
			cv::Mat depth_image_raw(height, width, CV_32SC1, scene.depth_image.data());
			cv::Mat depth_8b;
			depth_image_raw.convertTo(depth_8b, CV_8U, 1.0 / 32.0);
			cv::Mat depth_rgb;
                        cv::applyColorMap(255 - depth_8b, depth_rgb, cv::COLORMAP_JET);
			cv::drawMarker(depth_rgb, cv::Point(picking_point_.x, picking_point_.y), cv::Scalar(255, 255, 255), cv::MARKER_CROSS, 10, 1);
			cv::imshow(depth_viz_name, depth_rgb);

			/* Intensity Image */
			/* 측정 된 Lidar 신호의 강도 입니다. */
			cv::Mat intensity_image_raw(height, width, CV_16UC1, scene.intensity_image.data());

			/* normalize (min-max) */
			cv::Mat intensity_image_norm;
			cv::normalize(intensity_image_raw, intensity_image_norm, 0, 255, cv::NORM_MINMAX);

			cv::Mat intensity_norm_8b;
			intensity_image_norm.convertTo(intensity_norm_8b, CV_8U);

			cv::imshow(intensity_viz_name, intensity_norm_8b);

			/* coordinate data output */
			/* x, y, z 좌표상의 위치를 표현한 데이터입니다. */
			{
				std::size_t col = picking_point_.x;
				std::size_t row = picking_point_.y;

				std::size_t idx = col + (width * row);

				std::cout << "col: " << col << std::endl;
				std::cout << "row: " << row << std::endl;
				std::cout << "x [mm]: " << scene.pointcloud[idx].xyz.x << std::endl;		// x 좌표 (+ 정면)
				std::cout << "y [mm]: " << scene.pointcloud[idx].xyz.y << std::endl;		// y 좌표 (+ 좌)
				std::cout << "z [mm]: " << scene.pointcloud[idx].xyz.z << std::endl;		// z 좌표 (+ 상)
			}
		}
	}
	
	cv::destroyAllWindows();

	/* 스트리밍을 종료 합니다. */
	lidar_ml->tcp_device_stop();

	std::cout << "Streaming stopped!" << std::endl;

	/* 장치 연결을 해제합니다. */
	lidar_ml->disconnect();

	std::cout << "Done." << std::endl;
}


