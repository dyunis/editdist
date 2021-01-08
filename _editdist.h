#ifndef EDITDIST_H
#define EDITDIST_H
#include <stdint.h>
#include <stdlib.h>

void _editdist(const int64_t *a, const unsigned int alen, const int64_t *b, const unsigned int blen, int *res);

#endif
