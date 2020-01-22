all: test

test: approxidate-test
	./approxidate-test

approxidate-test: *.c *.h
	$(CC) -g -Wall -O2 -std=c11 $@.c approxidate.c -o $@ -lm

clean:
	rm -f approxidate-test
	$(MAKE) -C python clean
