# ADR-002: Mutex global en TransactionManager

## Contexto
El gestor de transacciones debe garantizar que las operaciones concurrentes sobre cuentas bancarias (depósitos, retiros y registro en el historial) se realicen de forma estrictamente atómica, sin condiciones de carrera y preservando un registro cronológico consistente.

## Decisión
Se utiliza un único mutex global (`std::mutex mtx_`) en `TransactionManager` junto con `std::lock_guard<std::mutex>` para serializar todas las operaciones de modificación (`deposit`, `withdraw`) y las lecturas del historial (`history()`). Además, el saldo de cada `Account` se mantiene como `std::atomic<double>` para lecturas libres de carreras mediante `getBalance()`.

## Consecuencias
- **Ventajas:**
  - Garantía absoluta de coherencia atómica sin riesgo de interbloqueos (*deadlocks*).
  - El historial de transacciones se actualiza de forma lineal y consistente con los saldos de las cuentas.
  - Sencillez de razonamiento y verificación bajo ThreadSanitizer.
- **Desventajas:**
  - Menor paralelismo cuando múltiples hilos operan simultáneamente sobre cuentas distintas.
- **Alternativas descartadas:**
  - Mutex por cuenta: requeriría el uso de `std::scoped_lock` para transferencias entre cuentas y un mutex separado para el historial, aumentando la complejidad sin ser estrictamente necesario para la demostración del patrón.
