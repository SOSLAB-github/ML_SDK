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


int main(int argc, char** argv)
{
	bool success;
	/* LidarML 객체를 생성합니다. */
	std::shared_ptr<SOSLAB::LidarMl> lidar_ml(new SOSLAB::LidarMl);

	if (argc > 1) {
		std::string path(argv[1]);
		std::cout << "Logging File : " << path << std::endl;

		//Connect Logging File
		lidar_ml->connect_file(path);

		//Logging File to PCD
		lidar_ml->binary2file("./");
	}
	else{
		std::cout << "Please check file path." << std::endl;
	}

	lidar_ml->disconnect();

	std::cout << "Done" << std::endl;
}
