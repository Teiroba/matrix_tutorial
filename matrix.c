#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "matrix.h"

#define PRINT_PRECISION "6"
#define PRINT_DECIMAL_PRECISION "2"

matrix matrix_create(unsigned n1, unsigned n2, scalar v)
{
  matrix m={n1,n2,true,NULL};
  if(n1==0 || n2==0)
    return m;
  else if(SIZE_MAX / n1 <= n2)
    m.ok = false;
  else if (!(m.data=calloc(((size_t) n1)*n2, sizeof(scalar))))
    m.ok = false;
  else {
    for(unsigned i=0; i<n1; ++i)
      for(unsigned j=0; j<n2; ++j)
        *matrix_get(m,i,j) = v;
  }
  
  return m;
}

matrix matrix_identity(unsigned n)
{
  matrix m = matrix_create(n, n, 0.);
  if(!m.ok)
    return m;

  for(unsigned i=0; i<n; ++i)
    *matrix_get(m, i, i) = 1.;
  return m;
}

void matrix_destroy(matrix m)
{
  if(m.ok) {
    m.ok = false;
    free(m.data);
  }
}

scalar *matrix_get(matrix m, unsigned i, unsigned j)
{
  if(!m.ok || i>m.n1 || i>m.n2)
    return NULL;

  return &m.data[i*m.n2+j];
}

matrix matrix_add(matrix m, matrix n)
{
  matrix res={0,0,false,NULL};

  if(m.n1!=n.n1 || m.n2!=n.n2 || !m.ok || !n.ok)
    return res;

  res=matrix_create(m.n1, m.n2, 0.);
  for(unsigned i=0; i<m.n1; ++i)
    for(unsigned j=0; j<m.n2; ++j)
      *matrix_get(res, i, j) = *matrix_get(m, i, j) + *matrix_get(n, i, j);

  return res;
}

matrix matrix_mul(matrix m, matrix n)
{
  matrix res={0,0,false,NULL};

  if (!m.ok || !n.ok || (m.n2 != n.n1))
    return res;

  res = matrix_create(m.n1, n.n2, 0.);
  for (unsigned i = 0; i < m.n1; ++i)
    for (unsigned j = 0; j < m.n2; ++j)
      for (unsigned k = 0; k < m.n2; ++k)
        *matrix_get(res, i, j) += *matrix_get(m, i, k) * *matrix_get(n, k, j);

  return res;
}

matrix matrix_power(matrix m, unsigned p)
{
  matrix res = { 0, 0, false, NULL };
  matrix tmp = { 0, 0, false, NULL };

  if (!m.ok || (m.n1 != m.n2))
    return res;

  if (p == 0)
  {
    return matrix_identity(m.n1);
  }
  else if (p == 1)
  {
    tmp = matrix_identity(m.n1);
    res = matrix_mul(m, tmp);
    matrix_destroy(tmp);
    return res;
  }
  else
  {
    tmp = matrix_power(m, p / 2);
    res = matrix_mul(tmp, tmp);
    matrix_destroy(tmp);
    if (p % 2)
    {
      tmp = res;
      res = matrix_mul(tmp, m);
      matrix_destroy(tmp);
    }
    return res;
  }
}

void matrix_print(FILE *f, matrix m)
{
  if(!m.ok)
    fprintf(f, "Invalid matrix\n");
  else {
    for(unsigned i=0; i<m.n1; ++i) {
      for(unsigned j=0; j<m.n2; ++j)
        fprintf(
            f, 
            "%"PRINT_PRECISION"."PRINT_DECIMAL_PRECISION"f ",
            *matrix_get(m, i, j));
      fprintf(f, "\n");
    }
  }
}

matrix scalar_multiplication(matrix m, double k)
{
  matrix res = matrix_create(m.n1, m.n2, 0.);
  for(unsigned i=0; i<m.n1;++i)
    for(unsigned j=0; j<m.n2;++j)
      *matrix_get(res,i,j) = k* (*matrix_get(m,i,j));
  ertrthkjhswdytgf
  return res;
}
