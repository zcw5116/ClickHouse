# Funciones para trabajar con agregados anulables {#functions-for-working-with-nullable-aggregates}

## IsNull {#isnull}

Comprueba si el argumento es [NULO](../syntax.md#null).

``` sql
isNull(x)
```

**Parámetros**

-   `x` — Un valor con un tipo de datos no compuesto.

**Valor devuelto**

-   `1` si `x` ser `NULL`.
-   `0` si `x` no es `NULL`.

**Ejemplo**

Tabla de entrada

``` text
┌─x─┬────y─┐
│ 1 │ ᴺᵁᴸᴸ │
│ 2 │    3 │
└───┴──────┘
```

Consulta

``` sql
SELECT x FROM t_null WHERE isNull(y)
```

``` text
┌─x─┐
│ 1 │
└───┘
```

## isNotNull {#isnotnull}

Comprueba si el argumento es [NULO](../syntax.md#null).

``` sql
isNotNull(x)
```

**Parámetros:**

-   `x` — Un valor con un tipo de datos no compuesto.

**Valor devuelto**

-   `0` si `x` ser `NULL`.
-   `1` si `x` no es `NULL`.

**Ejemplo**

Tabla de entrada

``` text
┌─x─┬────y─┐
│ 1 │ ᴺᵁᴸᴸ │
│ 2 │    3 │
└───┴──────┘
```

Consulta

``` sql
SELECT x FROM t_null WHERE isNotNull(y)
```

``` text
┌─x─┐
│ 2 │
└───┘
```

## Coalesce {#coalesce}

Comprueba de izquierda a derecha si `NULL` se aprobaron argumentos y devuelve el primer no-`NULL` argumento.

``` sql
coalesce(x,...)
```

**Parámetros:**

-   Cualquier número de parámetros de un tipo no compuesto. Todos los parámetros deben ser compatibles por tipo de datos.

**Valores devueltos**

-   El primer no-`NULL` argumento.
-   `NULL` si todos los argumentos son `NULL`.

**Ejemplo**

Considere una lista de contactos que pueden especificar varias formas de contactar a un cliente.

``` text
┌─name─────┬─mail─┬─phone─────┬──icq─┐
│ client 1 │ ᴺᵁᴸᴸ │ 123-45-67 │  123 │
│ client 2 │ ᴺᵁᴸᴸ │ ᴺᵁᴸᴸ      │ ᴺᵁᴸᴸ │
└──────────┴──────┴───────────┴──────┘
```

El `mail` y `phone` los campos son de tipo String, pero el `icq` campo `UInt32`, por lo que necesita ser convertido a `String`.

Obtenga el primer método de contacto disponible para el cliente de la lista de contactos:

``` sql
SELECT coalesce(mail, phone, CAST(icq,'Nullable(String)')) FROM aBook
```

``` text
┌─name─────┬─coalesce(mail, phone, CAST(icq, 'Nullable(String)'))─┐
│ client 1 │ 123-45-67                                            │
│ client 2 │ ᴺᵁᴸᴸ                                                 │
└──────────┴──────────────────────────────────────────────────────┘
```

## ifNull {#ifnull}

Devuelve un valor alternativo si el argumento principal es `NULL`.

``` sql
ifNull(x,alt)
```

**Parámetros:**

-   `x` — El valor que se debe comprobar `NULL`.
-   `alt` — El valor que devuelve la función si `x` ser `NULL`.

**Valores devueltos**

-   Valor `x`, si `x` no es `NULL`.
-   Valor `alt`, si `x` ser `NULL`.

**Ejemplo**

``` sql
SELECT ifNull('a', 'b')
```

``` text
┌─ifNull('a', 'b')─┐
│ a                │
└──────────────────┘
```

``` sql
SELECT ifNull(NULL, 'b')
```

``` text
┌─ifNull(NULL, 'b')─┐
│ b                 │
└───────────────────┘
```

## nullIf {#nullif}

Devoluciones `NULL` si los argumentos son iguales.

``` sql
nullIf(x, y)
```

**Parámetros:**

`x`, `y` — Valores de comparación. Deben ser tipos compatibles, o ClickHouse generará una excepción.

**Valores devueltos**

-   `NULL` si los argumentos son iguales.
-   El `x` valor, si los argumentos no son iguales.

**Ejemplo**

``` sql
SELECT nullIf(1, 1)
```

``` text
┌─nullIf(1, 1)─┐
│         ᴺᵁᴸᴸ │
└──────────────┘
```

``` sql
SELECT nullIf(1, 2)
```

``` text
┌─nullIf(1, 2)─┐
│            1 │
└──────────────┘
```

## assumeNotNull {#assumenotnull}

Resultados en un valor de tipo [NULL](../../data_types/nullable.md) para un no- `Nullable` si el valor no es `NULL`.

``` sql
assumeNotNull(x)
```

**Parámetros:**

-   `x` — El valor original.

**Valores devueltos**

-   El valor original del-`Nullable` tipo, si no es `NULL`.
-   El valor predeterminado para el-`Nullable` tipo si el valor original fue `NULL`.

**Ejemplo**

Considere el `t_null` tabla.

``` sql
SHOW CREATE TABLE t_null
```

``` text
┌─statement─────────────────────────────────────────────────────────────────┐
│ CREATE TABLE default.t_null ( x Int8,  y Nullable(Int8)) ENGINE = TinyLog │
└───────────────────────────────────────────────────────────────────────────┘
```

``` text
┌─x─┬────y─┐
│ 1 │ ᴺᵁᴸᴸ │
│ 2 │    3 │
└───┴──────┘
```

Aplicar el `assumeNotNull` función a la `y` columna.

``` sql
SELECT assumeNotNull(y) FROM t_null
```

``` text
┌─assumeNotNull(y)─┐
│                0 │
│                3 │
└──────────────────┘
```

``` sql
SELECT toTypeName(assumeNotNull(y)) FROM t_null
```

``` text
┌─toTypeName(assumeNotNull(y))─┐
│ Int8                         │
│ Int8                         │
└──────────────────────────────┘
```

## Acerca de Nosotros {#tonullable}

Convierte el tipo de argumento a `Nullable`.

``` sql
toNullable(x)
```

**Parámetros:**

-   `x` — El valor de cualquier tipo no compuesto.

**Valor devuelto**

-   El valor de entrada con un `Nullable` tipo.

**Ejemplo**

``` sql
SELECT toTypeName(10)
```

``` text
┌─toTypeName(10)─┐
│ UInt8          │
└────────────────┘
```

``` sql
SELECT toTypeName(toNullable(10))
```

``` text
┌─toTypeName(toNullable(10))─┐
│ Nullable(UInt8)            │
└────────────────────────────┘
```

[Artículo Original](https://clickhouse.tech/docs/es/query_language/functions/functions_for_nulls/) <!--hide-->
