# Práctica 1 — Calculadora de conjuntos (Yacc)

Especificación de Yacc para evaluar expresiones con conjuntos.

## Compilar

```bash
make
./conj
```

## Ejemplos

```text
{1,2,3}+{3,4}
{1 al 20}*{1 al 30}
{1 al 20}=={1 al 30}
{1 al 5}<={1 al 20}
```

Símbolos: `+` unión, `*` intersección, `-` diferencia, `~` complemento, `#` potencia, `==` iguales, `<=` subconjunto.

Detalle del enunciado y de los archivos: ver el [README de la raíz](../README.md).
