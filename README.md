# Compiladores — prácticas

Repositorio de respaldo de las prácticas de **Compiladores** (ESCOM).

Cada práctica vive en su propia carpeta (`practica1`, más adelante `practica2`, etc.) para no mezclar código ni romper lo que ya funciona.

## Práctica 1 — Yacc básico: calculadora de conjuntos

Carpeta: [`practica1/`](practica1/)

Calculadora de conjuntos con **Yacc/Bison**. Lees expresiones, las reconoces con una gramática y las evalúas.

Operaciones:

- unión `+`
- intersección `*`
- diferencia `-`
- complemento `~` (universo 0..9)
- conjunto potencia `#`
- igualdad `==`
- subconjunto `<=`
- rangos `{1 al 20}`

Los conjuntos de la demo se escriben así (A, B y C son solo nombres para hablar; no hay variables todavía):

```text
{1 al 20}+{1 al 30}
{1 al 20}*{1 al 30}
{1 al 20}=={1 al 30}
{1 al 5}<={1 al 20}
{1 al 5}<={1 al 30}
```

### Cómo compilar y correr

```bash
cd practica1
make
./conj
```

En Mac, si `yacc` pide Xcode, el `Makefile` usa `bison -y -d`.

Salir: `Ctrl+D` o `Ctrl+C`.

### Archivos (qué es de uno y qué no)

| Archivo | Qué es |
|---|---|
| `conjunto.y` | Especificación de Yacc: declaraciones (`%union`, tokens), gramática y `yylex` / `main` |
| `conjunto.c` / `conjunto.h` | Operaciones sobre conjuntos (arreglo + ciclos) |
| `Makefile` | Receta: Bison ? gcc |
| `y.tab.c` / `y.tab.h` | Los **genera** Bison; no se editan (no van al repo) |

La pila de Yacc se define en `%union` de `conjunto.y`.

### Relación con HOC1

El enunciado pide primero compilar **hoc1** (calculadora de `double`). Está en el material local `planb/lenguajeC/hoc1/`. Esta práctica usa la misma idea (`.y` ? Yacc ? C), pero los valores de la pila son conjuntos, no `double`.
