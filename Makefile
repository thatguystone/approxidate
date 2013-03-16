all: clean test
	@echo
	@./test

test: test.c approxidate.c approxidate.h
	gcc -g -Wall -O2 -std=gnu99 test.c approxidate.c -lm -o $@

clean:
	rm -f test