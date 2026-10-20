#include <stdlib.h>
#include <string.h>
#include "hoc.h"
#include "y.tab.h"

static Symbol *symlist = 0; /* tabla de simbolos: lista ligada */

Symbol *lookup(char *s) {
    Symbol *sp;
    for (sp = symlist; sp != (Symbol *)0; sp = sp->next)
        if (strcmp(sp->name, s) == 0)
            return sp;
    return 0;
}

Symbol *install(char *s, int t, Conjunto *d) {
    Symbol *sp;
    sp = (Symbol *)malloc(sizeof(Symbol));
    sp->name = (char *)malloc(strlen(s) + 1);
    strcpy(sp->name, s);
    sp->type = t;
    sp->u.val = d;
    sp->next = symlist; /* poner al frente de la lista */
    symlist = sp;
    return sp;
}
