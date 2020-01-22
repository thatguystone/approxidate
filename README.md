# Approxidate [![Build Status](https://github.com/thatguystone/approxidate/workflows/test/badge.svg)](https://github.com/thatguystone/approxidate/actions)

Taken from Linus' original code in `/git/date.c`, approxidate gives you a
dead-simple way to get a timestamp from tons of date formats.  Unlike git's
original approxidate, this approxidate also returns microseconds.

## Usage

There are two functions:

```c

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

```

When compiling, copy both approxidate.{c,h} to your project, link in the math
library (-lm), and you're good.

```c
#include <approxidate.h>

struct timeval t;
approxidate("10/Mar/2013:12:43:02.603 -0500", &t);
approxidate("10/Mar/2013:12:43:02 -0500", &t);
```

> Note: If no timezone is given, the system's local timezone is used.

For more examples, check out [approxidate-test.c](approxidate-test.c).

## Speed

From [approxidate-test.c](approxidate-test.c) (for 1,000,000 iterations):

```bash
$ make test
...
approxidate time: 0.144372
strptime time: 0.624939
```

## Python

Check out: https://pypi.python.org/pypi/approxidate
