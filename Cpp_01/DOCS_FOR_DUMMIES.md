DOCUMENTACIÓN PARA TONTOS - Cpp_01
================================

Resumen
-------
Esta carpeta contiene dos ejercicios (ex00 y ex01) relacionados con la clase `Zombie`.
El objetivo es entender objetos en pila vs heap, construcción y destrucción, y la gestión
de arrays dinámicos de objetos.

Archivos relevantes
- [ex00](ex00): `Zombie.hpp`, `Zombie.cpp`, `newZombie.cpp`, `randomChump.cpp`, `main.cpp`, `Makefile`
- [ex01](ex01): `Zombie.hpp`, `Zombie.cpp`, `zombieHorde.cpp`, `main.cpp`, `Makefile`

Instrucciones rápidas para compilar y ejecutar
- Compilar `ex00`: desde `Cpp_01/ex00` ejecutar `make`.
- Ejecutar `ex00`: `./ex00` (según Makefile genera ejecutable así).
- Compilar `ex01`: desde `Cpp_01/ex01` ejecutar `make`.
- Ejecutar `ex01`: `./ex01`.

Explicación general (conceptos clave)
- Pila (stack): objetos creados dentro de una función sin `new` viven en la pila y
  se destruyen automáticamente al salir del alcance.
- Montículo (heap): objetos creados con `new` permanecen hasta que `delete` (o `delete[]`) se llame.
- Constructor: función que crea/inicializa un objeto.
- Destructor: función que limpia o reporta cuando un objeto se destruye.

ex00 - descripción y funciones
------------------------------
Objetivo: mostrar la diferencia entre crear un `Zombie` en el heap y en la pila.

Ficheros principales
- `Zombie.hpp` / `Zombie.cpp`:
  - Clase `Zombie` con:
    - `Zombie(std::string name)` : constructor que guarda el nombre.
    - `~Zombie()` : destructor que imprime que el `Zombie` fue destruido.
    - `void announce(void) const` : imprime el mensaje del zombie: `"<name>: BraiiiiiiinnnzzzZ..."`.
  - `private: std::string name` : almacena el nombre del zombie.

- `newZombie.cpp`:
  - `Zombie* newZombie(std::string name)` : crea un `Zombie` con `new` en el heap y devuelve
    el puntero. El llamador es responsable de llamar `delete` cuando ya no lo necesite.

- `randomChump.cpp`:
  - `void randomChump(std::string name)` : crea un `Zombie` local (en la pila), llama `announce()`
    y cuando la función termina, el destructor del `Zombie` se ejecuta automáticamente.

- `main.cpp` (ejemplo de uso):
  - Crea un `Zombie` en heap con `newZombie("HeapZombie")`, llama `announce()`, luego `delete`.
  - Llama `randomChump("StackZombie")` que muestra un zombie en la pila.

Qué aprenderás con ex00
- La diferencia entre `new`/`delete` (heap) y objetos automáticos (stack).
- Cómo implementar un constructor, destructor y un método sencillo en C++.

ex01 - descripción y funciones
------------------------------
Objetivo: crear una 'horda' (array) de `Zombie` en memoria dinámica y asignarles nombres.

Ficheros principales
- `Zombie.hpp` / `Zombie.cpp`:
  - Versión extendida de la clase `Zombie` con métodos adicionales:
    - `Zombie()` : constructor por defecto (nombre vacío).
    - `Zombie(std::string name)` : constructor con nombre.
    - `~Zombie()` : destructor imprime que el zombie fue destruido.
    - `void announce(void) const` : igual que en ex00.
    - `void setName(std::string const &name)` : establece/actualiza el nombre del zombie.
    - `std::string const &getName() const` : devuelve referencia al nombre.

- `zombieHorde.cpp`:
  - `Zombie* zombieHorde(int N, std::string name)` :
    - Si `N <= 0` devuelve `NULL` (o `nullptr` conceptualmente).
    - Crea un array dinámico `new Zombie[N]` (N objetos por defecto) en el heap.
    - Recorre el array y llama `setName(name)` para darle a cada `Zombie` el mismo nombre base.
    - Devuelve el puntero al primer elemento del array.
    - El llamador debe usar `delete []` para liberar correctamente la horda.

- `main.cpp` (ejemplo de uso):
  - Pide `N = 5`, crea la `horde` con `zombieHorde(N, "HordeZombie")`, llama `announce()` en cada
    elemento y finalmente `delete [] horde`.

Qué aprenderás con ex01
- Crear arrays dinámicos de objetos (`new Type[N]`) y liberarlos con `delete []`.
- Uso de setters/getters para manejar datos privados dentro de una clase.

Notas sobre seguridad y "forbidden"
- Revisé los archivos de `ex00` y `ex01`. No se usan funciones peligrosas como `system()`, `exec*`,
  ni operaciones de escritura fuera de los límites del array.
- El código usa `new` y `delete` correctamente: cada `new` en `ex00` tiene su `delete` en `main`,
  y en `ex01` el array se libera con `delete []`.

Sugerencias y pasos siguientes
- Si quieres que ejecute la compilación aquí, dime y la ejecuto (`make` en cada subcarpeta).
- Puedo mejorar la documentación agregando ejemplos de salida esperada.

Fin de la documentación básica.

ex02 - descripción y funciones
------------------------------
Objetivo: entender punteros y referencias a std::string.

Ficheros principales
- `main.cpp`:
  - Crea `std::string str = "HI THIS IS BRAIN"`.
  - `std::string *stringPTR = &str;` — puntero a la cadena.
  - `std::string &stringREF = str;` — referencia a la cadena.
  - Imprime las direcciones (`&str`, `stringPTR`, `&stringREF`) y luego los valores
    (`str`, `*stringPTR`, `stringREF`).

ex03 - descripción y funciones
------------------------------
Objetivo: practicar referencias y punteros en miembros de clase.

Ficheros principales
- `Weapon.hpp/cpp`:
  - `Weapon(std::string type)` : constructor.
  - `const std::string &getType() const` : devuelve el tipo por referencia const.
  - `void setType(const std::string &type)` : actualiza el tipo.
- `HumanA`:
  - Toma una `Weapon &` en su constructor y la guarda como referencia.
  - `attack()` imprime `"<name> attacks with their <weapon type>"`.
- `HumanB`:
  - Guarda un `Weapon *` (puntero). `setWeapon(Weapon &)` asigna la dirección.
  - `attack()` verifica si el puntero es NULL antes de usarlo.

ex04 - descripción y funciones
------------------------------
Objetivo: reemplazar todas las apariciones de `s1` por `s2` en un archivo sin usar
`std::string::replace` ni funciones C.

Ficheros principales
- `main.cpp`:
  - Lee argumentos `file s1 s2`, abre `file`, lee todo su contenido en una `std::string`.
  - Reemplaza todas las ocurrencias de `s1` por `s2` usando `find` y construyendo
    una nueva cadena con `append` (no se usa `replace`).
  - Escribe el resultado en `<filename>.replace`.

ex05 - descripción y funciones
------------------------------
Objetivo: usar punteros a funciones miembro para despachar mensajes.

Ficheros principales
- `Harl.hpp/cpp`:
  - Métodos privados: `debug`, `info`, `warning`, `error` que imprimen mensajes.
  - `void complain(std::string level)` que usa un array de nombres y un array de
    punteros a miembros para llamar al método correcto sin usar if/else encadenados.

ex06 - descripción y funciones
------------------------------
Objetivo: filtrar mensajes de `Harl` usando `switch` y `fall-through`.

Ficheros principales
- `main.cpp` y `Harl` similar a ex05:
  - Programa `harlFilter` toma un solo argumento: el nivel.
  - Si el nivel pertenece a `DEBUG/INFO/WARNING/ERROR`, muestra los mensajes de
    ese nivel y los niveles superiores (usar `switch` con `case` y fallthrough).
  - Si el nivel no se reconoce, imprime un mensaje alternativo.

Notas finales sobre forbiddens
- Respeté las reglas del subject: no usé `printf`, `alloc`, `free`, ni `using namespace`.
- Para ex04 no se utilizó `std::string::replace`.

