# Cpp_02 — Guía y plantilla base

Este documento resume el enunciado oficial de `02.en.subject.pdf` y la hoja de evaluación, y proporciona una plantilla base para comenzar los ejercicios `ex00`..`ex03`.

Estructura propuesta (ya creada):

- `ex00/` — `include/`, `src/`, `Makefile`
- `ex01/` — `include/`, `src/`, `Makefile`
- `ex02/` — `include/`, `src/`, `Makefile`
- `ex03/` — `include/`, `src/`, `Makefile`

Reglas importantes (resumen)
- Compilar con `c++` y flags `-Wall -Wextra -Werror -std=c++98`.
- No implementar funciones en headers (salvo templates).
- No usar `using namespace`, `friend`, funciones C prohibidas (`printf`, `alloc`, `free`), ni librerías externas.
- Clases en forma canónica ortodoxa: default ctor, copy ctor, copy assignment, destructor.

Resumen por ejercicio y funciones esperadas

1) ex00 — Fixed (punto fijo básico)

- Archivos: `Fixed.hpp`, `Fixed.cpp`, `main.cpp`, `Makefile`
- Qué pide: una clase `Fixed` en forma canónica que almacena un entero crudo y tiene un `static const int` con el número de bits fraccionarios igual a `8`.
- Funciones públicas esperadas:
  - `Fixed()` — constructor por defecto (inicializa a 0).
  - `Fixed(Fixed const &)` — constructor de copia.
  - `Fixed &operator=(Fixed const &)` — operador de asignación.
  - `~Fixed()` — destructor.
  - `int getRawBits(void) const` — devuelve el valor interno crudo.
  - `void setRawBits(int const raw)` — establece el valor interno crudo.

- Cómo llevarlo a cabo:
  - Declara los miembros privados en `Fixed.hpp` y las funciones en `Fixed.cpp`.
  - `getRawBits` y `setRawBits` sólo acceden/actualizan el entero privado.
  - `main.cpp` debe contener un ejemplo mínimo similar al del sujeto, para demostrar llamadas y mensajes de constructor/destructor.

2) ex01 — Fixed útil (constructores int/float, conversión)

- Archivos: `Fixed.hpp`, `Fixed.cpp`, `main.cpp`, `Makefile`
- Qué pide: ampliar `Fixed` para permitir construir a partir de `int` y `float`, y añadir conversiones.
- Funciones añadidas esperadas:
  - `Fixed(int const n)` — constructor desde `int`.
  - `Fixed(float const f)` — constructor desde `float`.
  - `int toInt(void) const` — convierte el valor fijo a `int`.
  - `float toFloat(void) const` — convierte el valor fijo a `float`.
  - `std::ostream &operator<<(std::ostream &os, Fixed const &f)` — operador de salida que muestra el valor en `float`.

- Cómo llevarlo a cabo:
  - Implementa los constructores para convertir `int`/`float` al valor interno según `fractional bits`.
  - `toInt` y `toFloat` hacen la conversión inversa.
  - `operator<<` es una función no-miembro (no usar `friend`) que usa `toFloat()` para formatear la salida.

3) ex02 — Operadores y utilidades (comparación, aritmética, min/max, ++/--)

- Archivos: `Fixed.hpp`, `Fixed.cpp`, `main.cpp`, `Makefile`
- Qué pide: añadir sobrecarga de operadores a `Fixed`:
  - Operadores de comparación: `>`, `<`, `>=`, `<=`, `==`, `!=`.
  - Operadores aritméticos: `+`, `-`, `*`, `/`.
  - Operadores de incremento y decremento: pre/post `++` y `--`.
  - Funciones miembro estáticas: `min(Fixed &, Fixed &)` y `max(Fixed &, Fixed &)` (también versiones `const`).

- Cómo llevarlo a cabo:
  - Implementa los operadores como miembros o funciones no-miembro cuando corresponda.
  - Para `*` y `/` presta atención a la conversión de la parte fraccionaria para evitar pérdidas de precisión.
  - `min` y `max` devuelven la referencia al menor/mayor argumento.

4) ex03 — BSP (Point y función `bsp`)

- Archivos: `Point.hpp`, `Point.cpp`, `bsp.hpp`, `bsp.cpp`, `main.cpp`, `Makefile`
- Qué pide: una clase `Point` que contiene dos atributos `Fixed const x` y `Fixed const y`.
  - Constructor: `Point(float x, float y)` que inicializa `x` e `y`.
  - La función `bool bsp(Point const a, Point const b, Point const c, Point const point)` devuelve `true` si `point` está dentro del triángulo `abc`.

- Cómo llevarlo a cabo:
  - `Point` almacena coordenadas usando la clase `Fixed` del ejercicio anterior.
  - Implementa `bsp` usando áreas (barycentric) o comprobando signos de vectores cruzados — asegurándote de manejar puntos en los bordes como se indique por el enunciado.

Archivos añadidos en la plantilla
- He creado skeletons (headers con declaraciones, fuentes con implementaciones mínimas y `main` de ejemplo) para `ex00`..`ex03`.
- Cada `Makefile` compila con `-Wall -Wextra -Werror -std=c++98 -Iinclude`.

Siguientes pasos que puedo hacer por ti
- Implementar completamente uno de los ejercicios (por ejemplo `ex00` o `ex02`).
- Adaptar el README para añadir ejemplos concretos de uso y pruebas.
- Añadir scripts de prueba simples o instrucciones para `valgrind`.

Si quieres, empiezo implementando `ex00` completamente. Dime si prefieres que lo haga entero o que continúe creando `ex04`..`ex06` en la misma plantilla.
