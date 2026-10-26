# ADR-003: Registro de fábricas con std::unordered_map

## Contexto
En el módulo `02-abstract-factory-render`, la aplicación debe ser capaz de instanciar la fábrica adecuada (`OpenGLFactory`, `VulkanFactory`) a partir de una cadena descriptiva (por ejemplo, leída de configuración o argumentos de CLI) respetando el principio Open/Closed y evitando bifurcaciones condicionales (`if`/`else` o `switch`).

## Decisión
Se implementa un registro de fábricas mediante una tabla asociativa `std::unordered_map<std::string, FactoryMaker>` donde `FactoryMaker` es un `std::function<std::unique_ptr<RenderFactory>()>`.

```cpp
using FactoryMaker = std::function<std::unique_ptr<RenderFactory>()>;

const std::unordered_map<std::string, FactoryMaker> registry = {
    {"opengl", [] { return std::make_unique<OpenGLFactory>(); }},
    {"vulkan", [] { return std::make_unique<VulkanFactory>(); }},
};
```

## Consecuencias
- **Ventajas:**
  - Desacoplamiento total: la adición de nuevas plataformas (como `DirectXFactory`) requiere registrar una nueva entrada sin modificar ninguna lógica existente.
  - El código cliente no contiene sentencias condicionales que acoplen los distintos backends concretos.
  - Búsqueda en tiempo $O(1)$ promedio con manejo claro de errores (`std::out_of_range`).
- **Desventajas:**
  - Ligero costo de indirección mediante `std::function`.
- **Alternativas descartadas:**
  - Estructuras `if (name == "opengl") ... else if (name == "vulkan") ...`: violan el principio Open/Closed y fuerzan a recompilar y modificar el despacho central.
