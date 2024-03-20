# SOSLAB ML LiDAR SDK
---
This is a **C++ Software Development Kit(SDK)** for connecting and using the **ML LiDAR developed by SOSLAB.**</br>

## Release Version
- SDK v1.2.0

# Update
- Release v1.2.0

## Table of Contents

1. [Getting Started](#getting-started)
2. [Installation and Setup](#installation-and-setup)
3. [Using ML Manager](#using-ml-manager)
4. [Documentation](#documentation)

## Getting Started

To get started with this project, you will need:

- C++ development environment
- Windows or Ubuntu operating system
- SOSLAB ML LiDAR device

## Installation and Setup

Clone this repository to your local machine to access the APIs, examples, and other resources.

### Windows

APIs and examples for Windows can be found in the `ML_API/Win_API_CodeEX` folder.

### Ubuntu/ROS

APIs and examples for Ubuntu/ROS can be found in the `ML_API/Ubuntu_API_CodeEX` and `ML_API/ROS_API_CodeEX` folder.

## Using ML Manager

ML Manager is a LiDAR visualization software that runs on Windows operating systems.

### Windows Installation

To install and use ML Manager on Windows, follow these steps:

1. Navigate to the `ML_Manager` folder.
2. Run the `ML Manager_setup.exe` executable file.

## Documentation

User guides can be found in the `User_Guide` folder:

- [User Guide (Korean)](User_Guide/ML_User_Guide_v1.2(KOR).pdf)


## License

ML Manager S/W uses the Qt library, which is licensed under the GNU Lesser General Public License (LGPL) version 3. <br/>
We have complied with the requirements of the LGPL by dynamically linking to the Qt library. <br/>
This means that users have the ability to replace the Qt library with their own version if they wish. <br/>

The source code of the Qt library can be found here: <br/>
[https://download.qt.io/official_releases/qt/](https://download.qt.io/official_releases/qt/)

For more information about the LGPL, please refer to the full text of the license, available here: <br/>
[https://www.gnu.org/licenses/lgpl-3.0.html](https://www.gnu.org/licenses/lgpl-3.0.html)
