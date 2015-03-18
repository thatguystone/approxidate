dist: c
	python setup.py sdist

upload: c
	python setup.py sdist upload

c: _approxidate.c approxidate.h

_approxidate.c: ../approxidate.c
	cp $^ $@

approxidate.h: ../approxidate.h
	cp $^ $@

clean:
	rm -rf build/
	rm -rf dist/
	rm -f MANIFEST
	rm -f *.c *h
	rm -f approxidate.so
