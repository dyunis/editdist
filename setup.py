try:
    from setuptools import setup, Extension
except ImportError:
    from distutils import setup, Extension
# from Cython.Build import cythonize
# ext_modules = cythonize('editdist/wrapper.pyx')

ext_modules = [
    Extension(
        'editdist.wrapper',
        ['editdist/_editdist.cpp', 'editdist/wrapper.cpp'],
        include_dirs=['./editdist']
    )
]

setup(
    name='editdist',
    version='0.0.1',
    packages=['editdist'],
    ext_modules=ext_modules,
    setup_requires=['cython >= 0.29'],
    package_data={'editdist': ['_editdist.h']}
)
