cdef extern from "approxidate.h":
	cdef struct timeval:
		long int tv_sec
		long int tv_usec

	int approxidate(char*, timeval*)
