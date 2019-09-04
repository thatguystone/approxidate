# Approxidate [![Build Status](https://github.com/thatguystone/approxidate/workflows/test/badge.svg)](https://github.com/thatguystone/approxidate/actions)

Taken from Linus' original code in `/git/date.c`, approxidate gives you a dead-simple way to get a timestamp from tons of date formats.  Unlike git's original approxidate, this approxidate also returns microseconds.

## Usage

There's only one function: `int approxidate(const char *date, struct timeval *t)`.  It returns 0 when it parsed the date, -1 when it couldn't.

When compiling, copy both approxidate.{c,h} to your project, link in the math library (-lm), and you're good.

```c
#include <approxidate.h>

struct timeval t;
approxidate("10/Mar/2013:12:43:02.603 -0500", &t);
approxidate("10/Mar/2013:12:43:02 -0500", &t);
```

> Note: If no timezone is given, the system's local timezone is used.

For more, see [test.c](test.c).

## Speed

From benchmark.c (for 1,000,000 iterations):

```bash
$ make

rm -f test
gcc -g -Wall -O2 -std=gnu99 benchmark.c approxidate.c -lm -o benchmark

approxidate time: 0.363872
strptime time: 0.622350
```

## Python

Check out: https://pypi.python.org/pypi/approxidate
