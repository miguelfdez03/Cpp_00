# 🗺️ Fase 1 — Roadmap y Arquitectura Conceptual
## C++ Module 05: Repetition and Exceptions

> **Regla de oro de esta guía:** Todo lo aquí escrito se sustenta únicamente en el subject PDF (v11.1) y la hoja de evaluación oficial de 42evalhub. Si algo no está en esas dos fuentes, no está aquí.

---

## 🧩 Visión General: ¿Qué construyes y por qué?

El módulo te obliga a construir una burocracia en miniatura. No es un tema aleatorio: **la burocracia es el modelo perfecto para enseñar excepciones** porque:

- Las reglas son rígidas (grados fuera de rango → error).
- Los errores son esperables y deben gestionarse sin que el programa muera.
- Las entidades tienen jerarquías (formularios base → formularios concretos).

La progresión de los 4 ejercicios es deliberada: **cada uno añade exactamente una capa de complejidad nueva** encima de la anterior, y siempre reutilizas el código previo.

```
ex00  →  ex01  →  ex02  →  ex03
 │         │        │         │
Bureaucrat Form   AForm    Intern
(lanzar)  (firmar)(ejecutar)(crear)
```

---

## 📦 Ex00 — El Bureaucrat: aprender a lanzar

### ¿Qué problema de C++ resuelve?
Lanzar excepciones **personalizadas** que son atrapables como `std::exception`.
Antes de este módulo probablemente usabas códigos de error o `exit()`. Aquí aprendes que hay una alternativa limpia: la jerarquía de `std::exception`.

### Analogía
Un burócrata es un empleado con **rango** (1 = director, 150 = becario recién llegado).
Si intentas contratar a alguien con un rango de `0` o `151`, la oficina de RRHH **tira el formulario a la papelera** (lanza excepción) antes de que esa persona ponga un pie en la oficina.

### Arquitectura interna de `Bureaucrat`

```
Bureaucrat
├── _name  : const std::string   ← jamás cambia
├── _grade : int                 ← rango entre [1, 150]
│
├── [constructor]                ← lanza si _grade < 1 o > 150
├── getName()                    ← getter
├── getGrade()                   ← getter
├── incrementGrade()             ← _grade-- (acerca a 1); lanza si < 1
├── decrementGrade()             ← _grade++ (aleja de 1); lanza si > 150
├── operator<<                   ← "<name>, bureaucrat grade <grade>."
│
└── [excepciones anidadas]
    ├── GradeTooHighException : public std::exception
    └── GradeTooLowException  : public std::exception
```

### ⚠️ La trampa del "incremento"
El subject lo dice sin ambigüedad:
> *"Remember, since grade 1 is the highest and 150 the lowest, incrementing a grade 3 should result in a grade 2 for the bureaucrat."*

`incrementGrade()` hace `_grade--`. `decrementGrade()` hace `_grade++`.
Si los inviertes, **todos los tests del evaluador fallarán en cadena**.

### Flujo de ejecución esperado en `main`

```
1. Crear Bureaucrat válido           → sin excepción
2. Crear Bureaucrat con grade 0      → capturar GradeTooHighException
3. Crear Bureaucrat con grade 151    → capturar GradeTooLowException
4. Incrementar desde grade 1         → capturar GradeTooHighException
5. Decrementar desde grade 150       → capturar GradeTooLowException
6. Imprimir con operator<<           → "<name>, bureaucrat grade <grade>."
```

### Checks exactos del evaluador (42evalhub)
| ✓/✗ | Check |
|---|---|
| ☐ | Makefile compila con `-Wall -Wextra -Werror` |
| ☐ | `_name` es constante |
| ☐ | Grado en rango [1, 150] |
| ☐ | Excepción al construir con grado inválido |
| ☐ | Accessors `getName()` y `getGrade()` |
| ☐ | `incrementGrade()` y `decrementGrade()` existen |
| ☐ | Ambas funciones lanzan excepciones en los límites |
| ☐ | Excepciones heredan de `std::exception` (catchables con `std::exception& e`) |
| ☐ | `operator<<` muestra la info del Bureaucrat |
| ☐ | `main` con tests suficientes |
| ☐ | Orthodox Canonical Form completa |

---

## 📦 Ex01 — El Form: aprender a delegar excepciones

### ¿Qué problema de C++ resuelve?
La **interacción entre objetos a través de excepciones**. Un objeto (`Form`) lanza, otro objeto (`Bureaucrat`) atrapa y reporta. Es el patrón fundamental de la gestión de errores en sistemas orientados a objetos.

### Analogía
Un formulario burocrático tiene dos requisitos de acceso:
- Grado mínimo para **firmarlo** (un mando medio puede firmarlo).
- Grado mínimo para **ejecutarlo** (solo la dirección puede ejecutarlo).

El burócrata intenta firmar: si su rango no llega, el formulario rechaza la firma y el burócrata escribe en el registro "no pude firmarlo porque mi rango es insuficiente".

### Arquitectura interna de `Form`

```
Form
├── _name          : const std::string    ← jamás cambia
├── _isSigned      : bool                 ← false en construcción
├── _gradeToSign   : const int            ← constante [1,150]
├── _gradeToExecute: const int            ← constante [1,150]
│
├── [constructor]                         ← lanza si grados fuera de [1,150]
├── getName(), getIsSigned(),
│   getGradeToSign(), getGradeToExecute() ← getters
├── beSigned(Bureaucrat const&)           ← firma si grade ≤ _gradeToSign;
│                                            lanza GradeTooLowException si no
├── operator<<                            ← muestra ESTADO COMPLETO del form
│
└── [excepciones anidadas]
    ├── GradeTooHighException : public std::exception
    └── GradeTooLowException  : public std::exception
```

### ⚠️ El check más silencioso del evaluador
La hoja de evaluación dice textualmente:
> *"All these attributes are private and **not protected**."*

No es un detalle: es una verificación activa. Si usas `protected`, el evaluador lo ve, lo marca y el ejercicio puede no corregirse. Usa `private` **siempre**.

### Nueva función en `Bureaucrat`: `signForm()`

```
Bureaucrat::signForm(Form& form)
    └── llama a form.beSigned(*this)
         ├── éxito   → imprime: "<bureaucrat> signed <form>"
         └── falla   → captura la excepción
                        imprime: "<bureaucrat> couldn't sign <form> because <reason>"
```

La clave: `signForm()` **nunca lanza**. Atrapa la excepción de `beSigned()` y la convierte en un mensaje de texto. El que lanza es el `Form`, el que reporta es el `Bureaucrat`.

### Flujo de ejecución esperado en `main`

```
1. Crear Form válido                          → sin excepción
2. Crear Form con gradeToSign 0               → capturar GradeTooHighException
3. Crear Form con gradeToExecute 151          → capturar GradeTooLowException
4. Bureaucrat con grade suficiente firma      → "<bur> signed <form>"
5. Bureaucrat con grade insuficiente intenta  → "<bur> couldn't sign <form> because..."
6. Imprimir Form con operator<<               → nombre, signed/not signed, ambos grados
```

### Checks exactos del evaluador (42evalhub)
| ✓/✗ | Check |
|---|---|
| ☐ | Makefile compila con los flags apropiados |
| ☐ | Clase `Form` con los 4 atributos correctos |
| ☐ | Nombre y grados son constantes |
| ☐ | Atributos `private` (NO `protected`) |
| ☐ | Mismas restricciones de grado que `Bureaucrat` |
| ☐ | Accessors para todos los atributos |
| ☐ | `operator<<` muestra el **estado completo** del Form |
| ☐ | `Form::beSigned()` funciona como el subject describe |
| ☐ | `Bureaucrat::signForm()` funciona como el subject describe |
| ☐ | `main` con tests suficientes |
| ☐ | Orthodox Canonical Form completa |

---

## 📦 Ex02 — AForm y formularios concretos: polimorfismo real

### ¿Qué problema de C++ resuelve?
**Herencia, clases abstractas y polimorfismo**. Hasta ahora todos los formularios eran iguales (solo diferían en grados). Ahora necesitas formularios que hagan cosas distintas. La solución correcta en C++ es una clase base abstracta con un método virtual puro.

### Analogía
La clase `AForm` es como el **modelo de formulario en blanco** que existe en la oficina: define la estructura (grados, firma, nombre), pero no tiene contenido específico. No puedes rellenar un modelo en blanco — debes coger una copia concreta (`ShrubberyCreationForm`, etc.) y rellenarla.

### Arquitectura — La jerarquía completa

```
AForm  (abstracta — hereda interfaz de ex01, renombrada)
├── _name          : const std::string  (private, en la base)
├── _isSigned      : bool               (private, en la base)
├── _gradeToSign   : const int          (private, en la base)
├── _gradeToExecute: const int          (private, en la base)
│
├── [métodos concretos heredados de ex01]
├── execute(Bureaucrat const& executor) const = 0  ← PURO
│
├── ShrubberyCreationForm  (sign: 145, exec: 137)
│   └── execute() → crea archivo "<target>_shrubbery" con árboles ASCII
│
├── RobotomyRequestForm    (sign: 72,  exec: 45)
│   └── execute() → ruido de taladro + 50% robotomizado / 50% fallo
│
└── PresidentialPardonForm (sign: 25,  exec: 5)
    └── execute() → "<target> has been pardoned by Zaphod Beeblebrox."
```

### Las dos variantes válidas de `execute()` (el evaluador acepta ambas)

**Variante A — Checks en la base (más elegante, preferida por el subject):**
```
AForm::execute(executor)
    ├── verifica: _isSigned == true          → si no, lanza
    ├── verifica: executor.getGrade() ≤ _gradeToExecute  → si no, lanza
    └── llama a doExecute(executor)          ← método virtual protegido puro

ShrubberyCreationForm::doExecute(executor)
    └── solo hace la acción (crea el archivo)
```

**Variante B — Checks en cada subclase:**
```
ShrubberyCreationForm::execute(executor)
    ├── verifica firma y grado
    └── ejecuta la acción
```

> El subject dice: *"one way is more elegant than the other"* — implica que la Variante A (checks en la base) es la preferida. Pero **ambas son aceptadas** por el evaluador.

### Nueva función en `Bureaucrat`: `executeForm()`

```
Bureaucrat::executeForm(AForm const& form)
    └── llama a form.execute(*this)
         ├── éxito  → "<bureaucrat> executed <form>"
         └── falla  → mensaje de error explícito (captura la excepción)
```

### Grados exactos — No los memorices, tenlos de referencia

| Formulario | gradeToSign | gradeToExecute |
|---|---|---|
| `ShrubberyCreationForm` | 145 | 137 |
| `RobotomyRequestForm` | 72 | 45 |
| `PresidentialPardonForm` | 25 | 5 |

### Flujo de ejecución esperado en `main`

```
1. Crear Bureaucrat grade 1 (máximo poder)
2. Crear ShrubberyCreationForm target "garden"
   → signarlo   (grade 1 ≤ 145 ✓)
   → ejecutarlo  (grade 1 ≤ 137 ✓) → se crea "garden_shrubbery"
3. Intentar ejecutar form sin firmar → excepción
4. Crear Bureaucrat grade 100, intentar ejecutar RobotomyRequestForm (exec: 45) → excepción
5. Crear Bureaucrat grade 50, ejecutar RobotomyRequestForm → 50/50 output
6. Ejecutar PresidentialPardonForm → "X has been pardoned by Zaphod Beeblebrox."
```

### Checks exactos del evaluador (42evalhub)
| ✓/✗ | Check |
|---|---|
| ☐ | Makefile compila con los flags apropiados |
| ☐ | Formularios concretos conformes al subject (grados, nombres, acciones) |
| ☐ | Constructor de cada formulario concreto toma **solo 1 parámetro** (target) |
| ☐ | `AForm::execute(Bureaucrat const&)` existe y funciona |
| ☐ | Checks de firma y grado implementados (en base O en subclases, ambas válidas) |
| ☐ | `Bureaucrat::executeForm(AForm const&)` existe y funciona |
| ☐ | `main` con tests suficientes |
| ☐ | Orthodox Canonical Form completa en todas las clases |

---

## 📦 Ex03 — El Intern: Factory Pattern

### ¿Qué problema de C++ resuelve?
**Creación dinámica de objetos polimórficos sin condicionales anidados** (Factory Pattern). El problema real que resuelve es: *¿cómo seleccionas el tipo de objeto a crear en runtime sin escribir un `if/else if` interminable?* La respuesta es una tabla de dispatch.

### Analogía
El becario (`Intern`) es el empleado que va al archivero y saca el formulario que le piden. No sabe nada de los formularios, solo sabe **buscar en el índice** (`makeForm(nombre, target)`) y darte la copia correcta. Si el formulario no existe en el índice, te lo dice.

### Arquitectura de `Intern`

```
Intern
└── makeForm(std::string name, std::string target) : AForm*
     ├── busca "name" en una tabla de dispatch
     ├── si existe → crea el AForm correspondiente con "target"
     │              imprime "Intern creates <form>"
     │              devuelve el puntero
     └── si no existe → imprime mensaje de error
                         devuelve NULL (o lanza, según tu decisión)
```

### La tabla de dispatch — La única implementación válida

El evaluador tiene un check **separado y explícito** llamado "Good dispatching":
> *"The makeForm() function should use some kind of array of pointers to member functions to handle the creation of Forms. If it's using an unclean method, like if/elseif/elseif/else branchings, or some other ugly stuff like this, please count this as wrong."*

Hay varias formas correctas. La más directa en C++98:

```cpp
// Concepto — no sintaxis final, solo la lógica
struct FormEntry {
    std::string name;
    AForm* (*create)(std::string target);  // puntero a función factory
};

static FormEntry table[] = {
    { "shrubbery creation", &createShrubbery },
    { "robotomy request",   &createRobotomy  },
    { "presidential pardon",&createPardon    },
};

// makeForm recorre el array y llama a table[i].create(target)
```

Esto reemplaza completamente el `if/else if`. El evaluador lo verifica.

### ⚠️ Responsabilidad de memoria
`makeForm()` devuelve un `AForm*` (puntero a heap). Quien llama a `makeForm()` **es responsable de hacer `delete`**. Si en tu `main` no liberas los punteros devueltos, tendrás memory leaks y el evaluador lo detectará con `valgrind`.

### Flujo de ejecución esperado en `main`

```cpp
// Del propio subject — este ejemplo debe funcionar
Intern  someRandomIntern;
AForm*  rrf;
rrf = someRandomIntern.makeForm("robotomy request", "Bender");
// → imprime: "Intern creates RobotomyRequestForm"
delete rrf;  // ← no olvides esto

// Adicionales a testear:
makeForm("shrubbery creation", "home");
makeForm("presidential pardon", "Marvin");
makeForm("formulario inventado", "nadie");  // → error message
```

### Checks exactos del evaluador (42evalhub)
| ✓/✗ | Check |
|---|---|
| ☐ | Makefile compila con los flags apropiados |
| ☐ | Existe clase `Intern` |
| ☐ | `makeForm()` funciona como especifica el subject |
| ☐ | **[Check separado]** `makeForm()` NO usa `if/else if` — usa array de punteros a función |
| ☐ | No hay memory leaks (los `AForm*` se liberan) |
| ☐ | `main` con tests suficientes |
| ☐ | Orthodox Canonical Form completa |

---

## 🔄 Visión Global — Dependencias y orden de construcción

```
                    ┌─────────────────┐
                    │   std::exception │   (STL — ya existe)
                    └────────┬────────┘
                             │ hereda
              ┌──────────────┴──────────────┐
              │                             │
  Bureaucrat::GradeTooHighException   Bureaucrat::GradeTooLowException
  Form/AForm::GradeTooHighException   Form/AForm::GradeTooLowException
              │
              │
┌─────────────▼──────────────┐
│         Bureaucrat          │  ← ex00
│  _name, _grade              │
│  sign/executeForm()         │
└─────────────┬───────────────┘
              │ usa
┌─────────────▼───────────────┐
│      Form → AForm            │  ← ex01 → ex02
│  _name, _isSigned,           │
│  _gradeToSign/Execute        │
│  beSigned(), execute()=0     │
└──────┬────────┬─────────┬───┘
       │        │         │
  Shrubbery  Robotomy  Presidential  ← ex02 (concretos)
       │        │         │
       └────────┴────────┘
                │ crea
         ┌──────▼──────┐
         │    Intern    │  ← ex03
         │  makeForm()  │
         └─────────────┘
```

### Orden de implementación obligatorio
1. **`Bureaucrat`** — base de todo, sin dependencias externas propias.
2. **`Form`** — depende de `Bureaucrat` (recibe un `Bureaucrat const&` en `beSigned()`).
3. **`AForm`** + formularios concretos — extiende `Form` con polimorfismo.
4. **`Intern`** — depende de los 3 formularios concretos para poder crearlos.

Nunca saltes pasos: ex03 depende de que ex02 esté correcto, y ex02 depende de ex01.

---

## ✅ Checklist pre-entrega global

| Ítem | Estado |
|---|---|
| Compila con `c++ -Wall -Wextra -Werror -std=c++98` | ☐ |
| Ninguna función implementada en un `.h`/`.hpp` (salvo templates) | ☐ |
| Orthodox Canonical Form en **todas** las clases no-interfaz | ☐ |
| Sin `using namespace`, sin `friend`, sin C++11 | ☐ |
| Sin funciones C (`printf`, `malloc`, `free`) | ☐ |
| Tests suficientes en cada `main` | ☐ |
| Sin memory leaks (`valgrind --leak-check=full`) | ☐ |
| Atributos de `Form`/`AForm` son `private` (no `protected`) | ☐ |
| `incrementGrade()` acerca al 1 (`_grade--`) | ☐ |
| Grados exactos en formularios concretos | ☐ |
| `Intern::makeForm()` usa tabla de dispatch, sin `if/else if` | ☐ |
| Directorios: `ex00/`, `ex01/`, `ex02/`, `ex03/` | ☐ |
