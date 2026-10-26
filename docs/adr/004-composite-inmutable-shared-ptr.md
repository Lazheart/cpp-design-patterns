# ADR-004: Nodos de expresión inmutables con std::shared_ptr

## Contexto
En el módulo `03-composite-expressions`, un árbol de expresiones simbólicas complejas (como $f(x) = (x^2 + 3x) \cdot \sin(x)$) y el cálculo simbólico de su derivada generan subárboles compartidos (por ejemplo, múltiples referencias al mismo nodo `Variable` $x$ o a constantes reutilizadas). Duplicar nodos aumentaría innecesariamente el consumo de memoria y la complejidad de gestión de punteros.

## Decisión
Se define que todos los nodos derivados de `Expression` son estrictamente inmutables tras su construcción. La propiedad de los subárboles se gestiona mediante punteros inteligentes compartidos `std::shared_ptr<Expression>` (tipificado como `ExprPtr`).

## Consecuencias
- **Ventajas:**
  - El método `derivative()` puede reutilizar subárboles del grafo original sin copiarlos en profundidad.
  - Al ser inmutables, compartir punteros `shared_ptr` entre diferentes expresiones es completamente seguro contra carreras de datos.
  - La liberación de memoria es automática y libre de fugas cuando ya ninguna expresión referencia un subárbol.
- **Desventajas:**
  - Sobrecarga de control de referencias atómico inherente a `std::shared_ptr`.
- **Alternativas descartadas:**
  - Propiedad exclusiva con `std::unique_ptr`: obligaría a clonar nodos recursivamente cada vez que una variable o subexpresión se referenciara en más de un término, haciendo el cálculo de derivadas costoso e ineficiente.
