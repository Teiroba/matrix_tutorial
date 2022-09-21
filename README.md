# matrix_tutorial

Simple implementation of matrices in C for educational purposes about C programming under Linux.

## Types

- Type matrix : `matrix`,
  qui contient `ok` (matrice valide), `n1` (nombre de lignes) et `n2` (nombre de colonnes)
- Type scalar : `double`

## Opérateurs
- Addition de matrices :
  ```c 
  matrix matrix_add(matrix m, matrix n)
  ```
- Multiplication de matrices :
  ```c 
  matrix matrix_mul(matrix, matrix)
  ```
- Exponentiation rapide de matrices :
  ```c 
  matrix matrix_power(matrix, unsigned)
  ```
- Multiplication de matrice par un scalaire :
  ```c
  matrix scalar_multiplication(matrix, scalar)
  ```
- Coefficient i,j de la matrice m :
  ```c 
  scalar *matrix_get(matrix m, unsigned i, unsigned j)
  ```

## Fonctions de création

- Création de matrice :
  ```c 
  matrix matrix_create(unsigned, unsigned, scalar)
  ```
- Matrice identité de taille n :
  ```c
  matrix matrix_identity(unsigned n)
  ```
- Destruction de matrice :
  ```c
  void matrix_destroy(matrix)
  ```

## Fonctions d'affichage

- Affiche la matrice dans le fichier f :
  ```c
  void matrix_print(FILE *f, matrix)
  ```
