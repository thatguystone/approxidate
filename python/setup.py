from distutils.core import setup
from distutils.extension import Extension
import sys

with open('README') as f:
	long_description = f.read()

args = {
	'name': 'approxidate',
	'version': '1.0.0',
	'url': 'https://github.com/thatguystone/approxidate',
	'author': 'Andrew Stone',
	'author_email': 'andrew@clovar.com',
	'license': 'GPL v2',
	'description': 'a quick way to get a unix timestamp from a ton of arbitrary date formats',
	'long_description': long_description,
}

if sys.argv[1] == 'cython':
	import shutil
	from Cython.Distutils import build_ext

	for ext in ('c', 'h'):
		shutil.copyfile('../approxidate.%s' % ext, 'approxidate.%s' % ext)

	sys.argv.remove('cython')
	args.update({
		'cmdclass': {'build_ext': build_ext},
		'ext_modules': [Extension("approxidate", ["pyapproxidate.pyx", "approxidate.c"])]
	})
else:
	args.update({
		'ext_modules': [Extension("approxidate", ["pyapproxidate.c", "approxidate.c"])]
	})

setup(**args)
