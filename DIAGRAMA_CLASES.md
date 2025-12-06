# DIAGRAMA DE CLASES UML - SISTEMA TALLER MECÁNICO

## 1. JERARQUÍA DE VEHÍCULOS (Herencia Simple y Múltiple)

```
┌─────────────────────────────────────────────────┐
│              <<interface>>                      │
│              IElectrico                         │
├─────────────────────────────────────────────────┤
│ + getNivelBateria(): QString                    │
└─────────────────────────────────────────────────┘
                    △
                    │ implements
                    │
┌─────────────────────────────────────────────────┐
│         <<abstract>>                            │
│         Vehiculo                                │
├─────────────────────────────────────────────────┤
│ # id: int                                       │
│ # clienteId: int                                │
│ # patente: QString                              │
│ # modelo: QString                               │
│ # año: int                                      │
│ # motor: Motor  ◆──────────┐                    │
├─────────────────────────────────────────────────┤
│ + getTipo(): QString = 0 (virtual puro)         │
│ + getInfoAdicional(): QString = 0               │
│ + operator==(), operator!=(), operator<()       │
│ + operator<<()                                  │
└─────────────────────────────────────────────────┘
         △                  △
         │                  │
    ┌────┴────┐        ┌────┴────┐
    │         │        │         │
┌───┴───┐ ┌──┴──┐ ┌───┴────┐    │
│ Auto  │ │Moto │ │        │    │
├───────┤ ├─────┤ │        │    │
│       │ │     │ │        │    │
└───────┘ └─────┘ │        │    │
                  │        │    │
            ┌─────┴────────┴────┴─────┐
            │   AutoHibrido            │
            │  (Herencia Múltiple)     │
            ├──────────────────────────┤
            │ Auto + IElectrico        │
            │ - nivelBateria: QString  │
            ├──────────────────────────┤
            │ + getNivelBateria()      │
            │ + cargarBateria()        │
            └──────────────────────────┘
```

## 2. COMPOSICIÓN - Motor y Vehículo

```
┌─────────────────────────────────────┐
│           Motor                     │
│        (COMPOSICIÓN)                │
├─────────────────────────────────────┤
│ - tipo: QString                     │
│ - cilindrada: int                   │
│ - potencia: int                     │
│ - combustible: QString              │
├─────────────────────────────────────┤
│ + operator==(), operator!=()        │
│ + operator>(), operator<()          │
│ + operator<<()                      │
└─────────────────────────────────────┘
            ◆
            │ (parte de, no existe sin)
            │
┌───────────┴─────────────────────────┐
│         Vehiculo                    │
│ - motor: Motor                      │
└─────────────────────────────────────┘
```

## 3. AGREGACIÓN - Cliente y Vehículo

```
┌─────────────────────────────────────┐
│         Cliente                     │
│       (AGREGACIÓN)                  │
├─────────────────────────────────────┤
│ - id: int                           │
│ - rut: QString                      │
│ - nombre: QString                   │
│ - telefono: QString                 │
│ - direccion: QString                │
├─────────────────────────────────────┤
│ + validarRut(): bool (overload)     │
│ + coincide(): bool (overload)       │
│ + operator==(), operator!=()        │
│ + operator<(), operator<<()         │
└─────────────────────────────────────┘
            ◇
            │ (tiene, existe independiente)
            │ 1..*
┌───────────┴─────────────────────────┐
│         Vehiculo                    │
│ - clienteId: int                    │
└─────────────────────────────────────┘
```

## 4. HERENCIA - Documentos (Factura y Presupuesto)

```
┌─────────────────────────────────────────────────┐
│         <<abstract>>                            │
│         Documento                               │
├─────────────────────────────────────────────────┤
│ # id: int                                       │
│ # numero: QString                               │
│ # clienteId: int                                │
│ # items: QVector<ItemDocumento>                 │
│ # subtotal: double                              │
│ # impuesto: double                              │
│ # descuento: double                             │
├─────────────────────────────────────────────────┤
│ + getTipo(): QString = 0 (virtual puro)         │
│ + getTotal(): double = 0 (virtual puro)         │
│ + estaVencido(): bool = 0 (virtual puro)        │
│ + getEstado(): QString = 0 (virtual puro)       │
│ + agregarItem(), quitarItem()                   │
│ + operator==(), operator<(), operator<<()       │
└─────────────────────────────────────────────────┘
         △                         △
         │                         │
    ┌────┴────┐              ┌─────┴─────┐
    │         │              │           │
┌───┴──────────────┐   ┌─────┴────────────────┐
│   Factura        │   │   Presupuesto        │
├──────────────────┤   ├──────────────────────┤
│ - estadoPago     │   │ - estadoPresupuesto  │
│ - montoPagado    │   │ - diasValidez        │
│ - metodoPago     │   │ - facturaGeneradaId  │
├──────────────────┤   ├──────────────────────┤
│ + registrarPago()│   │ + enviar()           │
│ + anular()       │   │ + aprobar()          │
│                  │   │ + rechazar()         │
│                  │   │ + convertirAFactura()│
└──────────────────┘   └──────────────────────┘
```

## 5. CLASES DE GESTIÓN

```
┌─────────────────────────────────────┐
│    OrdenTrabajo                     │
├─────────────────────────────────────┤
│ - id: int                           │
│ - vehiculoId: int                   │
│ - estado: Estado (enum)             │
│ - repuestosUsados: QVector          │
│ - costoManoObra: double             │
├─────────────────────────────────────┤
│ + agregarRepuesto()                 │
│ + calcularCostoTotal()              │
│ + cambiarEstado()                   │
└─────────────────────────────────────┘

┌─────────────────────────────────────┐
│    Repuesto                         │
├─────────────────────────────────────┤
│ - id: int                           │
│ - codigo: QString                   │
│ - nombre: QString                   │
│ - stockActual: int                  │
│ - stockMinimo: int                  │
│ - precio: double                    │
├─────────────────────────────────────┤
│ + necesitaReposicion(): bool        │
│ + ajustarStock()                    │
└─────────────────────────────────────┘

┌─────────────────────────────────────┐
│    CitaAgenda                       │
├─────────────────────────────────────┤
│ - id: int                           │
│ - vehiculoId: int                   │
│ - fechaHoraInicio: QDateTime        │
│ - estado: EstadoCita (enum)         │
├─────────────────────────────────────┤
│ + cambiarEstado()                   │
│ + estaAtrasada(): bool              │
└─────────────────────────────────────┘

┌─────────────────────────────────────┐
│    HistorialServicio                │
├─────────────────────────────────────┤
│ - id: int                           │
│ - vehiculoId: int                   │
│ - ordenTrabajoId: int               │
│ - fecha: QDateTime                  │
│ - tipoServicio: QString             │
├─────────────────────────────────────┤
│ + agregarServicio()                 │
└─────────────────────────────────────┘
```

## 6. EXCEPCIONES PERSONALIZADAS

```
┌─────────────────────────────────────┐
│    std::exception                   │
└─────────────────────────────────────┘
            △
            │ inherits
    ┌───────┴───────┐
    │               │
┌───┴────────┐  ┌──┴─────────┐
│ErrorBaseDatos│ │ErrorValidacion│
├────────────┤  ├────────────┤
│ + what()   │  │ + what()   │
└────────────┘  └────────────┘
```

## 7. SINGLETON - DatabaseManager

```
┌─────────────────────────────────────────┐
│    DatabaseManager                      │
│      <<Singleton>>                      │
├─────────────────────────────────────────┤
│ - static instance: DatabaseManager*     │
│ - db: QSqlDatabase                      │
├─────────────────────────────────────────┤
│ - DatabaseManager() (privado)           │
│ + getInstance(): DatabaseManager*       │
│ + connect(): bool                       │
│ + createTables(): void                  │
│ + insertarCliente(), obtenerClientes()  │
│ + insertarVehiculo(), obtenerVehiculos()│
│ + insertarOrden(), obtenerOrdenes()     │
│ + insertarRepuesto(), obtenerRepuestos()│
│ + insertarFactura(), obtenerFacturas()  │
│ + insertarPresupuesto(), etc...         │
└─────────────────────────────────────────┘
```

## 8. CONCEPTOS OOP IMPLEMENTADOS

### ✅ CLASE ABSTRACTA
- `Vehiculo` (con métodos virtuales puros)
- `Documento` (con métodos virtuales puros)

### ✅ HERENCIA SIMPLE
- `Auto` → `Vehiculo`
- `Moto` → `Vehiculo`
- `Factura` → `Documento`
- `Presupuesto` → `Documento`

### ✅ HERENCIA MÚLTIPLE
- `AutoHibrido` → `Auto` + `IElectrico`

### ✅ COMPOSICIÓN
- `Vehiculo` ◆──→ `Motor` (motor es parte del vehículo)

### ✅ AGREGACIÓN
- `Cliente` ◇──→ `Vehiculo` (cliente tiene vehículos)

### ✅ POLIMORFISMO
- Métodos virtuales sobrescritos en clases derivadas
- `getTipo()`, `getTotal()`, `getEstado()`

### ✅ SOBRECARGA DE MÉTODOS
- `validarRut(QString)` y `validarRut()`
- `coincide(QString)` y `coincide(QString, QString)`
- `cargarBateria()` y `cargarBateria(int)`

### ✅ SOBRECARGA DE OPERADORES
- `operator==`, `operator!=`, `operator<`
- `operator<<` (para QTextStream)
- `operator>` (en Motor)

### ✅ EXCEPCIONES PERSONALIZADAS
- `ErrorBaseDatos`
- `ErrorValidacion`

### ✅ PATRÓN SINGLETON
- `DatabaseManager::getInstance()`


