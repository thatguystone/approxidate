#define _XOPEN_SOURCE
#include <stdio.h>

#include "approxidate.h"

void dump() {
	struct timeval t;
	if (approxidate("10/Mar/2013:00:00:02.345 -0500", &t) != 0) {
		printf("ERROR\n");
		exit(1);
	}
	
	printf("USEC: %ld\n", t.tv_usec);
	
	char buff[200];
	snprintf(buff, 200, "%ld", t.tv_sec);
	
	struct tm m;
	strptime(buff, "%s", &m);
	
	strftime(buff, sizeof(buff), "%a, %d %b %y %T %z", &m);
	printf("%s\n", buff);
	
	exit(0);
}

int main() {
	// dump();
	// unsigned long t = approxidate("may 11 2013", &error);
	
	struct timeval start, end;
	
	gettimeofday(&start, NULL);
	
	for (int i = 0; i < 1000000; i++) {
		// struct tm m;
		// strptime("10/Mar/2013:00:00:02", "%d/%b/%Y:%T", &m);
		
		struct timeval t;
		approxidate("10/Mar/2013:00:00:02.003 -0500", &t);
	}
	
	gettimeofday(&end, NULL);
	
	long usec = end.tv_usec - start.tv_usec;
	double run = usec/((double)(1000*1000));
	run += end.tv_sec - start.tv_sec;
	
	printf("Ran in: %lf\n", run);
	return 0;
}