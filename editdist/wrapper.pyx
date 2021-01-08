# cython: language_level=3
# distutils: language = c++
# distutils: sources = editdist/_editdist.cpp

from libc.stdlib cimport malloc, free
from libc.stdint cimport int64_t

cdef extern from "./_editdist.h":
    void _editdist(const int64_t *a, const unsigned int alen, const int64_t *b, const unsigned int blen, int *res)

# c.f. https://github.com/roy-ht/editdistance/blob/master/editdistance/bycython.pyx
def d(object a, object b):
    cdef unsigned int i
    cdef int l_a = len(a)
    cdef int64_t *al = <int64_t *>malloc(l_a * sizeof(int64_t))
    for i in range(l_a):
        al[i] = hash(a[i])
    cdef int l_b = len(b)
    cdef int64_t *bl = <int64_t *>malloc(l_b * sizeof(int64_t))
    for i in range(l_b):
        bl[i] = hash(b[i])
    cdef int *res = <int *>malloc(4 * sizeof(int))
    _editdist(al, l_a, bl, l_b, res)
    free(al)
    free(bl)
    py_res = (res[0], res[1], res[2], res[3])
    free(res)
    return py_res
