# ADR-001: Implementación de Singleton mediante Meyers Singleton

## Contexto
En el módulo `01-singleton-transaction-manager`, se requiere un único gestor de transacciones (`TransactionManager`) accesible globalmente y seguro para entornos multihilo. Las implementaciones tradicionales en C++ previo a C++11 solían depender de punteros crudos con asignación dinámica (`new`), comprobación de doble bloqueo (Double-Checked Locking Pattern, DCLP) y destructores manuales propensos a fallos de inicialización o fugas de memoria.

## Decisión
Se implementa el patrón **Meyers Singleton** aprovechando la garantía del estándar C++11 (mantenida en C++20) de inicialización segura de variables estáticas locales con duración de almacenamiento estático (Magic Statics). El constructor por defecto se declara privado, y las operaciones de copia y movimiento quedan explícitamente eliminadas (`= delete`).

```cpp
static TransactionManager& getInstance() {
    static TransactionManager instance;
    return instance;
}
```

## Consecuencias
- **Ventajas:**
  - Inicialización *thread-safe* garantizada a nivel de lenguaje sin overhead de bloqueos manuales durante el acceso posterior.
  - Destrucción automática y determinista al finalizar el programa.
  - Imposibilidad sintáctica de duplicación o clonación accidental.
- **Desventajas:**
  - El orden de destrucción de objetos estáticos globales entre distintas unidades de traducción puede ser difícil de controlar (aunque este gestor no depende de otros singletons en su destrucción).
- **Alternativas descartadas:**
  - `new` con DCLP y `std::atomic`: innecesariamente complejo y propenso a errores sutiles de ordenación de memoria.
