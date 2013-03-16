# Approxidate

Taken from Linus' original code in `/git/date.c`, approxidate gives you a dead-simple way to get a timestamp from tons of date formats.  Unlike git's original approxidate, this approxidate also returns microseconds.

## Usage

There's only one function: `int approxidate(const char *date, struct timeval *t)`.  It returns 0 when it parsed the date, -1 when it couldn't.

```c
#include <approxidate.h>

struct timeval t;
approxidate("10/Mar/2013:12:43:02.603 -0500", &t);
approxidate("10/Mar/2013:12:43:02 -0500", &t);
```

For more, see [test.c](test.c).
