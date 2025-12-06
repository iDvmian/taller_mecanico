# DIAGRAMA DE ARQUITECTURA DEL SISTEMA

## ARQUITECTURA EN CAPAS

```
╔════════════════════════════════════════════════════════════════╗
║                    CAPA DE PRESENTACIÓN (UI)                   ║
║                         Qt Widgets                             ║
╠════════════════════════════════════════════════════════════════╣
║                                                                ║
║  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐        ║
║  │ MainWindow   │  │ ClienteDialog│  │VehiculoDialog│        ║
║  │   (.ui)      │  │   (.ui)      │  │   (.ui)      │        ║
║  └──────────────┘  └──────────────┘  └──────────────┘        ║
║                                                                ║
║  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐        ║
║  │FacturaDialog │  │PresupDialog  │  │RepuestoDialog│        ║
║  └──────────────┘  └──────────────┘  └──────────────┘        ║
║                                                                ║
║  ┌──────────────┐  ┌──────────────┐                          ║
║  │  OrdenDialog │  │  CitaDialog  │                          ║
║  └──────────────┘  └──────────────┘                          ║
║                                                                ║
╠════════════════════════════════════════════════════════════════╣
║                   CAPA DE CONTROL (Lógica)                     ║
╠════════════════════════════════════════════════════════════════╣
║                                                                ║
║  Slots y Señales (Qt)                                         ║
║  ├─ onAgregarCliente()                                        ║
║  ├─ onNuevaOrden()                                            ║
║  ├─ onNuevaFactura()                                          ║
║  └─ ...                                                       ║
║                                                                ║
╠════════════════════════════════════════════════════════════════╣
║                    CAPA DE MODELO (Business Logic)             ║
╠════════════════════════════════════════════════════════════════╣
║                                                                ║
║  ┌─────────────────────────────────────────────────────────┐  ║
║  │              JERARQUÍA DE CLASES                        │  ║
║  ├─────────────────────────────────────────────────────────┤  ║
║  │                                                         │  ║
║  │  Vehiculo (Abstract)                                    │  ║
║  │    ├─ Auto                                              │  ║
║  │    ├─ Moto                                              │  ║
║  │    └─ AutoHibrido (Herencia Múltiple)                  │  ║
║  │                                                         │  ║
║  │  Documento (Abstract)                                   │  ║
║  │    ├─ Factura                                           │  ║
║  │    └─ Presupuesto                                       │  ║
║  │                                                         │  ║
║  │  Cliente                                                │  ║
║  │  Motor (Composición con Vehiculo)                       │  ║
║  │  OrdenTrabajo                                           │  ║
║  │  Repuesto                                               │  ║
║  │  CitaAgenda                                             │  ║
║  │  HistorialServicio                                      │  ║
║  │                                                         │  ║
║  └─────────────────────────────────────────────────────────┘  ║
║                                                                ║
╠════════════════════════════════════════════════════════════════╣
║                   CAPA DE ACCESO A DATOS                       ║
╠════════════════════════════════════════════════════════════════╣
║                                                                ║
║  ┌──────────────────────────────────────────────────────┐     ║
║  │         DatabaseManager (Singleton)                  │     ║
║  ├──────────────────────────────────────────────────────┤     ║
║  │  + getInstance()                                     │     ║
║  │  + connect()                                         │     ║
║  │  + createTables()                                    │     ║
║  │                                                      │     ║
║  │  CRUD Clientes:                                      │     ║
║  │  ├─ insertarCliente()                                │     ║
║  │  ├─ obtenerCliente()                                 │     ║
║  │  ├─ actualizarCliente()                              │     ║
║  │  └─ eliminarCliente()                                │     ║
║  │                                                      │     ║
║  │  CRUD Vehículos:                                     │     ║
║  │  ├─ insertarVehiculo()                               │     ║
║  │  ├─ obtenerVehiculos()                               │     ║
║  │  └─ eliminarVehiculo()                               │     ║
║  │                                                      │     ║
║  │  CRUD Órdenes:                                       │     ║
║  │  ├─ insertarOrdenTrabajo()                           │     ║
║  │  ├─ obtenerOrdenes()                                 │     ║
║  │  └─ actualizarOrdenTrabajo()                         │     ║
║  │                                                      │     ║
║  │  CRUD Repuestos:                                     │     ║
║  │  ├─ insertarRepuesto()                               │     ║
║  │  ├─ obtenerRepuestos()                               │     ║
║  │  └─ actualizarStock()                                │     ║
║  │                                                      │     ║
║  │  CRUD Facturas/Presupuestos:                         │     ║
║  │  ├─ insertarFactura()                                │     ║
║  │  ├─ insertarPresupuesto()                            │     ║
║  │  ├─ obtenerFacturas()                                │     ║
║  │  └─ actualizarFactura()                              │     ║
║  │                                                      │     ║
║  │  CRUD Citas:                                         │     ║
║  │  ├─ insertarCita()                                   │     ║
║  │  ├─ obtenerCitas()                                   │     ║
║  │  └─ actualizarCita()                                 │     ║
║  │                                                      │     ║
║  │  Manejo de Excepciones:                              │     ║
║  │  ├─ ErrorBaseDatos                                   │     ║
║  │  └─ ErrorValidacion                                  │     ║
║  └──────────────────────────────────────────────────────┘     ║
║                            │                                   ║
║                            ▼                                   ║
╠════════════════════════════════════════════════════════════════╣
║                      BASE DE DATOS                             ║
╠════════════════════════════════════════════════════════════════╣
║                                                                ║
║                  SQLite Database                               ║
║            (taller_mecanico.db)                                ║
║                                                                ║
║  Tablas:                                                       ║
║  ├─ clientes                                                   ║
║  ├─ vehiculos                                                  ║
║  ├─ ordenes_trabajo                                            ║
║  ├─ repuestos                                                  ║
║  ├─ repuestos_orden                                            ║
║  ├─ facturas                                                   ║
║  ├─ presupuestos                                               ║
║  ├─ items_documento                                            ║
║  ├─ citas_agenda                                               ║
║  └─ historial_servicio                                         ║
║                                                                ║
╚════════════════════════════════════════════════════════════════╝
```

## FLUJO DE DATOS - EJEMPLO: CREAR FACTURA

```
┌─────────────┐
│   Usuario   │
└──────┬──────┘
       │ 1. Click "Nueva Factura"
       ▼
┌─────────────────────────────────┐
│      MainWindow                 │
│  onNuevaFactura()               │
└──────┬──────────────────────────┘
       │ 2. Abre diálogo
       ▼
┌─────────────────────────────────┐
│    FacturaDialog                │
│  - Cargar clientes              │
│  - Cargar órdenes               │
│  - Agregar items                │
│  - Calcular totales             │
└──────┬──────────────────────────┘
       │ 3. Usuario completa y acepta
       ▼
┌─────────────────────────────────┐
│    Factura (Modelo)             │
│  - Validar datos                │
│  - Calcular subtotal            │
│  - Calcular total con IVA       │
└──────┬──────────────────────────┘
       │ 4. Llamar a DB Manager
       ▼
┌─────────────────────────────────┐
│    DatabaseManager              │
│  insertarFactura()              │
│  - BEGIN TRANSACTION            │
│  - INSERT INTO facturas         │
│  - INSERT INTO items_documento  │
│  - COMMIT                       │
└──────┬──────────────────────────┘
       │ 5. Guardar en BD
       ▼
┌─────────────────────────────────┐
│    SQLite Database              │
│  - facturas                     │
│  - items_documento              │
└──────┬──────────────────────────┘
       │ 6. Éxito/Error
       ▼
┌─────────────────────────────────┐
│    MainWindow                   │
│  - actualizarTablaFacturas()    │
│  - actualizarDashboard()        │
│  - Mostrar mensaje              │
└─────────────────────────────────┘
```

## ESTRUCTURA DE ARCHIVOS

```
POOOO/
│
├── main.cpp                          # Punto de entrada
│
├── mainwindow.h/cpp/ui               # Ventana principal
│
├── TallerMecanico.pro                # Archivo de proyecto Qt
├── resources.qrc                     # Recursos (imágenes)
│
├── models/                           # CAPA DE MODELO
│   ├── vehiculo.h/cpp                # Clase abstracta base
│   ├── auto.h/cpp                    # Herencia simple
│   ├── moto.h/cpp                    # Herencia simple
│   ├── autohibrido.h/cpp             # Herencia múltiple
│   ├── motor.h/cpp                   # Composición
│   ├── cliente.h/cpp                 # Agregación
│   ├── documento.h/cpp               # Clase abstracta
│   ├── ordentrabajo.h/cpp            # Gestión de trabajos
│   ├── repuesto.h/cpp                # Inventario
│   ├── citaagenda.h/cpp              # Calendario
│   └── historialservicio.h/cpp       # Historial
│
├── dialogs/                          # CAPA DE PRESENTACIÓN
│   ├── clientedialog.h/cpp/ui        # UI Cliente
│   ├── vehiculodialog.h/cpp/ui       # UI Vehículo
│   ├── facturadialog.h/cpp           # UI Factura
│   ├── presupuestodialog.h/cpp       # UI Presupuesto
│   ├── repuestodialog.h/cpp          # UI Repuesto
│   ├── ordentrabajodialog.h/cpp      # UI Orden
│   └── citadialog.h/cpp              # UI Cita
│
├── database/                         # CAPA DE DATOS
│   ├── databasemanager.h/cpp         # Singleton + CRUD
│   └── taller_mecanico.db            # SQLite (generado)
│
└── images/                           # Recursos
    ├── Logo.png
    └── icon.ico
```

## PATRONES DE DISEÑO UTILIZADOS

### 1. **SINGLETON**
```cpp
DatabaseManager* DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return &instance;
}
```

### 2. **MVC (Model-View-Controller)**
- **Model**: Clases en /models
- **View**: Archivos .ui y widgets Qt
- **Controller**: MainWindow y Dialogs

### 3. **FACTORY (implícito)**
```cpp
Vehiculo* vehiculo = nullptr;
if (tipo == "Auto") {
    vehiculo = new Auto(...);
} else if (tipo == "Moto") {
    vehiculo = new Moto(...);
}
```

### 4. **TEMPLATE METHOD** (en clases abstractas)
```cpp
// Documento define la estructura
double Documento::getTotal() const = 0;  // Implementado por hijos
QString Documento::getTipo() const = 0;
```

## TECNOLOGÍAS UTILIZADAS

### Framework
- **Qt 6.10.1** - Framework de UI
- **Qt Creator** - IDE

### Base de Datos
- **SQLite 3** - Base de datos embebida
- **Qt SQL Module** - Driver y ORM

### Lenguaje
- **C++17** - Estándar del lenguaje
- **MinGW 64-bit** - Compilador

### Conceptos OOP
- Clases Abstractas
- Herencia Simple y Múltiple
- Composición y Agregación
- Polimorfismo
- Sobrecarga de Métodos
- Sobrecarga de Operadores
- Excepciones Personalizadas
- Patrón Singleton

## FUNCIONALIDADES DEL SISTEMA

### ✅ Gestión de Clientes
- CRUD completo
- Validación de RUT
- Historial por cliente

### ✅ Gestión de Vehículos
- Múltiples tipos (Auto, Moto, Híbrido)
- Asociación con clientes
- Historial de servicios

### ✅ Órdenes de Trabajo
- Estados de seguimiento
- Repuestos usados
- Cálculo de costos
- Historial

### ✅ Inventario de Repuestos
- Control de stock
- Stock crítico
- Ajustes de inventario

### ✅ Facturación
- Facturas con items
- Presupuestos
- Registro de pagos
- Conversión presupuesto → factura

### ✅ Agenda/Calendario
- Citas programadas
- Visualización por fecha
- Estados de citas
- Marcadores en calendario

## CONCEPTOS OOP CUMPLIDOS ✅

1. ✅ Clase Abstracta (Vehiculo, Documento)
2. ✅ Herencia Simple (Auto, Moto, Factura, Presupuesto)
3. ✅ Herencia Múltiple (AutoHibrido)
4. ✅ Composición (Vehiculo ◆─ Motor)
5. ✅ Agregación (Cliente ◇─ Vehiculo)
6. ✅ Polimorfismo (métodos virtuales)
7. ✅ Sobrecarga de Métodos (validarRut, coincide, cargarBateria)
8. ✅ Sobrecarga de Operadores (==, !=, <, <<, >)
9. ✅ Excepciones Personalizadas (ErrorBaseDatos, ErrorValidacion)
10. ✅ CRUD Completo con Base de Datos SQLite


