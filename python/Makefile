all:
	python setup.py cython build_ext --inplace

dist: all
	python setup.py sdist

upload: clean all
	python setup.py sdist upload

clean:
	rm -rf build/
	rm -rf dist/
	rm -f MANIFEST
	rm -f pyapproxidate.c
	rm -f approxidate.*
	rm -f approxidate.so
