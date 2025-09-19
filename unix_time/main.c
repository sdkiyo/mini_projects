#include "unix_time.h"
#include <time.h>
#include <sys/resource.h>

int main()
{
	struct timespec tp = {};
	clock_gettime(CLOCK_REALTIME, &tp);
	HumanTime ht = {};

	time_to_date(&ht, &tp, 3);

	print_log(ht, "FileName.c", "SSdffffffSdffffffSdffffffSdffffffSdffffffSdffffffdffffff");

	return 0;
}
