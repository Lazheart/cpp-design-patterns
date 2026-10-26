# ADR-006: neighbors() devuelve std::span<const int>

## Contexto
En el módulo `04-iterator-graph`, los iteradores (`BFSIterator`, `DFSIterator`) necesitan consultar la lista de nodos adyacentes de un nodo dado. Exponer directamente la estructura interna de `Graph` (por ejemplo `std::vector<int>&` o la tabla `unordered_map`) rompería el encapsulamiento y permitiría mutaciones accidentales. Devolver una copia (`std::vector<int>`) incurriría en asignaciones dinámicas y sobrecoste de memoria en cada paso del recorrido.

## Decisión
Se implementa `neighbors(int id) const` retornando una vista no propietaria de solo lectura mediante `std::span<const int>` (C++20).

```cpp
std::span<const int> neighbors(int id) const;
```

## Consecuencias
- **Ventajas:**
  - Encapsulamiento estricto: el consumidor no puede modificar la lista interna ni el contenedor subyacente.
  - Cero copias y cero asignaciones de memoria en el heap ($O(1)$ en tiempo y memoria).
  - Interfaz moderna e idiomática de C++20 que se integra con bucles `for` basados en rango y algoritmos estándar.
- **Desventajas:**
  - Si el grafo se muta estructuralmente durante la iteración, los iteradores o spans existentes pueden quedar invalidados (comportamiento documentado explícitamente en la API).
- **Alternativas descartadas:**
  - Retornar `const std::vector<int>&`: acopla la interfaz a la elección específica de `vector` en lugar de una vista genérica continua.
  - Retornar `std::vector<int>` por valor: sobrecoste significativo por clonación de datos.
