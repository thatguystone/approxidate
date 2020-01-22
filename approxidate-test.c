#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 200809L
#include "approxidate.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static time_t _start_of_day(time_t sec)
{
	return sec - (sec % 86400);
}

static double monotonic_now()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);

	return ts.tv_sec + (ts.tv_nsec / 1000000000.0);
}

static bool approxidate_test()
{
	long           usec;
	time_t         ts;
	struct tm*     tm;
	char           buff[128];
	struct timeval tv;
	struct timeval tv_rel;
	int            errors = 0;

#define assert_equal(a, b)                                                     \
	if (a != b) {                                                              \
		fprintf(                                                               \
			stderr,                                                            \
			"Test failure at line %d: %ld != %ld\n",                           \
			__LINE__,                                                          \
			(long)a,                                                           \
			(long)b);                                                          \
		errors++;                                                              \
	}

	approxidate("10/Mar/2013:00:00:02.003 UTC", &tv);
	assert_equal(tv.tv_sec, 1362873602);
	assert_equal(tv.tv_usec, 3000);

	approxidate("10/Mar/2013:00:00:02 UTC", &tv);
	assert_equal(tv.tv_sec, 1362873602);
	assert_equal(tv.tv_usec, 0);

	approxidate("10/Mar/2013:00:00:07 UTC", &tv);
	assert_equal(tv.tv_sec, 1362873607);
	assert_equal(tv.tv_usec, 0);

	approxidate("10/Mar/2012:00:00:07 UTC", &tv);
	assert_equal(tv.tv_sec, 1331337607);
	assert_equal(tv.tv_usec, 0);

	approxidate("10/Mar/2012:00:00:07 +0500", &tv);
	assert_equal(tv.tv_sec, 1331319607);
	assert_equal(tv.tv_usec, 0);

	approxidate("10/Mar/2012:00:00:07.657891 +0500", &tv);
	assert_equal(tv.tv_sec, 1331319607);
	assert_equal(tv.tv_usec, 657891);

	approxidate("10/Mar/2012:00:00:07.657891 +1400", &tv);
	assert_equal(tv.tv_sec, 1331287207);
	assert_equal(tv.tv_usec, 657891);

	approxidate("10/Mar/2012:00:00:07.657891 -0110", &tv);
	assert_equal(tv.tv_sec, 1331341807);
	assert_equal(tv.tv_usec, 657891);

	approxidate("mar 10 2013 00:00:07 UTC", &tv);
	assert_equal(tv.tv_sec, 1362873607);
	assert_equal(tv.tv_usec, 0);

	approxidate("mar 10 2013 04:00:07 -0500", &tv);
	assert_equal(tv.tv_sec, 1362906007);
	assert_equal(tv.tv_usec, 0);

	approxidate("march 10 2013 04:00:07 -0500", &tv);
	assert_equal(tv.tv_sec, 1362906007);
	assert_equal(tv.tv_usec, 0);

	approxidate("march 10 2013 04:00:07 -0500", &tv);
	assert_equal(tv.tv_sec, 1362906007);
	assert_equal(tv.tv_usec, 0);

	approxidate("10 march 2013 04:00:07 -0500", &tv);
	assert_equal(tv.tv_sec, 1362906007);
	assert_equal(tv.tv_usec, 0);

	approxidate("2013 10 march 04:00:07 -0500", &tv);
	assert_equal(tv.tv_sec, 1362906007);
	assert_equal(tv.tv_usec, 0);

	approxidate("2013 march 10 04:00:07 -0500", &tv);
	assert_equal(tv.tv_sec, 1362906007);
	assert_equal(tv.tv_usec, 0);

	approxidate("00:00:07.657891", &tv);
	assert_equal(tv.tv_usec, 657891);

	approxidate("23:11:07.9876 +1400", &tv);
	assert_equal(tv.tv_usec, 987600);

	approxidate("23:11:07.9876", &tv);
	assert_equal(tv.tv_usec, 987600);

	approxidate("1/1/2014", &tv);
	assert_equal(_start_of_day(tv.tv_sec), 1388534400);

	approxidate("1/1/2014 UTC", &tv);
	assert_equal(_start_of_day(tv.tv_sec), 1388534400);

	tv_rel.tv_sec  = 1577910617; // 2020-01-01 12:30:17 -08:00
	tv_rel.tv_usec = 0;

	approxidate_relative("1/1/2014", &tv, &tv_rel);
	assert_equal(tv.tv_sec, 1388608217);

	/*
	 * Git doesn't allow dates more than 10 days in the future. Make sure
	 * approxidate does.
	 *   - if today is 3/15/2015
	 *   - 8/15/2015 should parse as "Aug 15, 2015", not "Mar 8, 2015".
	 */
	ts = time(NULL);
	ts += 86400 * 31 * 5;
	tm = gmtime(&ts);
	strftime(buff, sizeof(buff), "%m/%d/%Y", tm);
	approxidate(buff, &tv);
	assert_equal(_start_of_day(tv.tv_sec), _start_of_day(ts));

	gettimeofday(&tv, NULL);
	usec = tv.tv_usec;
	approxidate("10/Mar/2012", &tv);

	if (!((usec - 10000) < tv.tv_usec && (usec + 10000) > tv.tv_usec)) {
		fprintf(stderr, "Error: usec calculation for anonymous time is off\n");
		errors++;
	}

	if (errors > 0) {
		fprintf(stderr, "%d tests failed\n", errors);
		return false;
	} else {
		fprintf(stderr, "All tests passed\n");
	}

	return true;
}

static void approxidate_benchmark()
{
	const int ROUNDS = 1000000;
	double    start  = monotonic_now();

	for (int i = 0; i < ROUNDS; i++) {
		struct timeval t;
		assert(approxidate("10/Mar/2013:00:00:02.003 -0500", &t) >= 0);
	}

	printf("approxidate time: %lf\n", monotonic_now() - start);

	start = monotonic_now();
	for (int i = 0; i < ROUNDS; i++) {
		struct tm m;
		assert(strptime("10/Mar/2013:00:00:02", "%d/%b/%Y:%T", &m) != NULL);
	}

	printf("strptime time: %lf\n", monotonic_now() - start);
}

int main()
{
	if (!approxidate_test()) {
		return EXIT_FAILURE;
	}

	approxidate_benchmark();

	return EXIT_SUCCESS;
}
