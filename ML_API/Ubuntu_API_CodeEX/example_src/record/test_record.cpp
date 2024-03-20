#include<iostream>
#include <memory>

#ifdef _WIN32
#include<direct.h>
#include<io.h>
#endif // _WIN32
#ifdef __linux__
#include<sys/stat.h>
#endif

#include"ml/libsoslab_ml.h"

int main()
{
	bool success;
	/* LidarML ��ü�� �����մϴ�. */
	std::shared_ptr<SOSLAB::LidarMl> lidar_ml(new SOSLAB::LidarMl);	
	
	/* ���� ������ Ȱ���Ͽ� ��ġ�� �����մϴ�. */
 	SOSLAB::ip_settings_t ip_settings_device;
	SOSLAB::ip_settings_t ip_settings_pc;
	ip_settings_pc.ip_address = "0.0.0.0"; 
	ip_settings_pc.port_number = 2000;
	ip_settings_device.ip_address = "192.168.1.10";
	ip_settings_device.port_number = 2000;
	success = lidar_ml->connect(ip_settings_device, ip_settings_pc);
	if (!success) {
		std::cerr << "LiDAR ML :: connection failed." << std::endl;
		return 0;
	}

	/* ������ ��Ʈ������ ���� �մϴ�. */
	success = lidar_ml->tcp_device_run();
	if (!success) {
		std::cerr << "LiDAR ML :: start failed." << std::endl;
		return 0;
	}
	std::cout << "LiDAR ML :: Streaming started!" << std::endl;

	std::string save_directory = "../";

// #ifdef _WIN32
// 	if (_access(save_directory.c_str(), 0)) {
// 		if (_mkdir(save_directory.c_str())) return false;
// 	}
// #endif // _WIN32
// #ifdef __linux__
// 	mkdir(save_directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
// #endif
	bool retval = lidar_ml->start_recording(save_directory + "record");

	int frame_number = 0;
	int logging_data_size = 10;
	std::string filename;
	while (frame_number < logging_data_size) {
		SOSLAB::LidarMl::scene_t scene;
		/* Stream FIFO�κ��� �� �����Ӿ� Lidar data�� �����ɴϴ�. */
		if (lidar_ml->get_scene(scene)) {
			std::size_t height = scene.rows;	// Lidar frame�� height �����Դϴ�.
			std::size_t width = scene.cols;		// Lidar frame�� width �����Դϴ�.

			frame_number++;
			std::cout << frame_number << std::endl;
		}
	}
	lidar_ml->stop_recording();
	
	/* ��Ʈ������ ���� �մϴ�. */
	lidar_ml->tcp_device_stop();

	std::cout << "Streaming stopped!" << std::endl;

	/* ��ġ ������ �����մϴ�. */
	lidar_ml->disconnect();

	std::cout << "Done." << std::endl;
	system("pause");
}
