#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include <stdint.h>

#include <sys/time.h>

#include "colors.h"


//const size_t unix_timestamp_with_timezone = 1709251200;// 2024 march 1
//const size_t unix_timestamp_with_timezone = 1709164800;// 2024 february 29
//const size_t unix_timestamp_with_timezone = 1740787200;// 2025 march 1
//const size_t unix_timestamp_with_timezone = 1740700800;// 2025 february 28

#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_MONTH 2629743
#define SECONDS_IN_YEAR 31556926

typedef struct HumanTime {
	long nanosecond;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} HumanTime;

void time_to_date(struct HumanTime *const pHumanTime, const struct timespec *const pTimespec, const int8_t timezone);


#define print_log(humanTime, str1, str2){fprintf(stderr, CYAN "%d-%d-%d %d:%d:%d.%ld " BLUE "pid:%d [" MAGENTA "%s() " RESET_COLOR str1 BLUE "]" RESET_COLOR ": " str2 RESET_COLOR "\n",\
	humanTime.year, humanTime.month, humanTime.day,\
	humanTime.hour, humanTime.minute, humanTime.second,\
	humanTime.nanosecond, getpid(), __func__);}

