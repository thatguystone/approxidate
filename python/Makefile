SRCS = \
	approxidate/approxidate.c \
	approxidate/approxidate.h

develop: $(SRCS)
	python setup.py develop

test: $(SRCS)
	python setup.py test

sdist: $(SRCS)
	python setup.py sdist

upload:
	$(MAKE) clean
	$(MAKE) sdist
	twine upload --config-file=~/.config/pypi/rc dist/*

$(SRCS): approxidate/%: ../%
	cp $^ $@

clean:
	py3clean .
	rm -f $(SRCS)
	rm -f approxidate/*.so
	rm -rf *.egg-info
	rm -rf build/
	rm -rf dist/
