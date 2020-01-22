#pragma once
#include <sys/time.h>

/**
 * Get a unix timestamp from an arbitrary date string.
 *
 * If the given date string is missing any parts (date, time, etc), those parts
 * will be filled in from the current time.
 *
 * Returns -1 on parse failure, 0 on success.
 */
int approxidate(const char* date, struct timeval* tv);

/**
 * Get a unix timestamp from an arbitrary date string.
 *
 * Functions much like approxidate, except that if the given date string is
 * missing any parts (date, time, etc), those parts will be filled in from the
 * relative_to value; if relative_to is NULL, then now is used.
 *
 * Returns -1 on parse failure, 0 on success.
 */
int approxidate_relative(
	const char*           date,
	struct timeval*       tv,
	const struct timeval* relative_to);
