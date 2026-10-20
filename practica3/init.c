#include "hoc.h"
#include "y.tab.h"

static struct {
    char *name;
    Conjunto *(*func)(Conjunto *);
} builtins[] = {
    "potencia", potenciaConjunto,
    0, 0
};

void init(void) {
    int i;
    Symbol *s;
    for (i = 0; builtins[i].name; i++) {
        s = install(builtins[i].name, BLTIN, 0);
        s->u.ptr = builtins[i].func;
    }
}
