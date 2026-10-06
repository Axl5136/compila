%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "conjunto.h"

void yyerror(char *s);
int yylex(void);
%}

%union {
    int num;
    Conjunto *conj;
}

%token <num> NUMBER
%token AL EQ SUBSET
%type <conj> exp conjunto lista
%type <num> cmp

%nonassoc EQ SUBSET
%left '+' '-'
%left '*'
%right '~' '#'
%%
list:
        | list '\n'
        | list exp '\n'  { printf("= "); imprimeConjunto($2); }
        | list cmp '\n'  {
                if ($2)
                    printf("= si\n");
                else
                    printf("= no\n");
            }
        ;

cmp:      exp EQ exp          { $$ = iguales($1, $3); }
        | exp SUBSET exp      { $$ = subconjunto($1, $3); }
        ;

exp:      conjunto            { $$ = $1; }
        | exp '+' exp         { $$ = unirConjunto($1, $3); }
        | exp '*' exp         { $$ = intersecConjunto($1, $3); }
        | exp '-' exp         { $$ = diferenConjunto($1, $3); }
        | '~' exp             { $$ = complementoConjunto($2); }
        | '#' exp             { imprimePotencia($2); $$ = $2; }
        | '(' exp ')'         { $$ = $2; }
        ;

conjunto: '{' '}'             { $$ = creaConjunto(8); }
        | '{' lista '}'       { $$ = $2; }
        ;

lista:    NUMBER              { $$ = creaConjunto(32); insertar($$, $1); }
        | NUMBER AL NUMBER    { $$ = creaConjunto(32); insertarRango($$, $1, $3); }
        | lista ',' NUMBER    { $$ = insertar($1, $3); }
        ;
%%

int lineno = 1;

int main(void) {
    printf("Calculadora de conjuntos (practica 1)\n");
    printf("  + union   * interseccion   - diferencia\n");
    printf("  == iguales   <= subconjunto\n");
    printf("  {1 al 20} es el rango 1,2,3,...,20\n");
    printf("Demo: A={1 al 20}  B={1 al 30}  C={1 al 5}\n\n");
    yyparse();
    return 0;
}

int yylex(void) {
    int c;
    int d;
    char pal[16];
    int i;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == EOF)
        return 0;

    if (isdigit(c)) {
        ungetc(c, stdin);
        scanf("%d", &yylval.num);
        return NUMBER;
    }

    /* ==  iguales */
    if (c == '=') {
        d = getchar();
        if (d == '=')
            return EQ;
        ungetc(d, stdin);
        return c;
    }

    /* <=  subconjunto */
    if (c == '<') {
        d = getchar();
        if (d == '=')
            return SUBSET;
        ungetc(d, stdin);
        return c;
    }

    /* palabra "al" para {1 al 20} */
    if (isalpha(c)) {
        i = 0;
        pal[i] = (char)c;
        i++;
        while ((c = getchar()) != EOF && isalpha(c) && i < 15) {
            pal[i] = (char)c;
            i++;
        }
        if (c != EOF)
            ungetc(c, stdin);
        pal[i] = '\0';
        if (strcmp(pal, "al") == 0)
            return AL;
        printf("palabra no valida: %s\n", pal);
        return 0;
    }

    if (c == '\n')
        lineno++;

    return c;
}

void yyerror(char *s) {
    fprintf(stderr, "%s cerca de la linea %d\n", s, lineno);
}
