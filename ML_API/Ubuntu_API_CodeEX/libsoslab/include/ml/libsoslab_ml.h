/*
 * libsoslab_ml.h
 *
 *  Created on: Dec 02, 2019
 *      Author: gnohead
 */

#ifndef LIDAR_ML_H_
#define LIDAR_ML_H_


#include "soslab_typedef.h"
#include <array>
#include <fstream>

#define TCP_PACKET_MTU											(1440)
#define TCP_PROT_HEADER_SIZE									(4)
#define TCP_PROT_FW_UPLOAD_HEADER_SIZE							(8)
#define TCP_PROT_FW_UPLOAD_DATA_SIZE_MAX						(TCP_PACKET_MTU-(TCP_PROT_HEADER_SIZE+TCP_PROT_FW_UPLOAD_HEADER_SIZE))

#define TCP_PROT_DATA_LEN_MAX                                   (65535-4)

#define TCP_PROT_MAIN_CMD_ERROR                                 ('E')
    #define TCP_PROT_ERROR_SUB_CMD_DEVICE                       ('D')
    #define TCP_PROT_ERROR_SUB_CMD_PACKET                       ('P')

#define TCP_PROT_MAIN_CMD_SYSTEM_MODE                           ('S')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_CHANGE_TO_NORMAL       ('N')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_CHANGE_TO_PROD         ('P')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_READ                   ('R')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_CHANGE_SUCCESS         ('O')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_CHANGE_FAIL            ('X')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_IS_NORMAL              ('N')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_IS_PROD                ('P')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_IS_FWUP                ('F')
    #define TCP_PROT_SYSTEM_MODE_SUB_CMD_IS_ERROR               ('E')

#define TCP_PROT_MAIN_CMD_REGISTER                              ('R')
    #define TCP_PROT_REGISTER_SUB_CMD_WRITE                     ('W')
    #define TCP_PROT_REGISTER_SUB_CMD_READ                      ('R')
    #define TCP_PROT_REGISTER_SUB_CMD_WRITE_SUCCESS             ('O')
    #define TCP_PROT_REGISTER_SUB_CMD_WRITE_FAIL                ('X')
    #define TCP_PROT_REGISTER_SUB_CMD_SEND                      ('S')

#define TCP_PROT_MAIN_CMD_MEMORY                                ('M')
    #define TCP_PROT_MEMORY_SUB_CMD_UPLOAD                      ('U')
    #define TCP_PROT_MEMORY_SUB_CMD_DOWNLOAD                    ('D')
    #define TCP_PROT_MEMORY_SUB_CMD_VERIFY                      ('V')
    #define TCP_PROT_MEMORY_SUB_CMD_SUCCESS                     ('O')
    #define TCP_PROT_MEMORY_SUB_CMD_FAIL                        ('X')

#define TCP_PROT_MAIN_CMD_FW                                    ('F')
    #define TCP_PROT_FW_SUB_CMD_UPLOAD                          ('U')
    #define TCP_PROT_FW_SUB_CMD_UPLOAD_SUCCESS                  ('O')
    #define TCP_PROT_FW_SUB_CMD_UPLOAD_ACK                      ('A')
    #define TCP_PROT_FW_SUB_CMD_UPLOAD_FAIL                     ('X')
	#define TCP_PROT_FW_SOFTWARE_RESET							('S')

#define TCP_PROT_MAIN_CMD_PROD                                  ('P')
    #define TCP_PROT_PROD_SUB_CMD_CMD                           ('C')
    #define TCP_PROT_PROD_SUB_CMD_REPORT                        ('R')

#define TCP_PROT_MAIN_CMD_DEVICE                                ('D')
    #define TCP_PROT_DEVICE_SUB_CMD_RUN                         ('R')
    #define TCP_PROT_DEVICE_SUB_CMD_STOP                        ('S')
    #define TCP_PROT_DEVICE_SUB_CMD_SUCCESS                     ('O')
    #define TCP_PROT_DEVICE_SUB_CMD_FAIL                        ('X')

#define TCP_PROT_MAIN_CMD_TRIG                                  ('T')
	#define TCP_PROT_TRIG_SUB_CMD_CAPTURE                       ('C')
    
#define HEADER					"SLAB"

#define	SET_EN					0x0000
#define SET_VCSEL_MANUAL_CS		0x0001
#define SET_VCSEL_PARAM			0x0002
#define	SET_PRI					0x0003
#define	SET_INTF_REJECT			0x0004
#define	SET_SAMPLE				0x0005
#define	SET_START_COL			0x0006
#define	SET_END_COL				0x0007
#define	SET_START_ROW			0x0008
#define	SET_END_ROW				0x0009
#define	SET_PULSE_INHIBIT		0x000A
#define	SET_PULSE_EDGE			0x000B
#define	SET_PULSE_DELAY			0x000C
#define	SET_PULSE_DUTY			0x000D
#define	SET_STREAM_MODE			0x000E
#define	SET_TYPE_B_PARAM		0x000F
 //#define	SET_XXX			0x0010
#define	SET_INTENSITY			0x0011
#define SET_JITTER_EN			0x0012
#define SET_PEAK_WIDTH			0x0013
#define	SET_FIR_OFFSET			0x0014
#define	SET_COEFF_A				0X0015
#define	SET_COEFF_B				0X0016
#define	SET_COG_TAP_NUM			0x0017
#define	SET_SPAD_OFFSET_L		0x0018	// 0x0018 ~ 0x007B
#define	SET_SPAD_OFFSET_R		0x007C	// 0x007C ~ 0x00DF
//#define SET_THRESHOLD_COE		0x00E0	// 0x00E0 ~ 0x00E2
#define SET_LENS_COE			0x00E3	// 0x00E3 ~ 0x00EE (fx, fy, cx, cy, p1, p2, k1, k2, k3, k4, k5, k6)
#define SET_GLOBAL_OFFSET		0x00EF

#define SET_VOLTAGE				0x00F0
#define SET_DEVICE_IP			0x00F1
#define SET_DEVICE_PORT			0x00F2
#define SET_SAVE				0x00F3
#define SET_DUAL_CH				0x00F4
#define SET_VCSEL_DRV_TYPE		0x00F5	// 0:high control, 1:high-low-common control
#define SET_VCSEL_OFFSET		0x00F6	// 0x00F6 ~ 0x0155 96 offsets
#define SET_EMITTER_DWIDTH		0x0156
#define SET_THRESHOLD_COE		0x0157	// 0x0157 ~ 0x015A
#define SET_WALKERROR_COE		0x015B	// 0x015B ~ 0x0160
#define SET_FILLING_EN			0x0286
#define	SET_H_CL_DELAY			0x0287
#define	SET_CLS_DUTY			0x0288
#define	SET_INTS_FIR_COE		0x0289	// 0x0289 ~ 0x0293
#define	SET_OUTPUT_SYNC_POL		0x0294
#define	SET_RX_HV_CTRL_EN		0x0295
#define	SET_INPUT_SYNC_POL		0x0296
#define	SET_SYNC_MODE			0x0297
#define	SET_FPS					0x0298

namespace SOSLAB
{
	class SOSLAB_EXPORTS LidarMl
	{
	public:
		enum class LASER_CLOCK_EDGE : uint8_t {
			minus_ve = 0x00,
			plus_ve = 0x01
		};

		typedef struct SOSLAB_EXPORTS _ML1_CONFIGURATIONS_T {
			float vdp_voltage;
			float vdn_voltage;
			float hv_bias;

			uint8_t vcsel_manual_cs;
			union {
				struct {
					uint32_t vcsel_no_chs : 8;
					uint32_t vcsel_cols_per_ch : 8;
					uint32_t vcsel_param_dummy_ : 16;
				};
				uint32_t vcsel_param;
			};
			uint16_t pri;
			bool intf_reject;
			uint16_t target_samples;
			uint16_t start_column_index;
			uint16_t end_column_index;
			uint8_t start_row_index;
			uint8_t end_row_index;

			bool pulse_inhibit;
			bool pulse_edge;
			uint16_t pulse_delay;
			uint8_t pulse_duty;

			uint8_t stream_mode;

			union {
				struct {
					uint32_t ls_duty : 9;
					uint32_t l_h_delay : 9;
					uint32_t hs_duty : 9;
					uint32_t _type_b_param_dummy : 5;
				};
				uint32_t type_b_param;
			};

			union {
				struct {
					uint32_t intensity_img : 2;
					uint32_t grey_img : 2;
					uint32_t _dummy_ : 28;
				};
				uint32_t intensity_mode;
			};
			uint32_t peak_separation_width;
			uint8_t fir_offset;
			union {
				struct {
					uint32_t coeff_a0 : 4;
					uint32_t coeff_a1 : 4;
					uint32_t coeff_a2 : 4;
					uint32_t coeff_a3 : 4;
					uint32_t coeff_a4 : 4;
					uint32_t coeff_a5 : 4;
					uint32_t coeff_a6 : 4;
					uint32_t coeff_a7 : 4;
				};
				uint32_t coeff_group_a;
			};
			union {
				struct {
					uint32_t coeff_a8 : 4;
					uint32_t coeff_a9 : 4;
					uint32_t coeff_a10 : 4;
					uint32_t coeff_a11 : 4;
					uint32_t coeff_a12 : 4;
					uint32_t coeff_a13 : 4;
					uint32_t coeff_a14 : 4;
					uint32_t coeff_a15 : 4;
				};
				uint32_t coeff_group_b;
			};

			uint8_t cog_tap_num;
			bool jitter_en;

			float threshold_coe[4];
			float lens_coe[12];

			uint8_t vcsel_type;
			bool dual_channel;

			uint16_t global_offset;

			uint16_t vcsel_offset[96];

			uint32_t filling_en;

			float emitter_dwidth;

			float walkerror_coe[6];

			uint32_t h_cl_delay;
			uint32_t cls_duty;

			float intensity_fir_coe[11];

			uint32_t output_sync_polarity;
			uint32_t rx_hv_ctrl_en;

			uint32_t input_sync_polarity;
			uint32_t sync_signal_mode;

			uint32_t fps;

		} configurations_t;

		typedef struct SOSLAB_EXPORTS _ML1_SCENE_T {
			std::vector<uint64_t> timestamp;
			uint8_t frame_id;
			std::size_t rows;
			std::size_t cols;
			std::vector<uint16_t> grey_image;
			std::vector<uint32_t> depth_image;
			std::vector<uint16_t> intensity_image;
			std::vector<point_t> pointcloud;
			std::vector<uint32_t> depth_image2;
			std::vector<uint16_t> intensity_image2;
			std::vector<point_t> pointcloud2;
		} scene_t;

		typedef struct SOSLAB_EXPORTS _ML1_IP_T {
			uint32_t device_ip;
			uint32_t device_port;
			uint32_t pc_ip;
			uint32_t pc_port;
		} ip_t;

		typedef struct SOSLAB_EXPORTS _SPAD_OFFSET_T {
			uint8_t spad_offset_l[100];
			uint8_t spad_offset_r[100];
		} spad_offset_t;

#pragma pack(push, 1)
		typedef struct SOSLAB_EXPORTS _SPAD_VOLTAGE_T {
			uint8_t n;
			uint8_t vdp;
			uint8_t vdn;
			uint8_t hv;
		} spad_voltage_t;
#pragma pack(pop)

#pragma pack(push, 1)
		typedef struct SOSLAB_EXPORTS _UDP_PROTOCOL_T {
			char header[4];
			uint16_t addr;
			union {
				uint32_t data;
				float fdata;
			};
		} udp_protocol_t;
#pragma pack(pop)

#pragma pack(push, 1)
		typedef struct SOSLAB_EXPORTS _TCP_PROTOCOL_T{
			uint16_t data_len;
			char main_cmd;
			char sub_cmd;
			uint8_t data[TCP_PROT_DATA_LEN_MAX];
		} tcp_protocol_t;
#pragma pack(pop)

		typedef struct SOSLAB_EXPORTS _ML1_HIST_T {
			std::size_t column;
			std::size_t row;
			std::size_t total_bin;
			std::vector<uint16_t> data;
		} histogram_t;

#pragma pack(push, 1)
		typedef struct SOSLAB_EXPORTS _ML1_SENSING_T {
			uint64_t timestamp;
			uint32_t xadc_scan_count;

			float xadc_onchip_temp;
			float xadc_vccint;
			float xadc_vccaux;
			float xadc_vccbram;
			float xadc_vccpint;
			float xadc_vccpaux;
			float xadc_vcco_ddr;

			float xadc_rd_ddr_vtt;
			float xadc_rd_dp3v3;
			float xadc_rd_p12v;
			float xadc_rd_heat;

			float xadc_tx_0v5;
			float xadc_tx_5v0;
			float xadc_tx_12v;
			float xadc_tx_hv;
			float xadc_tx_temp;

			float xadc_rx_vio;
			float xadc_rx_vcore;
			float xadc_rx_bias;

			float xadc_rx_vdp;
			float xadc_rx_vdn;
			float xadc_rx_0v5;

			float rx_temp;
		} sensing_packet_t;
#pragma pack(pop)

		explicit LidarMl();
		~LidarMl();

		static std::string api_info();

		bool connect(const ip_settings_t ml, const ip_settings_t local);
		
		void disconnect();

		bool configuration(const configurations_t& configurations);
		bool start();
		bool stop();
		bool get_scene(scene_t& scene);
		bool get_scene(scene_t& scene, uint64_t index);
		bool get_histogram(histogram_t& histogram);
		bool get_sensing_packet(sensing_packet_t& sensing);
		bool get_sensing_packet(sensing_packet_t& sensing, uint64_t index);

		bool ip_setting(const ip_t& ip_setting);
		bool spad_offset_config(const spad_offset_t& spad_offset);

		bool tcp_system_mode_change_to_normal();
		bool tcp_system_mode_change_to_production();
		bool tcp_system_mode_read();
		
		bool tcp_register_write(const char* name);
		bool tcp_register_read();
		bool tcp_register_read(const char* name);
		bool tcp_memory_upload();
		bool tcp_memory_download();
		bool tcp_memory_verify();
		bool tcp_fw_upload(const char* name);
		bool tcp_software_reset();
		bool tcp_production_mode_command(const char* cmd, uint16_t len);
		bool tcp_device_run();
		bool tcp_device_stop();
		bool tcp_trigger_capture();
		
		bool tcp_get_message(tcp_protocol_t& buffer);

		//Data logging module
		bool start_recording(std::string dir_path);
		void stop_recording();

		bool connect_file(const std::string filepath);
		bool binary2file(std::string save_directory);

		//Data Processing Function
		void set_zigzag_filling_enable(bool enable);
		void set_deflaring_enable(bool enable);
		void set_real_ambient_enable(bool enable);
		void set_line_filling_enable(bool enable);

		void set_tr_retro_threshold_ml0(int val);
		void set_tr_retro_threshold_ml2(int val);
		void set_line_filling_left_offset(int val);
		void set_line_filling_right_offset(int val);

		void get_logging_file_size(uint64_t& size);

	private:
		void* lidar_;

		//Data Processing Trigger
		bool zigzagfilling;
		bool deflaring;
		bool real_ambient;
		bool line_filling;

		int tr_retro_threshold_ml0;
		int tr_retro_threshold_ml2;
		int line_filling_left_offset;
		int line_filling_right_offset;
	};

}   /* namespace SOSLAB */



#endif /* LIDAR_GL_H_ */
