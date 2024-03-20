/*
 * soslab_typdef.h
 *
 *  Created on: Nov 16, 2018
 *      Author: gnohead
 */

#ifndef SOSLAB_TYPEDEF_H_
#define SOSLAB_TYPEDEF_H_

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <cstring>
#include <system_error>
#include <limits>

#define _USE_MATH_DEFINES
#include <math.h>

/* Macros */
#ifdef SOSLABAPI_EXPORTS
	#if defined(_MSC_VER)
		#define SOSLAB_EXPORTS __declspec(dllexport)
	#elif defined(__GNUC__)
		#define SOSLABAPI_EXPORTS __attribute__((visibility("default")))
	#endif
#endif

#ifndef SOSLAB_EXPORTS
	#define SOSLAB_EXPORTS
#endif


/* un-used */
#define UNUSED(x) (void)(x)

/** @brief default value for 1 Giga */
#define CONST_ONE_GIGA  1000000000.0
/** @brief default value for 1 nano */
#define CONST_ONE_NANO  (1.0 / CONST_ONE_GIGA)
/** @brief default value for 20 nano */
#define CONST_20_NANO   (20.0 * CONST_ONE_NANO)
/** @brief default value for DEG2RAD */
#define DEG2RAD         (M_PI / 180.0)
/** @brief default value for RAD2DEG */
#define RAD2DEG         (180.0 / M_PI)

/* common type definitions */
namespace SOSLAB
{
    /** @brief integer */
    typedef int32_t INT_T;

    /** @brief unsigned int */
    typedef uint32_t UINT_T;

    /** @brief floating point */
    typedef double FLOAT_T;

    /** @brief data arryay */
    typedef std::vector<uint8_t> hex_array_t;

    /** @brief The structure of a single point corresponds to the speherical coordinate system. */
#if defined(_MSC_VER)
#pragma pack(push, 1) 
    typedef struct _SPHERICAL_POINT_T
#else
    typedef struct __attribute__((packed)) _SPHERICAL_POINT_T
#endif
    {
        FLOAT_T r;          /**< Range value */
        FLOAT_T theta;      /**< Theta value */
        FLOAT_T phi;        /**< Phi value */

        bool operator==(_SPHERICAL_POINT_T const& pt) const
        {
            bool retval = (std::numeric_limits<FLOAT_T>::epsilon() < abs(r - pt.r));
            retval &= (std::numeric_limits<FLOAT_T>::epsilon() < abs(theta - pt.theta));
            retval &= (std::numeric_limits<FLOAT_T>::epsilon() < abs(phi - pt.phi));
            return retval;
        }

    } spherical_point_t;
#if defined(_MSC_VER)
#pragma pack(pop)
#endif


    /** @brief The structure of a single point corresponds to the cartesian coordinate system. */
#if defined(_MSC_VER)
#pragma pack(push, 1) 
    typedef struct _CARTESIAN_POINT_T
#else
    typedef struct __attribute__((packed)) _CARTESIAN_POINT_T
#endif
    {
        FLOAT_T x;          /**< x value */
        FLOAT_T y;          /**< y value */
        FLOAT_T z;          /**< z value */

        bool operator==(_CARTESIAN_POINT_T const& pt) const
        {
            bool retval = (std::numeric_limits<FLOAT_T>::epsilon() < abs(x - pt.x));
            retval &= (std::numeric_limits<FLOAT_T>::epsilon() < abs(y - pt.y));
            retval &= (std::numeric_limits<FLOAT_T>::epsilon() < abs(z - pt.z));
            return retval;
        }

    } cartesian_point_t;
#if defined(_MSC_VER)
#pragma pack(pop)
#endif


    /** @brief The structure of a single point for TWO coordinate system. */
#if defined(_MSC_VER)
#pragma pack(push, 1) 
    typedef struct _POINT_T
#else
    typedef struct __attribute__((packed)) _POINT_T
#endif
    {
        std::size_t index;          /**< sequence index */
        std::size_t timestamp_1us;  /**< timestamp [1us] */
        spherical_point_t rtp;      /**< spherical coordinate */
        cartesian_point_t xyz;      /**< cartesian coordinate */
        FLOAT_T pw;                 /**< pulse width */

        _POINT_T() { memset(this, 0, sizeof(_POINT_T)); }

        bool operator==(_POINT_T const& pt) const
        {
            bool retval = (index == pt.index);
            retval &= (timestamp_1us == pt.timestamp_1us);
            retval &= (rtp == pt.rtp);
            retval &= (xyz == pt.xyz);
            retval &= (pw == pt.pw);
            return retval;
        }

    } point_t;
#if defined(_MSC_VER)
#pragma pack(pop)
#endif

    /** @brief Structure of the pointcloud of SOSLAB LiDAR */
    typedef std::vector<point_t> pointcloud_t;

    /** @brief IP communication address */
    typedef struct IP_ADDRESS_T {
        std::string ip_address;
        int port_number;
    } ip_settings_t;

    /** @biref Serial communication settings */
    typedef struct SERIAL_PORT_SETTINGS_T {
        std::string name;
        int baudrate;
    } serial_port_settings_t;

} /* namespace SOSLAB */


#endif /* SOSLAB_TYPEDEF_H_ */



