CFLAGS = \
	-Wall \
	-O2 \
	-std=gnu99

LDFLAGS = \
	-lm

all: benchmark

libapproxidate.so: approxidate.c approxidate.h
	$(CC) -shared -fPIC $(CFLAGS) approxidate.c -o $@

.PHONY: benchmark
benchmark:
	$(CC) $(CFLAGS) benchmark.c approxidate.c -o $@ $(LDFLAGS)
	@./benchmark

.PHONY: test
test:
	$(CC) -g $(CFLAGS) test.c approxidate.c -o $@ $(LDFLAGS)
	@./test

clean:
	rm -f benchmark
	rm -f libapproxidate.so
	rm -f test
