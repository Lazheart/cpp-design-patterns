# ADR-005: Método virtual asConstant() para evitar dynamic_cast

## Contexto
Durante la construcción y simplificación algebraica de expresiones compuestas (por ejemplo $0 \cdot u \to 0$, $u + 0 \to u$ o $1 \cdot u \to u$), o al inspeccionar el exponente en `Power`, surge la necesidad de consultar si un nodo concreto representa un valor numérico constante. El uso de `dynamic_cast<Constant*>` violaría las mejores prácticas de programación orientada a objetos y acoplaría el cliente con implementaciones concretas.

## Decisión
Se añade en la clase base abstracta `Expression` un método virtual con implementación por defecto:
```cpp
virtual std::optional<double> asConstant() const { return std::nullopt; }
```
La clase `Constant` sobreescribe este método devolviendo `std::optional<double>(value_)`. Además, `Power` recibe estrictamente `std::shared_ptr<Constant>` para el exponente, garantizando la restricción mediante el sistema de tipos en tiempo de compilación.

## Consecuencias
- **Ventajas:**
  - Cero inspección de tipos en tiempo de ejecución (RTTI / `dynamic_cast`).
  - Las funciones helper de construcción inteligente (`add`, `multiply`, etc.) pueden evaluar y simplificar expresiones de manera puramente polimórfica y limpia.
  - El diseño permanece cerrado a modificaciones y abierto a nuevas subclases de `Expression`.
- **Desventajas:**
  - Introduce un método especializado en la interfaz base `Expression`, aunque devuelva `nullopt` de manera natural y segura.
- **Alternativas descartadas:**
  - `dynamic_cast`: costo en tiempo de ejecución, acoplamiento a tipos derivados y violación de principios de diseño limpio.
