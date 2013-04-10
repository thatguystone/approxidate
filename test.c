#include <stdio.h>
#include <assert.h>

#include "approxidate.h"

static int errors = 0;

#define assert_equal(a, b) if (a != b) { \
	fprintf(stderr, "Error: %ld != %ld\n", (long)a, (long)b); \
	errors++; \
}

int main() {
	struct timeval tv;
	approxidate("10/Mar/2013:00:00:02.003", &tv);
	assert_equal(tv.tv_sec, 1362891602);
	assert_equal(tv.tv_usec, 3000);

	approxidate("10/Mar/2013:00:00:02", &tv);
	assert_equal(tv.tv_sec, 1362891602);
	assert_equal(tv.tv_usec, 0);

	approxidate("10/Mar/2013:00:00:07", &tv);
	assert_equal(tv.tv_sec, 1362891607);
	assert_equal(tv.tv_usec, 0);

	approxidate("10/Mar/2012:00:00:07", &tv);
	assert_equal(tv.tv_sec, 1331355607);
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

	approxidate("10/Mar/2012:00:00:07.657891 -110", &tv);
	assert_equal(tv.tv_sec, 1331355607);
	assert_equal(tv.tv_usec, 657891);

	gettimeofday(&tv, NULL);
	long usec = tv.tv_usec;
	approxidate("10/Mar/2012", &tv);

	if (!((usec - 10000) < tv.tv_usec && (usec + 10000) > tv.tv_usec)) {
		fprintf(stderr, "Error: usec calculation for anonymous time is off\n"); \
		errors++;
	}

	approxidate("00:00:07.657891", &tv);
	assert_equal(tv.tv_usec, 657891);

	approxidate("23:11:07.9876 +1400", &tv);
	assert_equal(tv.tv_usec, 987600);

	approxidate("23:11:07.9876", &tv);
	assert_equal(tv.tv_usec, 987600);

	if (errors > 0) {
		fprintf(stderr, "%d tests failed\n", errors);
		return 1;
	} else {
		fprintf(stderr, "All tests passed!\n");
	}

	return 0;
}
