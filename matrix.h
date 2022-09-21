#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>

typedef double scalar;

typedef struct matrix {
  unsigned n1, n2;
  bool ok;
  scalar *data;
} matrix;

matrix matrix_create(unsigned n1, unsigned n2, scalar v);
void matrix_destroy(matrix m);
matrix matrix_identity(unsigned n);
scalar *matrix_get(matrix m, unsigned i, unsigned j);
matrix matrix_add(matrix m, matrix n);
matrix matrix_mul(matrix m, matrix n);
matrix matrix_power(matrix m, unsigned p);
matrix scalar_multiplication(matrix m, scalar k);
void matrix_print(FILE *f, matrix m);

matrix add_matrix(matrix m, matrix n);

#endif /* MATRIX_H */
