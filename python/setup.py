from setuptools import setup, Extension

with open("README.rst") as f:
    long_description = f.read()

setup(
    name="approxidate",
    version="1.0.4",
    url="https://github.com/thatguystone/approxidate",
    author="Andrew Stone",
    author_email="a@stne.dev",
    license="GPL v2",
    description="a quick way to get a unix timestamp from arbitrary date formats",
    long_description=long_description,
    project_urls={
        "Source": "https://github.com/thatguystone/approxidate",
        "Tracker": "https://github.com/thatguystone/approxidate/issues",
    },
    packages=["approxidate"],
    ext_modules=[
        Extension("approxidate._c", ["approxidate/_c.c", "approxidate/approxidate.c"]),
    ],
    package_data={"approxidate": ["approxidate.h"],},
)
