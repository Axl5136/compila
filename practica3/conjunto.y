%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <setjmp.h>
#include "hoc.h"

void yyerror(char *s);
int yylex(void);
int yyparse(void);
void warning(char *s, char *t);
%}

%union {
    int num;
    Conjunto *conj;
    Symbol *sym;
}

%token <num> NUMBER
%token <sym> VAR BLTIN INDEF
%token AL EQ SUBSET
%type <conj> exp conjunto lista asgn
%type <num> cmp

%right '='
%nonassoc EQ SUBSET
%left '+' '-'
%left '*'
%right '~' '#'
%%
list:
        | list '\n'
        | list asgn '\n'
        | list exp '\n'   { printf("= "); imprimeConjunto($2); }
        | list cmp '\n'   {
                if ($2)
                    printf("= si\n");
                else
                    printf("= no\n");
            }
        | list error '\n' { yyerrok; }
        ;

asgn:     VAR '=' exp     {
                $$ = $1->u.val = $3;
                $1->type = VAR;
            }
        ;

exp:      conjunto            { $$ = $1; }
        | VAR                 {
                if ($1->type == INDEF)
                    execerror("variable no definida", $1->name);
                $$ = $1->u.val;
            }
        | BLTIN '(' exp ')'   { $$ = ($1->u.ptr)($3); }
        | exp '+' exp         { $$ = unirConjunto($1, $3); }
        | exp '*' exp         { $$ = intersecConjunto($1, $3); }
        | exp '-' exp         { $$ = diferenConjunto($1, $3); }
        | '~' exp             { $$ = complementoConjunto($2); }
        | '#' exp             { imprimePotencia($2); $$ = $2; }
        | '(' exp ')'         { $$ = $2; }
        ;

cmp:      exp EQ exp          { $$ = iguales($1, $3); }
        | exp SUBSET exp      { $$ = subconjunto($1, $3); }
        ;

conjunto: '{' '}'             { $$ = creaConjunto(8); }
        | '{' lista '}'       { $$ = $2; }
        ;

lista:    NUMBER              { $$ = creaConjunto(32); insertar($$, $1); }
        | NUMBER AL NUMBER    { $$ = creaConjunto(32); insertarRango($$, $1, $3); }
        | lista ',' NUMBER    { $$ = insertar($1, $3); }
        ;
%%

jmp_buf begin;
char *progname;
int lineno = 1;

int main(int argc, char *argv[]) {
    progname = argv[0];
    init();
    printf("Calculadora de conjuntos (practica 3)\n");
    printf("  + union   * interseccion   - diferencia\n");
    printf("  ~ complemento   # conjunto potencia\n");
    printf("  == iguales   <= subconjunto\n");
    printf("  nombre = {1, 2, 3}   guarda un conjunto\n");
    printf("  potencia(A)          builtin\n");
    printf("  {1 al 20}            rango\n\n");
    setjmp(begin);
    yyparse();
    return 0;
}

void execerror(char *s, char *t) {
    warning(s, t);
    longjmp(begin, 0);
}

int yylex(void) {
    int c;
    int d;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == EOF)
        return 0;

    if (isdigit(c)) {
        ungetc(c, stdin);
        scanf("%d", &yylval.num);
        return NUMBER;
    }

    /* == iguales, un solo = es asignacion */
    if (c == '=') {
        d = getchar();
        if (d == '=')
            return EQ;
        if (d != EOF)
            ungetc(d, stdin);
        return '=';
    }

    /* <= subconjunto */
    if (c == '<') {
        d = getchar();
        if (d == '=')
            return SUBSET;
        if (d != EOF)
            ungetc(d, stdin);
        return c;
    }

    /* "al" es palabra del rango; lo demas es variable o builtin */
    if (isalpha(c)) {
        Symbol *s;
        char sbuf[100];
        char *p = sbuf;

        do {
            if (p < sbuf + 99)
                *p++ = c;
        } while ((c = getchar()) != EOF && isalnum(c));
        if (c != EOF)
            ungetc(c, stdin);
        *p = '\0';
        if (strcmp(sbuf, "al") == 0)
            return AL;
        if ((s = lookup(sbuf)) == (Symbol *)0)
            s = install(sbuf, INDEF, 0);
        yylval.sym = s;
        if (s->type == INDEF)
            return VAR;
        return s->type;
    }

    if (c == '\n')
        lineno++;

    return c;
}

void yyerror(char *s) {
    warning(s, (char *)0);
}

void warning(char *s, char *t) {
    fprintf(stderr, "%s: %s", progname, s);
    if (t)
        fprintf(stderr, " %s", t);
    fprintf(stderr, " cerca de la linea %d\n", lineno);
}
