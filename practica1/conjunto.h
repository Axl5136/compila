#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <stdio.h>
#include <stdlib.h>

typedef int tTipo;

struct conjunto {
    tTipo *eltos;   /* los nùmeros que hay dentro */
    int cardinal;    /* cuùntos elementos hay ahorita */
    int tama;        /* espacio reservado en el arreglo */
};
typedef struct conjunto Conjunto;

/* Universo para el complemento: {0,1,2,...,9} */
#define UMIN 0
#define UMAX 9

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

int subconjunto(Conjunto *A, Conjunto *B);
int iguales(Conjunto *A, Conjunto *B);

#endif
