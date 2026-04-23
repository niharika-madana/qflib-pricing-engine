/** 
@file  defines.hpp
@brief Library-wide version numbers, macro, and constant definitions
*/

#pragma once

/** version string */

constexpr const char* QF_VERSION_STRING = 
#ifdef NDEBUG
    "1.0.0";
#else
    "1.0.0-debug";
#endif

/** version numbers */
constexpr int QF_VERSION_MAJOR = 1;
constexpr int QF_VERSION_MINOR = 0;
constexpr int QF_VERSION_REVISION = 0;

/** Macro for namespaces */
#define BEGIN_NAMESPACE(x)	namespace x {
#define END_NAMESPACE(x)	}

/** Macro for Extern C */
#define BEGIN_EXTERN_C  extern "C" {
#define END_EXTERN_C    }

/** number of days in a year */
constexpr double DAYS_PER_YEAR = 365.25;

/** number of seconds in a day */
constexpr double SECS_PER_DAY = 86400.; //(24.*60*60)
constexpr long SECS_PER_DAY_LONG = 86400L;

/** number of seconds in a year */
constexpr double SECS_PER_YEAR = (SECS_PER_DAY * DAYS_PER_YEAR);

/** number of seconds in an hour */
constexpr double SECS_PER_HOUR = 3600.;

// math constants
#define _USE_MATH_DEFINES
#include <cmath>

// extra math constants
/** 1/sqrt(2*pi) */
constexpr double M_1_SQRT2PI = 0.398942280401432678;
