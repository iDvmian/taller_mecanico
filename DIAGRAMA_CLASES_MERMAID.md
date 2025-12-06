# 📊 DIAGRAMAS DE CLASES (VISUAL)

## CÓMO VER ESTOS DIAGRAMAS COMO IMÁGENES:

### Opción 1: GitHub
- Sube este archivo a GitHub y se verá automáticamente como diagrama

### Opción 2: VS Code
- Instala la extensión "Markdown Preview Mermaid Support"
- Abre este archivo y presiona `Ctrl+Shift+V` para vista previa

### Opción 3: Online (CONVERTIR A PNG/SVG)
1. Ve a: https://mermaid.live/
2. Copia el código del diagrama
3. Se genera automáticamente la imagen
4. Descarga como PNG o SVG

---

## 1. JERARQUÍA DE VEHÍCULOS (Herencia Simple y Múltiple)

```mermaid
classDiagram
    %% Interfaz
    class IElectrico {
        <<interface>>
        +getNivelBateria() QString
    }
    
    %% Clase abstracta base
    class Vehiculo {
        <<abstract>>
        #id: int
        #clienteId: int
        #patente: QString
        #modelo: QString
        #anio: int
        #motor: Motor
        +getTipo()* QString
        +getInfoAdicional()* QString
        +getPatente() QString
        +getModelo() QString
        +operator==() bool
        +operator!=() bool
        +operator~() bool
    }
    
    %% Motor (composición)
    class Motor {
        -tipo: QString
        -cilindrada: int
        -potencia: int
        -combustible: QString
        +getTipo() QString
        +getCilindrada() int
        +getPotencia() int
        +operator==() bool
        +operator>() bool
        +operator~() bool
    }
    
    %% Herencia simple
    class Auto {
        -numeroPuertas: int
        +getTipo() QString
        +getInfoAdicional() QString
        +getNumeroPuertas() int
        +mostrarInfo() void
        +mostrarInfo(bool) void
    }
    
    class Moto {
        -tieneCajon: bool
        +getTipo() QString
        +getInfoAdicional() QString
        +tieneCajonCarga() bool
    }
    
    %% Herencia múltiple
    class AutoHibrido {
        -nivelBateria: QString
        +getTipo() QString
        +getInfoAdicional() QString
        +getNivelBateria() QString
        +cargarBateria() void
        +cargarBateria(int) void
    }
    
    %% Relaciones
    Vehiculo <|-- Auto : hereda
    Vehiculo <|-- Moto : hereda
    Auto <|-- AutoHibrido : hereda
    IElectrico <|.. AutoHibrido : implementa
    Vehiculo *-- Motor : composición
    
    %% Notas
    note for Vehiculo "Clase Abstracta\nMétodos virtuales puros"
    note for AutoHibrido "HERENCIA MÚLTIPLE\nAuto + IElectrico"
    note for Motor "COMPOSICIÓN\nParte integral del vehículo"
```

---

## 2. DOCUMENTOS (Factura y Presupuesto)

```mermaid
classDiagram
    %% Clase abstracta
    class Documento {
        <<abstract>>
        #id: int
        #numero: QString
        #clienteId: int
        #fecha: QDateTime
        #items: QVector~ItemDocumento~
        #subtotal: double
        #impuesto: double
        #descuento: double
        +getTipo()* QString
        +getTotal()* double
        +estaVencido()* bool
        +getEstado()* QString
        +agregarItem() void
        +quitarItem() void
        +calcularSubtotal() double
    }
    
    class ItemDocumento {
        <<struct>>
        +descripcion: QString
        +cantidad: int
        +precioUnitario: double
        +subtotal: double
    }
    
    class Factura {
        -estadoPago: EstadoFactura
        -montoPagado: double
        -metodoPago: QString
        -fechaPago: QDateTime
        +getTipo() QString
        +getTotal() double
        +estaVencido() bool
        +getEstado() QString
        +registrarPago() void
        +anular() void
    }
    
    class Presupuesto {
        -estado: EstadoPresupuesto
        -diasValidez: int
        -facturaGeneradaId: int
        +getTipo() QString
        +getTotal() double
        +estaVencido() bool
        +getEstado() QString
        +enviar() void
        +aprobar() void
        +rechazar() void
        +convertirAFactura() int
    }
    
    class EstadoFactura {
        <<enumeration>>
        PENDIENTE
        PAGADA
        PARCIAL
        VENCIDA
        ANULADA
    }
    
    class EstadoPresupuesto {
        <<enumeration>>
        BORRADOR
        ENVIADO
        APROBADO
        RECHAZADO
        VENCIDO
        CONVERTIDO
    }
    
    %% Relaciones
    Documento <|-- Factura : hereda
    Documento <|-- Presupuesto : hereda
    Documento o-- ItemDocumento : contiene
    Factura --> EstadoFactura : usa
    Presupuesto --> EstadoPresupuesto : usa
    
    note for Documento "Clase Abstracta\nPolimorfismo"
```

---

## 3. CLIENTE Y VEHÍCULO (Agregación)

```mermaid
classDiagram
    class Cliente {
        -id: int
        -rut: QString
        -nombre: QString
        -apellido: QString
        -telefono: QString
        -direccion: QString
        +validarRut() bool
        +validarRut(QString)$ bool
        +coincide(QString) bool
        +coincide(QString, QString) bool
        +operator==() bool
        +operator!=() bool
        +operator~() bool
    }
    
    class Vehiculo {
        <<abstract>>
        #id: int
        #clienteId: int
        #patente: QString
        #modelo: QString
        #anio: int
        +getTipo()* QString
        +getInfoAdicional()* QString
    }
    
    %% Agregación
    Cliente o-- "0..*" Vehiculo : tiene
    
    note for Cliente "AGREGACIÓN\nCliente tiene vehículos\npero existen independientes"
    note for Cliente "SOBRECARGA MÉTODOS\nvalidarRut() x2\ncoincide() x2"
```

---

## 4. GESTIÓN DE ÓRDENES Y REPUESTOS

```mermaid
classDiagram
    class OrdenTrabajo {
        -id: int
        -vehiculoId: int
        -fechaIngreso: QDateTime
        -fechaEntrega: QDateTime
        -descripcion: QString
        -estado: EstadoOrden
        -costoManoObra: double
        -observaciones: QString
        -repuestosUsados: QVector~RepuestoUsado~
        +agregarRepuesto() void
        +quitarRepuesto() void
        +calcularCostoTotal() double
        +cambiarEstado() void
        +getEstadoTexto() QString
    }
    
    class EstadoOrden {
        <<enumeration>>
        PENDIENTE
        EN_PROCESO
        ESPERANDO_REPUESTOS
        COMPLETADA
        ENTREGADA
        CANCELADA
    }
    
    class RepuestoUsado {
        <<struct>>
        +repuestoId: int
        +nombre: QString
        +cantidad: int
        +precioUnitario: double
        +subtotal: double
    }
    
    class Repuesto {
        -id: int
        -codigo: QString
        -nombre: QString
        -descripcion: QString
        -precio: double
        -stockActual: int
        -stockMinimo: int
        -categoria: QString
        +necesitaReposicion() bool
        +ajustarStock() void
        +esStockCritico() bool
    }
    
    class Vehiculo {
        <<abstract>>
        #id: int
        #patente: QString
    }
    
    %% Relaciones
    Vehiculo --> "1..*" OrdenTrabajo : tiene
    OrdenTrabajo --> EstadoOrden : usa
    OrdenTrabajo o-- RepuestoUsado : contiene
    RepuestoUsado --> Repuesto : referencia
```

---

## 5. AGENDA Y CITAS

```mermaid
classDiagram
    class CitaAgenda {
        -id: int
        -vehiculoId: int
        -clienteNombre: QString
        -vehiculoPatente: QString
        -fechaHoraInicio: QDateTime
        -fechaHoraFin: QDateTime
        -titulo: QString
        -descripcion: QString
        -estado: EstadoCita
        +cambiarEstado() void
        +estaAtrasada() bool
        +getDuracion() int
        +getEstadoTexto() QString
    }
    
    class EstadoCita {
        <<enumeration>>
        PROGRAMADA
        CONFIRMADA
        EN_CURSO
        COMPLETADA
        CANCELADA
        NO_ASISTIO
    }
    
    class Vehiculo {
        <<abstract>>
        #id: int
        #patente: QString
    }
    
    class HistorialServicio {
        -id: int
        -vehiculoId: int
        -ordenTrabajoId: int
        -fecha: QDateTime
        -tipoServicio: QString
        -descripcion: QString
        -costo: double
        -kilometraje: int
    }
    
    %% Relaciones
    Vehiculo --> "0..*" CitaAgenda : tiene
    Vehiculo --> "0..*" HistorialServicio : tiene
    CitaAgenda --> EstadoCita : usa
```

---

## 6. PATRÓN SINGLETON - DatabaseManager

```mermaid
classDiagram
    class DatabaseManager {
        <<Singleton>>
        -instance$: DatabaseManager*
        -db: QSqlDatabase
        -DatabaseManager()
        +getInstance()$ DatabaseManager*
        +connect() bool
        +createTables() void
        +insertarCliente() bool
        +obtenerClientes() QVector
        +insertarVehiculo() bool
        +obtenerVehiculos() QVector
        +insertarOrdenTrabajo() bool
        +insertarRepuesto() bool
        +insertarFactura() bool
        +insertarPresupuesto() bool
        +insertarCita() bool
        +obtenerIngresosDelMes() double
        +obtenerRepuestosStockCritico() QVector
    }
    
    class Cliente {
        -id: int
        -rut: QString
        -nombre: QString
    }
    
    class Vehiculo {
        <<abstract>>
        #id: int
        #patente: QString
    }
    
    class OrdenTrabajo {
        -id: int
        -vehiculoId: int
    }
    
    class Repuesto {
        -id: int
        -codigo: QString
    }
    
    class Factura {
        -id: int
        -numero: QString
    }
    
    class Presupuesto {
        -id: int
        -numero: QString
    }
    
    class CitaAgenda {
        -id: int
        -vehiculoId: int
    }
    
    %% Relaciones
    DatabaseManager ..> Cliente : gestiona
    DatabaseManager ..> Vehiculo : gestiona
    DatabaseManager ..> OrdenTrabajo : gestiona
    DatabaseManager ..> Repuesto : gestiona
    DatabaseManager ..> Factura : gestiona
    DatabaseManager ..> Presupuesto : gestiona
    DatabaseManager ..> CitaAgenda : gestiona
    
    note for DatabaseManager "PATRÓN SINGLETON\nUna única instancia\nConstructor privado"
```

---

## 7. EXCEPCIONES PERSONALIZADAS

```mermaid
classDiagram
    class exception {
        <<standard>>
        +what() const char*
    }
    
    class ErrorBaseDatos {
        -mensaje: string
        +ErrorBaseDatos(string)
        +what() const char*
    }
    
    class ErrorValidacion {
        -mensaje: string
        +ErrorValidacion(string)
        +what() const char*
    }
    
    %% Herencia
    exception <|-- ErrorBaseDatos : hereda
    exception <|-- ErrorValidacion : hereda
    
    note for ErrorBaseDatos "Errores de BD\nSQLite errors"
    note for ErrorValidacion "Errores de datos\nValidaciones"
```

---

## 8. DIAGRAMA GENERAL DEL SISTEMA

```mermaid
classDiagram
    %% Clases principales
    class Cliente
    class Vehiculo {
        <<abstract>>
    }
    class Auto
    class Moto
    class AutoHibrido
    class Motor
    class OrdenTrabajo
    class Repuesto
    class Factura
    class Presupuesto
    class CitaAgenda
    class HistorialServicio
    class DatabaseManager {
        <<Singleton>>
    }
    
    %% Relaciones principales
    Cliente o-- Vehiculo : agregación
    Vehiculo <|-- Auto : herencia
    Vehiculo <|-- Moto : herencia
    Auto <|-- AutoHibrido : herencia múltiple
    Vehiculo *-- Motor : composición
    Vehiculo --> OrdenTrabajo
    Vehiculo --> CitaAgenda
    Vehiculo --> HistorialServicio
    OrdenTrabajo --> Repuesto
    Cliente --> Factura
    Cliente --> Presupuesto
    DatabaseManager ..> Cliente
    DatabaseManager ..> Vehiculo
    DatabaseManager ..> OrdenTrabajo
    DatabaseManager ..> Repuesto
    DatabaseManager ..> Factura
```

---

## LEYENDA DE RELACIONES

- `<|--` : **Herencia** (Auto hereda de Vehiculo)
- `*--` : **Composición** (Motor es parte de Vehiculo)
- `o--` : **Agregación** (Cliente tiene Vehículos)
- `-->` : **Asociación** (Relación simple)
- `..>` : **Dependencia** (Usa temporalmente)
- `<|..` : **Implementación** (Implementa interfaz)

---

## CÓMO GENERAR IMÁGENES PNG/SVG:

### Método 1: Mermaid Live Editor
1. Ve a: https://mermaid.live/
2. Copia cualquier bloque de código Mermaid
3. Se genera automáticamente
4. Click en "Download PNG" o "Download SVG"

### Método 2: VS Code
1. Instala extensión: "Markdown Preview Mermaid Support"
2. Abre este archivo
3. Click derecho → "Markdown Preview Mermaid: Save to PNG/SVG"

### Método 3: Online Converter
- https://mermaid.ink/ (convierte código a URL de imagen)

---

**TODOS LOS DIAGRAMAS SON RENDERIZABLES COMO IMÁGENES** ✅

