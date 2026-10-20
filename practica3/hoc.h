#include "conjunto.h"

typedef struct Symbol { /* entrada de la tabla de simbolos */
    char *name;
    short type; /* VAR, BLTIN, INDEF */
    union {
        Conjunto *val;                  /* si es VAR */
        Conjunto *(*ptr)(Conjunto *);   /* si es BLTIN */
    } u;
    struct Symbol *next; /* lista simplemente ligada */
} Symbol;

Symbol *install(char *s, int t, Conjunto *d);
Symbol *lookup(char *s);
void execerror(char *s, char *t);
void init(void);
