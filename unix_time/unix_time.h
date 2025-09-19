#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include <stdint.h>

#include <sys/time.h>

#include "colors.h"


//tp.tv_sec / 3600;// hours
//tp.tv_sec / 86400;// days
//tp.tv_sec / 2629743;// months
//tp.tv_sec / 31556926;// years
//const size_t unix_time = 1709251200;// 2024 march 1
//const size_t unix_time = 1709164800;// 2024 february 29
//const size_t unix_time = 1740787200;// 2025 march 1
//const size_t unix_time = 1740700800;// 2025 february 28

#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_MONTH 2629743
#define SECONDS_IN_YEAR 31556926

typedef struct HumanTime {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	long nanosecond;
} HumanTime;

int8_t time_to_date(struct HumanTime *const humanTime, const struct timespec *const timespec_pointer, const int8_t timezone);


#define print_log(humanTime, str1, str2){fprintf(stderr, cyan"%d-%d-%d %d:%d:%d.%ld " blue"pid:%d [" magenta"%s() "reset_color str1 blue"]"reset_color": " str2 reset_color"\n",\
	humanTime.year, humanTime.month, humanTime.day,\
	humanTime.hour, humanTime.minute, humanTime.second,\
	humanTime.nanosecond, getpid(), __func__);}

