**Introducción a Cpp03 (explicación para principiantes)**

Este repositorio contiene implementaciones de los ejercicios ex00, ex01 y ex02 del módulo C++03. Cada ejercicio está en su propia carpeta (`ex00`, `ex01`, `ex02`) y sigue la estructura:

- `include/`: archivos `.hpp` (cabeceras)
- `src/`: archivos `.cpp` (implementación) y `main.cpp`
- `Makefile`: reglas para compilar con `-std=c++98 -Wall -Wextra -Werror`

Cómo compilar y ejecutar

1. Entra en la carpeta del ejercicio, por ejemplo:

   cd Cpp_03/ex00
   make
   ./ex00

2. Para limpiar los binarios: `make fclean`

Descripción general de las clases

1) `ClapTrap` (ex00)
- Propósito: representar un pequeño robot que puede atacar, recibir daño y repararse.
- Atributos (privados): `name`, `hitPoints` (vida), `energyPoints` (energía) y `attackDamage` (daño por ataque).
- Métodos principales:
  - `attack(target)`: consume energía y muestra un mensaje indicando que ataca al objetivo.
  - `takeDamage(amount)`: reduce los puntos de vida según el daño recibido.
  - `beRepaired(amount)`: consume energía y aumenta los puntos de vida.

Concepto clave para principiantes: la encapsulación
- Los atributos están privados (ex00), lo que significa que solo las funciones de la propia clase pueden accederlos directamente. Esto ayuda a proteger el estado interno del objeto.

2) `ScavTrap` (ex01)
- Propósito: una versión especializada de `ClapTrap` con más vida y energía, y una habilidad especial.
- Herencia: `ScavTrap` hereda de `ClapTrap` (public). En esta carpeta la clase base usa atributos `protected` para que las clases derivadas puedan accederlos directamente.
- Cambios importantes frente a `ClapTrap`:
  - Valores iniciales mayores (`hitPoints = 100`, `energyPoints = 50`, `attackDamage = 20`).
  - `attack()` sobrescrito para mostrar un mensaje diferente.
  - `guardGate()`: función especial que imprime que el `ScavTrap` ha entrado en modo guardián.

Concepto clave para principiantes: herencia
- La herencia permite crear una clase nueva (hija) basada en una clase existente (padre). La hija reutiliza código del padre y puede añadir o modificar comportamientos.

3) `FragTrap` (ex02)
- Propósito: otra versión especializada de `ClapTrap` centrada en la interacción amistosa.
- Valores iniciales típicos: `hitPoints = 100`, `energyPoints = 100`, `attackDamage = 30`.
- Función especial: `highFivesGuys()` que pide un "high five" (saludo) e imprime un mensaje.

Conceptos clave usados en el código
- Constructores y destructores: cada clase imprime mensajes al construirse y destruirese para que puedas ver el orden de creación y destrucción de los objetos.
- Copia y asignación: se definen el constructor copia y el operador de asignación para manejar copias de objetos de forma segura.
- Reglas del proyecto: el código está escrito para compilar con el estándar `C++98` y evita características modernas de C++ (C++11+).

Buenas prácticas explicadas
- Separar la interfaz (`.hpp`) de la implementación (`.cpp`) mejora la organización y facilita la lectura.
- Usar `-Wall -Wextra -Werror` ayuda a detectar avisos y errores que podrían provocar comportamientos inesperados.

Siguientes pasos sugeridos para aprender
- Modifica los valores iniciales y observa cómo cambian los comportamientos.
- Añade getters y setters para practicar control de acceso en las clases.
- Crea nuevos métodos que combinen acciones (por ejemplo, un método `battle` que haga varias acciones seguidas).

Si quieres, puedo:
- Ejecutar `make` en cada ejercicio y mostrar la salida.
- Ajustar los mensajes para que coincidan exactamente con otro enunciado.

Fin del documento
