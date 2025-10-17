#include "unix_time.h"


void time_to_date(struct HumanTime *const pHumanTime, const struct timespec *const pTimespec, const int8_t timezone)
{
	const time_t unix_timestamp_with_timezone = pTimespec->tv_sec + (timezone * SECONDS_IN_HOUR);

	pHumanTime->year = unix_timestamp_with_timezone / SECONDS_IN_YEAR;

	const uint8_t leap_years = (pHumanTime->year - 2) / 4;

	uint8_t isLeap = 0;

	if (((pHumanTime->year - 2) % 4) == 0)
	{
		isLeap = 1;
	}

	const uint16_t days_from_start = (unix_timestamp_with_timezone / SECONDS_IN_DAY);

	const uint16_t days_in_current_year = ((days_from_start - leap_years) + isLeap) % 365;

	if (days_in_current_year <= 31)
	{
		pHumanTime->month = 1;
		pHumanTime->day = days_in_current_year;
	}
	else if (days_in_current_year <= 59 + isLeap)
	{
		pHumanTime->month = 2;
		pHumanTime->day = days_in_current_year - 31;
	}
	else if (days_in_current_year <= 90 + isLeap)
	{
		pHumanTime->month = 3;
		pHumanTime->day = days_in_current_year - (59 + isLeap);
	}
	else if (days_in_current_year <= 120 + isLeap)
	{
		pHumanTime->month = 4;
		pHumanTime->day = days_in_current_year - (90 + isLeap);
	}
	else if (days_in_current_year <= 151 + isLeap)
	{
		pHumanTime->month = 5;
		pHumanTime->day = days_in_current_year - (120 + isLeap);
	}
	else if (days_in_current_year <= 181 + isLeap)
	{
		pHumanTime->month = 6;
		pHumanTime->day = days_in_current_year - (151 + isLeap);
	}
	else if (days_in_current_year <= 212 + isLeap)
	{
		pHumanTime->month = 7;
		pHumanTime->day = days_in_current_year - (181 + isLeap);
	}
	else if (days_in_current_year <= 243 + isLeap)
	{
		pHumanTime->month = 8;
		pHumanTime->day = days_in_current_year - (212 + isLeap);
	}
	else if (days_in_current_year <= 273 + isLeap)
	{
		pHumanTime->month = 9;
		pHumanTime->day = days_in_current_year - (243 + isLeap);
	}
	else if (days_in_current_year <= 304 + isLeap)
	{
		pHumanTime->month = 10;
		pHumanTime->day = days_in_current_year - (273 + isLeap);
	}
	else if (days_in_current_year <= 334 + isLeap)
	{
		pHumanTime->month = 11;
		pHumanTime->day = days_in_current_year - (304 + isLeap);
	}
	else if (days_in_current_year <= 365 + isLeap)
	{
		pHumanTime->month = 12;
		pHumanTime->day = days_in_current_year - (334 + isLeap);
	}

	const uint32_t seconds_in_current_day = unix_timestamp_with_timezone - (days_from_start * SECONDS_IN_DAY);

	pHumanTime->hour = seconds_in_current_day / SECONDS_IN_HOUR;

	const uint16_t seconds_in_current_hour = seconds_in_current_day - (pHumanTime->hour * SECONDS_IN_HOUR);

	pHumanTime->minute = seconds_in_current_hour / 60;

	pHumanTime->second = seconds_in_current_hour - (pHumanTime->minute * 60);

	pHumanTime->nanosecond = pTimespec->tv_nsec;
	pHumanTime->year += 1970;
}
