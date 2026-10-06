#include "conjunto.h"

Conjunto *creaConjunto(int tama) {
    Conjunto *conj = (Conjunto *)malloc(sizeof(Conjunto));
    if (tama < 8)
        tama = 8;
    conj->tama = tama;
    conj->cardinal = 0;
    conj->eltos = (tTipo *)malloc(sizeof(tTipo) * tama);
    return conj;
}

Conjunto *copiaConjunto(Conjunto *conj) {
    int i;
    Conjunto *copy = creaConjunto(conj->cardinal);
    for (i = 0; i < conj->cardinal; i++)
        copy->eltos[i] = conj->eltos[i];
    copy->cardinal = conj->cardinal;
    return copy;
}

void imprimeConjunto(Conjunto *conj) {
    int i;
    printf("{");
    for (i = 0; i < conj->cardinal; i++) {
        if (i)
            printf(",");
        printf("%d", conj->eltos[i]);
    }
    printf("}\n");
}

int pertenece(Conjunto *A, tTipo x) {
    int i;
    for (i = 0; i < A->cardinal; i++)
        if (A->eltos[i] == x)
            return 1;
    return 0;
}

Conjunto *insertar(Conjunto *A, tTipo x) {
    if (pertenece(A, x))
        return A;
    if (A->cardinal >= A->tama) {
        A->tama = A->tama * 2;
        A->eltos = (tTipo *)realloc(A->eltos, sizeof(tTipo) * A->tama);
    }
    A->eltos[A->cardinal] = x;
    A->cardinal = A->cardinal + 1;
    return A;
}

/* Mete todos los enteros desde a hasta b, por ejemplo 1 al 20 */
Conjunto *insertarRango(Conjunto *A, int a, int b) {
    int x;
    int ini = a;
    int fin = b;
    if (ini > fin) {
        ini = b;
        fin = a;
    }
    for (x = ini; x <= fin; x++)
        insertar(A, x);
    return A;
}

Conjunto *unirConjunto(Conjunto *A, Conjunto *B) {
    int i;
    Conjunto *nvo = creaConjunto(A->cardinal + B->cardinal);
    for (i = 0; i < A->cardinal; i++)
        insertar(nvo, A->eltos[i]);
    for (i = 0; i < B->cardinal; i++)
        insertar(nvo, B->eltos[i]);
    return nvo;
}

Conjunto *intersecConjunto(Conjunto *A, Conjunto *B) {
    int i;
    Conjunto *nvo = creaConjunto(A->cardinal);
    for (i = 0; i < A->cardinal; i++)
        if (pertenece(B, A->eltos[i]))
            insertar(nvo, A->eltos[i]);
    return nvo;
}

Conjunto *diferenConjunto(Conjunto *A, Conjunto *B) {
    int i;
    Conjunto *nvo = creaConjunto(A->cardinal);
    for (i = 0; i < A->cardinal; i++)
        if (!pertenece(B, A->eltos[i]))
            insertar(nvo, A->eltos[i]);
    return nvo;
}

/* Universo fijo 0..9 para que el complemento sea f�cil de explicar */
Conjunto *complementoConjunto(Conjunto *A) {
    int x;
    Conjunto *nvo = creaConjunto(UMAX - UMIN + 1);
    for (x = UMIN; x <= UMAX; x++)
        if (!pertenece(A, x))
            insertar(nvo, x);
    return nvo;
}

/* Para cada elemento: o lo pongo en el subconjunto, o no.
   Al terminar de decidir, imprimo ese subconjunto. */
static void recPot(Conjunto *A, int i, int *temp, int k) {
    int j;
    if (i == A->cardinal) {
        printf("{");
        for (j = 0; j < k; j++) {
            if (j)
                printf(",");
            printf("%d", temp[j]);
        }
        printf("} ");
        return;
    }
    recPot(A, i + 1, temp, k);
    temp[k] = A->eltos[i];
    recPot(A, i + 1, temp, k + 1);
}

void imprimePotencia(Conjunto *A) {
    int temp[512];
    printf("P = { ");
    recPot(A, 0, temp, 0);
    printf("}\n");
}

/* 1 si todos los de A estan en B (A subconjunto de B) */
int subconjunto(Conjunto *A, Conjunto *B) {
    int i;
    for (i = 0; i < A->cardinal; i++)
        if (!pertenece(B, A->eltos[i]))
            return 0;
    return 1;
}

int iguales(Conjunto *A, Conjunto *B) {
    if (A->cardinal != B->cardinal)
        return 0;
    return subconjunto(A, B);
}
