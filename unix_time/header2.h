


#include <errno.h>
#include <time.h>
 
#define SECS_PER_HOUR   (60 * 60)
#define SECS_PER_DAY    (SECS_PER_HOUR * 24)
 
/* Compute the `struct tm' representation of *T,
  25    offset OFFSET seconds east of UTC,
  26    and store year, yday, mon, mday, wday, hour, min, sec into *TP.
  27    Return nonzero if successful.  */
int
__offtime (t, offset, tp)
    const time_t *t;
    long int offset;
    struct tm *tp;
{
	time_t days, rem, y;
	const unsigned short int *ip;
 
	days = *t / SECS_PER_DAY;
	rem = *t % SECS_PER_DAY;
	rem += offset;
	while (rem < 0)
	{
		rem += SECS_PER_DAY;
		--days;
	}
	while (rem >= SECS_PER_DAY)
	{
		rem -= SECS_PER_DAY;
		++days;
	}
	tp->tm_hour = rem / SECS_PER_HOUR;
	rem %= SECS_PER_HOUR;
	tp->tm_min = rem / 60;
	tp->tm_sec = rem % 60;
   /* January 1, 1970 was a Thursday.  */
	tp->tm_wday = (4 + days) % 7;
	if (tp->tm_wday < 0)
		tp->tm_wday += 7;
	y = 1970;
 
#define DIV(a, b) ((a) / (b) - ((a) % (b) < 0))
#define LEAPS_THRU_END_OF(y) (DIV (y, 4) - DIV (y, 100) + DIV (y, 400))
 
	while (days < 0 || days >= (__isleap (y) ? 366 : 365))
	{
       /* Guess a corrected year, assuming 365 days per year.  */
		time_t yg = y + days / 365 - (days % 365 < 0);
 
       /* Adjust DAYS and Y to match the guessed year.  */
		days -= ((yg - y) * 365 + LEAPS_THRU_END_OF (yg - 1) - LEAPS_THRU_END_OF (y - 1));
		y = yg;
	}
	x = tp.tv_sec - ((tp.tv_sec / DAYS) * DAYS);// x = seconds in day
	printf("x%d\n", x);

	const int y = (((tp.tv_sec / 31536000) + 1970) - 1969) / 4;
	printf("y%d\n", y);

	tp->tm_year = y - 1900;
	if (tp->tm_year != y - 1900)
	{
       /* The year cannot be represented due to overflow.  */
		__set_errno (EOVERFLOW);
		return 0;
	}
	tp->tm_yday = days;
	ip = __mon_yday[__isleap(y)];
	for (y = 11; days < (long int) ip[y]; --y)
		continue;
	days -= ip[y];
	tp->tm_mon = y;
	tp->tm_mday = days + 1;
	return 1;
}




