cimport approxidate

def approx(date):
	if isinstance(date, unicode):
		date = date.encode('UTF-8')

	cdef timeval tv
	if approxidate(date, &tv) == -1:
		return -1.0
	return tv.tv_sec + (tv.tv_usec / 1000000.0)
