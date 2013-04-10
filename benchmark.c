#define _XOPEN_SOURCE
#define _GNU_SOURCE 500
#include <stdio.h>
#include <time.h>

#include "approxidate.h"

#define ROUNDS 1000000

int main() {
	long usec;
	struct timeval start, end;
	gettimeofday(&start, NULL);

	for (int i = 0; i < ROUNDS; i++) {
		struct timeval t;
		approxidate("10/Mar/2013:00:00:02.003 -0500", &t);
	}

	gettimeofday(&end, NULL);
	usec = end.tv_usec - start.tv_usec;

	double approxidate_time = usec/((double)(1000*1000));
	approxidate_time += end.tv_sec - start.tv_sec;

	gettimeofday(&start, NULL);

	for (int i = 0; i < ROUNDS; i++) {
		struct tm m;
		strptime("10/Mar/2013:00:00:02", "%d/%b/%Y:%T", &m);
	}

	gettimeofday(&end, NULL);
	usec = end.tv_usec - start.tv_usec;

	double strptime_time = usec/((double)(1000*1000));
	strptime_time += end.tv_sec - start.tv_sec;

	printf("approxidate time: %lf\n", approxidate_time);
	printf("strptime time: %lf\n", strptime_time);
	return 0;
}
