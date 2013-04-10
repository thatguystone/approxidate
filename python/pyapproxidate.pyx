cimport capproxidate

def approx(char *date):
	cdef capproxidate.timeval tv
	capproxidate.approxidate(date, &tv)
	return tv.tv_sec + (tv.tv_usec / 1000000.0)
