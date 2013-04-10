all: benchmark

libapproxidate.so:
	gcc -Wall -O2 -std=gnu99 -shared -fPIC approxidate.c -o $@

benchmark: clean benchmark.c approxidate.c approxidate.h
	gcc -g -Wall -O2 -std=gnu99 benchmark.c approxidate.c -lm -o $@
	@./benchmark

test: clean test.c approxidate.c approxidate.h
	gcc -g -Wall -O2 -std=gnu99 test.c approxidate.c -lm -o $@
	@./test

clean:
	rm -f benchmark
	rm -f libapproxidate.so
	rm -f test
