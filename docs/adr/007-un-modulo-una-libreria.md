# ADR-007: Un módulo = Una librería estática con demo y tests independientes

## Contexto
El repositorio implementa cuatro patrones de diseño distintos e independientes. Un diseño monolítico acoplaría los tiempos de compilación, las dependencias y las pruebas de los cuatro patrones en una única entidad indivisible.

## Decisión
Se estructura el repositorio como un monorepo modular donde cada patrón reside en su propio subdirectorio (`01-...`, `02-...`, `03-...`, `04-...`), construyendo:
1. Una librería estática (`STATIC`) con cabeceras públicas en `include/` y fuentes privadas en `src/`.
2. Un ejecutable de demostración interactiva en `app/main.cpp`.
3. Una suite de pruebas unitarias y de integración en `tests/`.

## Consecuencias
- **Ventajas:**
  - Desacoplamiento total: cada módulo compila y se prueba de forma independiente.
  - Tiempos de compilación incrementales reducidos.
  - Estructura limpia y reproducible que refleja las mejores prácticas en desarrollo industrial con C++ y CMake.
- **Desventajas:**
  - Ligeramente más archivos `CMakeLists.txt` a mantener (uno por módulo más el raíz).
- **Alternativas descartadas:**
  - Una sola librería general conteniendo todos los patrones: mezclaría responsabilidades y dificultaría aislar problemas o probar un único patrón.
