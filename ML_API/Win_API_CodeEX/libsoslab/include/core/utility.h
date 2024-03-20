

#ifndef UTILITY_H_
#define UTILITY_H_

#include "soslab_typedef.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <array>

namespace SOSLAB {
    namespace UTILITY {
		std::string SOSLAB_EXPORTS hex_array_to_string(const uint8_t* hex_array, const std::size_t length, const std::string title = "", const std::size_t margin = 32);
		void SOSLAB_EXPORTS print_hex(const uint8_t* hex_array, const std::size_t length, const std::string title, const std::size_t margin = 32);
		void SOSLAB_EXPORTS calculate_checksum(uint8_t* crc, uint8_t* data, std::size_t size);

		std::array<uint8_t, 3> SOSLAB_EXPORTS range_to_color(const uint16_t range, const uint16_t max, const uint16_t min);

		std::vector<std::pair<unsigned int, std::string> > SOSLAB_EXPORTS enum_serialport();


		/*
		 * template functions
		 */
        template<typename T>
        std::string numeric_array_to_string(const std::vector<T>& numeric_array, const std::string title = "", const std::size_t margin = 32)
        {
            std::stringstream ss;
            if (!title.empty()) {
                ss << "\n> " << title << std::endl;
            }
            ss << "numeric array : { ";
            for (unsigned short j = 0; j < numeric_array.size(); j++) {

                if ((margin == j) && (margin != numeric_array.size())) {
                    ss << std::endl << "..." << std::endl;
                }

                if ((j > margin) && (j < (numeric_array.size() - margin))) {
                    continue;
                }

                ss << std::dec << std::fixed << numeric_array[j];
                ss << " ";
            }
            ss << "} TOTAL(" << std::dec << numeric_array.size() << ")";

            return ss.str();
        }
    } /* namespace UTILITY */

}   /* namespace SOSLAB */

#endif  /* UTILITY_H_ */