#include "utest.h"
#include "matrix.h"

UTEST(matrix_create, simple) {
  matrix m = matrix_create(3, 5, 0.);
  ASSERT_TRUE(m.ok && m.n1==3 && m.n2==5);
}

UTEST(matrix_create, too_large) {
  matrix m = matrix_create((unsigned)-1, (unsigned)-1, 0.);
  ASSERT_FALSE(m.ok);
}

UTEST(matrix_create, zero) {
  matrix m = matrix_create(0, 0, 0.);
  ASSERT_TRUE(m.ok && m.n1==0 && m.n2==0);
}

UTEST(matrix_identity, simple) {
  matrix m = matrix_identity(42);
  ASSERT_TRUE(m.ok && m.n1==42 && m.n2==42);
}

UTEST(matrix_identity, too_large) {
  matrix m = matrix_identity((unsigned) -1);
  ASSERT_TRUE(!m.ok);
}

UTEST(matrix_identity, zero) {
  matrix m = matrix_identity(0);
  ASSERT_TRUE(m.ok && m.n1==0 && m.n2==0);
}

UTEST(matrix_destroy, simple) {
  matrix m = matrix_create(2, 5, 0.);
  matrix_destroy(m);
  ASSERT_TRUE(1);
}

UTEST(matrix_destroy, wrong) {
  matrix m;
  m.ok=false;
  m.data=(scalar*)0xdeadbeef;
  matrix_destroy(m);
  ASSERT_TRUE(1);
}

UTEST(matrix_get, simple) {
  matrix m = matrix_identity(12);
  ASSERT_TRUE(*matrix_get(m,3,3)==1.);
}

UTEST(matrix_get, wrong) {
  matrix m;
  m.ok=false;
  ASSERT_TRUE(matrix_get(m, 0, 0)==NULL);
}


UTEST(matrix_add,simple){
    matrix mat1 = matrix_create(5,5,5.);
    matrix mat2 = matrix_identity(5);
    matrix mat = matrix_add(mat1,mat2);
    for (int i = 0; i<5 ; i++){for (int j=0; j< 5; j++){
	ASSERT_TRUE(*matrix_get(mat,i,j)==*matrix_get(mat1,i,j)+*matrix_get(mat2,i,j));
    }}
}


UTEST(matrix_mul, simple) {
  matrix m = matrix_create(3, 5, 0.), n = matrix_create(5, 4, 0.), res;
#define GO(i, j, v) ASSERT_TRUE(*matrix_get(res, i, j) == v)
  *matrix_get(m, 0, 3) = 1.;
  *matrix_get(n, 3, 3) = 1.;
  *matrix_get(n, 3, 0) = 1.;

  res = matrix_mul(m, n);

  GO(0, 0, 1.);
  GO(0, 1, 0.);
  GO(0, 2, 0.);
  GO(0, 3, 1.);
  GO(1, 0, 0.);
  GO(1, 1, 0.);
  GO(1, 2, 0.);
  GO(1, 3, 0.);
  GO(2, 0, 0.);
  GO(2, 1, 0.);
  GO(2, 2, 0.);
  GO(2, 3, 0.);

  matrix_destroy(m); matrix_destroy(n); matrix_destroy(res);
  m = matrix_create(2, 2, 0.);
  *matrix_get(m, 1, 0) = -1.;
  *matrix_get(m, 0, 1) =  1.;
#define SUPER(p, a, b, c, d) do { res = matrix_power(m, p); GO(0, 0, a); GO(0, 1, b); GO(1, 0, c); GO(1, 1, d); } while (0)
  SUPER(0,  1.,  0.,  0.,  1.);
  SUPER(1,  0.,  1., -1.,  0.);
  SUPER(2, -1.,  0.,  0., -1.);
  SUPER(3,  0., -1.,  1.,  0.);
  SUPER(4,  1.,  0.,  0.,  1.);
#undef SUPER
#undef GO
/*
            0 0 0 1
0 0 0 1 0   0 0 0 0     1 0 0 1
0 0 0 0 0   0 0 0 0  =  0 0 0 0
0 0 0 0 0   1 0 0 1     0 0 0 0
            0 0 0 0


0  1 = rotation
-1 0   de -90°
*/
}

UTEST_MAIN()
