try:
    from setuptools import setup, Extension
except ImportError:
    from distutils import setup, Extension
# from Cython.Build import cythonize
# ext_modules = cythonize('wrapper.pyx')

ext_modules = [
    Extension(
        'editdist.wrapper',
        ['editdist/_editdist.cpp', 'editdist/wrapper.cpp'],
        include_dirs=['./editdist'],
        language='c++'
    )
]

setup(
    name='editdist',
    ext_modules=ext_modules,
    packages=['editdist'],
    package_data={'editdist': ['_editdist.h']}
)
