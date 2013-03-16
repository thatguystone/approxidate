#ifndef APPROXIDATE_H
#define APPROXIDATE_H

#include <math.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>

/**
 * @param date The date string
 * @param tv Where the time will be placed.
 *
 * @return 0 on success
 * @return 1 on error
 */
int approxidate(const char *date, struct timeval *tv);

#endif
