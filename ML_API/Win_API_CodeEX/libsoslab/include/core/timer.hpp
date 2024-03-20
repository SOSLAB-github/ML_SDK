/*
 * timer.hpp
 *
 *  Created on: Nov 26, 2018
 *      Author: gnohead
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "soslab_typedef.h"
#include <iomanip>
#include <chrono>

#include <ctime>

#include <sstream>

namespace SOSLAB {
    class SOSLAB_EXPORTS Timer
    {
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

    public:
        Timer() 
        {
            start();
        }

        ~Timer() 
        {
        }

        std::chrono::time_point<std::chrono::high_resolution_clock> start() 
        {
            start_time = std::chrono::high_resolution_clock::now();
            return start_time;
        }

        double elapsed_time(bool reset=true) 
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> begin_time = start_time;
            double elapsed_t = 0.0;
            if (reset) {
                elapsed_t = std::chrono::duration<double>(start() - begin_time).count();
            }
            else {
                elapsed_t = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin_time).count();
            }
            return elapsed_t;
        }

        static std::size_t now() 
        {
            std::chrono::time_point<std::chrono::system_clock> ts = std::chrono::system_clock::now();
            return std::size_t(std::chrono::duration_cast<std::chrono::microseconds>(ts.time_since_epoch()).count());
        }

        static std::size_t now_milli() 
        {
            std::chrono::time_point<std::chrono::system_clock> ts = std::chrono::system_clock::now();
            return std::size_t(std::chrono::duration_cast<std::chrono::milliseconds>(ts.time_since_epoch()).count());
        }

        static std::string localtime_str() 
        {
            auto now = std::chrono::system_clock::now();
            std::time_t base_time = std::chrono::system_clock::to_time_t(now);

            std::stringstream ss;

#if defined(_MSC_VER)
            struct tm base_date_local;
            localtime_s(&base_date_local, &base_time);
            ss << std::put_time(&base_date_local, "%Y%m%d_%X");
#else
            struct tm* base_date_local = localtime(&base_time);
            //ss << std::put_time(base_date_local, "%Y%m%d_%X");
            /* for gcc 4.8 */
            {
				char str[255] = {0,};
				if (0 < strftime(str, sizeof(str), "%Y%m%d_%X", base_date_local)) ss << str << std::endl;
			}
#endif

            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
            ss << '.' << std::setfill('0') << std::setw(3) << ms.count();

            return ss.str();
        }

        static std::string epoch_to_localtime_str(std::size_t epoch_microseconds)
        {
            double timestamp_usec = (epoch_microseconds / 1000000.0);
            double timestamp_sec = floor(timestamp_usec);
            double timestamp_subsec = round((timestamp_usec - timestamp_sec) * 1000000.0);

            std::stringstream ss;
            std::time_t epochtime = timestamp_sec;
#if defined(_MSC_VER)
            struct tm base_date_local;
            localtime_s(&base_date_local, &epochtime);
            ss << std::put_time(&base_date_local, "%Y%m%d_%X") << "." << timestamp_subsec;
#else
            struct tm *base_date_local = localtime(&epochtime);
            //ss << std::put_time(base_date_local, "%Y%m%d_%X") << "." << timestamp_subsec;
			/* for gcc 4.8 */
            {
				char str[255] = {0,};
				if (0 < strftime(str, sizeof(str), "%Y%m%d_%X", base_date_local)) ss << str << "." << timestamp_subsec;
			}
#endif

            return ss.str();
        }
    };
}   /* namespace SOSLAB */


#endif /* TIMER_HPP_ */
