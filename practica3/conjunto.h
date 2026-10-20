#include <stdio.h>
#include <stdlib.h>

#define UMIN 0
#define UMAX 9

typedef int tTipo;

typedef struct conjunto {
    tTipo *eltos;
    int cardinal;
    int tama;
} Conjunto;

Conjunto *creaConjunto(int tama);
Conjunto *copiaConjunto(Conjunto *conj);
void imprimeConjunto(Conjunto *conj);
int pertenece(Conjunto *A, tTipo x);
Conjunto *insertar(Conjunto *A, tTipo x);
Conjunto *insertarRango(Conjunto *A, int a, int b);
Conjunto *unirConjunto(Conjunto *A, Conjunto *B);
Conjunto *intersecConjunto(Conjunto *A, Conjunto *B);
Conjunto *diferenConjunto(Conjunto *A, Conjunto *B);
Conjunto *complementoConjunto(Conjunto *A);
void imprimePotencia(Conjunto *A);
Conjunto *potenciaConjunto(Conjunto *A);
int subconjunto(Conjunto *A, Conjunto *B);
int iguales(Conjunto *A, Conjunto *B);
