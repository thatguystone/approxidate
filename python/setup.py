from distutils.core import setup
from distutils.extension import Extension

with open('README') as f:
	long_description = f.read()

try:
	from Cython.Build import cythonize
	ext = cythonize([Extension("approxidate", ["approxidate.pyx", "_approxidate.c"])])
except:
	ext = [Extension("approxidate", ["approxidate.c", "_approxidate.c"])]

setup(
	name='approxidate',
	version='1.0.2',
	url='https://github.com/thatguystone/approxidate',
	author='Andrew Stone',
	author_email='andrew@clovar.com',
	license='GPL v2',
	description='a quick way to get a unix timestamp from a ton of arbitrary date formats',
	long_description=long_description,
	ext_modules=ext,
)
