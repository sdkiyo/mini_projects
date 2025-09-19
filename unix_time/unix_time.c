#include "unix_time.h"


int8_t time_to_date(struct HumanTime *const humanTime, const struct timespec *const timespec_pointer, const int8_t timezone)
{
	const size_t unix_timestamp_with_timezone = timespec_pointer->tv_sec + (timezone * SECONDS_IN_HOUR);

	humanTime->year = unix_timestamp_with_timezone / SECONDS_IN_YEAR;

	const uint8_t leap_years = (humanTime->year - 2) / 4;

	uint8_t isLeap = (humanTime->year - 2) % 4;
	if (isLeap == 0)
	{
		isLeap = 1;// leap year
	}
	else
	{
		isLeap = 0;// not leap year
	}

	const uint16_t days_in_current_year = (((unix_timestamp_with_timezone / SECONDS_IN_DAY) - leap_years) + isLeap) % 365;

	if (days_in_current_year <= 31)
	{
		humanTime->month = 1;
		humanTime->day = days_in_current_year;
	}
	else if (days_in_current_year <= 59 + isLeap)
	{
		humanTime->month = 2;
		humanTime->day = days_in_current_year - 31;
	}
	else if (days_in_current_year <= 90 + isLeap)
	{
		humanTime->month = 3;
		humanTime->day = days_in_current_year - (59 + isLeap);
	}
	else if (days_in_current_year <= 120 + isLeap)
	{
		humanTime->month = 4;
		humanTime->day = days_in_current_year - (90 + isLeap);
	}
	else if (days_in_current_year <= 151 + isLeap)
	{
		humanTime->month = 5;
		humanTime->day = days_in_current_year - (120 + isLeap);
	}
	else if (days_in_current_year <= 181 + isLeap)
	{
		humanTime->month = 6;
		humanTime->day = days_in_current_year - (151 + isLeap);
	}
	else if (days_in_current_year <= 212 + isLeap)
	{
		humanTime->month = 7;
		humanTime->day = days_in_current_year - (181 + isLeap);
	}
	else if (days_in_current_year <= 243 + isLeap)
	{
		humanTime->month = 8;
		humanTime->day = days_in_current_year - (212 + isLeap);
	}
	else if (days_in_current_year <= 273 + isLeap)
	{
		humanTime->month = 9;
		humanTime->day = days_in_current_year - (243 + isLeap);
	}
	else if (days_in_current_year <= 304 + isLeap)
	{
		humanTime->month = 10;
		humanTime->day = days_in_current_year - (273 + isLeap);
	}
	else if (days_in_current_year <= 334 + isLeap)
	{
		humanTime->month = 11;
		humanTime->day = days_in_current_year - (304 + isLeap);
	}
	else if (days_in_current_year <= 365 + isLeap)
	{
		humanTime->month = 12;
		humanTime->day = days_in_current_year - (334 + isLeap);
	}

	const uint32_t seconds_in_current_day = (unix_timestamp_with_timezone) - (((unix_timestamp_with_timezone) / SECONDS_IN_DAY) * SECONDS_IN_DAY);

	humanTime->hour = seconds_in_current_day / SECONDS_IN_HOUR;

	humanTime->minute = (seconds_in_current_day - (humanTime->hour * SECONDS_IN_HOUR)) / 60;

	humanTime->second = seconds_in_current_day - (humanTime->hour * SECONDS_IN_HOUR) - (humanTime->minute * 60);

	humanTime->nanosecond = timespec_pointer->tv_nsec;
	humanTime->year += 1970;

	return 0;
}
