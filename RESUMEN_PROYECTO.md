# 📋 RESUMEN DEL PROYECTO - SISTEMA TALLER MECÁNICO

## 🎯 INFORMACIÓN GENERAL

**Nombre:** Sistema de Gestión de Taller Mecánico  
**Lenguaje:** C++17  
**Framework:** Qt 6.10.1  
**Base de Datos:** SQLite 3  
**Compilador:** MinGW 64-bit  

---

## 📊 CONCEPTOS OOP IMPLEMENTADOS

### ✅ 1. CLASE ABSTRACTA
**Implementación:**
- `Vehiculo` - Clase base abstracta con métodos virtuales puros
- `Documento` - Clase base abstracta para Factura y Presupuesto

**Código:**
```cpp
class Vehiculo {
public:
    virtual QString getTipo() const = 0;      // Virtual puro
    virtual QString getInfoAdicional() const = 0;
};
```

### ✅ 2. HERENCIA SIMPLE
**Implementación:**
- `Auto` → `Vehiculo`
- `Moto` → `Vehiculo`
- `Factura` → `Documento`
- `Presupuesto` → `Documento`

**Diagrama:**
```
    Vehiculo (abstracta)
        ↑
    ┌───┴───┐
  Auto    Moto
```

### ✅ 3. HERENCIA MÚLTIPLE
**Implementación:**
- `AutoHibrido` hereda de `Auto` y de la interfaz `IElectrico`

**Código:**
```cpp
class AutoHibrido : public Auto, public IElectrico {
    // Combina funcionalidad de Auto + IElectrico
};
```

**Diagrama:**
```
    Auto          IElectrico
      ↑               ↑
      └───────┬───────┘
          AutoHibrido
```

### ✅ 4. COMPOSICIÓN
**Implementación:**
- `Vehiculo` ◆──→ `Motor`
- El motor es **parte integral** del vehículo, no existe sin él

**Código:**
```cpp
class Vehiculo {
protected:
    Motor motor;  // COMPOSICIÓN - motor es parte del vehículo
};
```

**Diagrama:**
```
┌──────────┐   ◆────────┐
│ Vehiculo │───────────>│ Motor │
└──────────┘ compuesto  └───────┘
```

### ✅ 5. AGREGACIÓN
**Implementación:**
- `Cliente` ◇──→ `Vehiculo`
- El cliente **tiene** vehículos, pero los vehículos existen independientemente

**Diagrama:**
```
┌─────────┐   ◇────────┐
│ Cliente │──────────>│Vehiculo│
└─────────┘  tiene    └────────┘
```

### ✅ 6. POLIMORFISMO
**Implementación:**
- Métodos virtuales sobrescritos en clases derivadas

**Código:**
```cpp
// Clase base
virtual QString getTipo() const = 0;

// Auto
QString getTipo() const override { return "AUTO"; }

// Moto
QString getTipo() const override { return "MOTO"; }

// Uso polimórfico
Vehiculo* v = new Auto();
qDebug() << v->getTipo();  // Llama a Auto::getTipo()
```

### ✅ 7. SOBRECARGA DE MÉTODOS
**Implementación:**

**En Cliente:**
```cpp
// Sobrecarga 1
bool validarRut();

// Sobrecarga 2
static bool validarRut(const QString &rut);

// Sobrecarga 3
bool coincide(const QString &texto) const;

// Sobrecarga 4
bool coincide(const QString &texto, const QString &criterio) const;
```

**En AutoHibrido:**
```cpp
// Sobrecarga 1
void cargarBateria();

// Sobrecarga 2
void cargarBateria(int porcentaje);
```

### ✅ 8. SOBRECARGA DE OPERADORES
**Implementación:**

**Operadores de comparación:**
```cpp
bool operator==(const Vehiculo &otro) const;
bool operator!=(const Vehiculo &otro) const;
bool operator<(const Vehiculo &otro) const;
```

**Operador de salida:**
```cpp
friend QTextStream &operator<<(QTextStream &out, const Vehiculo &v);
```

**En Motor:**
```cpp
bool operator==(const Motor &otro) const;
bool operator>(const Motor &otro) const;
bool operator<(const Motor &otro) const;
```

### ✅ 9. EXCEPCIONES PERSONALIZADAS
**Implementación:**

```cpp
// Exception base: std::exception
//       ↑
//   ┌───┴───────┐
//   │           │
// ErrorBaseDatos  ErrorValidacion

class ErrorBaseDatos : public std::exception {
private:
    std::string mensaje;
public:
    ErrorBaseDatos(const std::string &msg) : mensaje(msg) {}
    const char* what() const noexcept override {
        return mensaje.c_str();
    }
};
```

**Uso:**
```cpp
try {
    db->insertarCliente(cliente);
} catch (const ErrorBaseDatos &e) {
    QMessageBox::critical(this, "Error", e.what());
}
```

### ✅ 10. CRUD CON BASE DE DATOS
**Implementación completa en todas las entidades:**

#### CLIENTES
```cpp
- insertarCliente(Cliente &cliente)
- obtenerCliente(int id)
- obtenerTodosClientes()
- actualizarCliente(const Cliente &cliente)
- eliminarCliente(int id)
```

#### VEHÍCULOS
```cpp
- insertarVehiculo(Vehiculo *vehiculo)
- obtenerVehiculo(int id)
- obtenerVehiculosCliente(int clienteId)
- obtenerTodosVehiculos()
- eliminarVehiculo(int id)
```

#### ÓRDENES DE TRABAJO
```cpp
- insertarOrdenTrabajo(OrdenTrabajo &orden)
- obtenerOrdenTrabajo(int id)
- obtenerTodasOrdenes()
- actualizarOrdenTrabajo(const OrdenTrabajo &orden)
```

#### REPUESTOS (Inventario)
```cpp
- insertarRepuesto(Repuesto &repuesto)
- obtenerRepuesto(int id)
- obtenerTodosRepuestos()
- actualizarRepuesto(const Repuesto &repuesto)
- eliminarRepuesto(int id)
- actualizarStock(int id, int cantidad, bool esIngreso)
```

#### FACTURAS Y PRESUPUESTOS
```cpp
- insertarFactura(Factura &factura)
- obtenerFactura(int id)
- obtenerTodasFacturas()
- actualizarFactura(const Factura &factura)

- insertarPresupuesto(Presupuesto &presupuesto)
- obtenerPresupuesto(int id)
- obtenerTodosPresupuestos()
- actualizarPresupuesto(const Presupuesto &presupuesto)
```

#### CITAS AGENDA
```cpp
- insertarCita(CitaAgenda &cita)
- obtenerCita(int id)
- obtenerTodasCitas()
- obtenerCitasPorFecha(const QDate &fecha)
- actualizarCita(const CitaAgenda &cita)
- eliminarCita(int id)
```

---

## 🗂️ ESTRUCTURA DE LA BASE DE DATOS

### Tablas Principales
1. **clientes** - Datos de clientes
2. **vehiculos** - Vehículos (Auto, Moto, Híbrido)
3. **ordenes_trabajo** - Órdenes de trabajo/servicio
4. **repuestos** - Inventario de repuestos
5. **repuestos_orden** - Relación N:M entre órdenes y repuestos
6. **facturas** - Facturas de cobro
7. **presupuestos** - Presupuestos de trabajo
8. **items_documento** - Items de facturas/presupuestos
9. **citas_agenda** - Calendario de citas
10. **historial_servicio** - Historial por vehículo

### Relaciones
- Cliente **1:N** Vehículos
- Vehículo **1:N** Órdenes de Trabajo
- Vehículo **1:N** Citas
- Orden **N:M** Repuestos (tabla intermedia: repuestos_orden)
- Cliente **1:N** Facturas
- Cliente **1:N** Presupuestos
- Factura/Presupuesto **1:N** Items

---

## 🎨 FUNCIONALIDADES DEL SISTEMA

### 📋 Gestión de Clientes
- ✅ Agregar, editar, eliminar clientes
- ✅ Validación de RUT chileno
- ✅ Búsqueda y filtrado
- ✅ Ver historial de servicios por cliente

### 🚗 Gestión de Vehículos
- ✅ Registrar Auto, Moto, Auto Híbrido
- ✅ Datos del motor (composición)
- ✅ Asociación con clientes (agregación)
- ✅ Ver historial de servicios por vehículo

### 🔧 Órdenes de Trabajo
- ✅ Crear órdenes con estados
- ✅ Asignar repuestos a la orden
- ✅ Calcular costos (mano de obra + repuestos)
- ✅ Seguimiento de estados:
  - Pendiente
  - En proceso
  - Esperando repuestos
  - Completada
  - Entregada
  - Cancelada

### 📦 Inventario de Repuestos
- ✅ CRUD de repuestos
- ✅ Control de stock (actual vs mínimo)
- ✅ Ajustes de inventario (ingresos/egresos)
- ✅ Alertas de stock crítico

### 💰 Facturación
- ✅ Crear facturas con items múltiples
- ✅ Crear presupuestos
- ✅ Cálculo automático de totales (subtotal, IVA, descuento)
- ✅ Registro de pagos (total o parcial)
- ✅ Anular facturas
- ✅ Convertir presupuesto aprobado a factura
- ✅ Ver detalles completos de documentos

### 📅 Agenda/Calendario
- ✅ Programar citas
- ✅ Calendario visual con días marcados
- ✅ Estados de citas
- ✅ Lista de citas por día
- ✅ Colores por estado

---

## 🎨 INTERFAZ GRÁFICA

### Diseño
- **Tema:** Claro con acentos naranjas (#ea6f15)
- **Fondo:** Blanco (#ffffff)
- **Contraste:** Suave y profesional
- **Logo:** Integrado en la interfaz

### Pestañas Principales
1. **CLIENTES** - Gestión de clientes
2. **ÓRDENES** - Órdenes de trabajo
3. **INVENTARIO** - Repuestos y stock
4. **AGENDA** - Calendario de citas
5. **FACTURACIÓN** - Facturas y presupuestos

---

## 📁 ARCHIVOS DEL PROYECTO

```
POOOO/
├── main.cpp
├── mainwindow.h/cpp/ui
├── TallerMecanico.pro
├── resources.qrc
├── models/
│   ├── vehiculo.h/cpp
│   ├── auto.h/cpp
│   ├── moto.h/cpp
│   ├── autohibrido.h/cpp
│   ├── motor.h/cpp
│   ├── cliente.h/cpp
│   ├── documento.h/cpp
│   ├── ordentrabajo.h/cpp
│   ├── repuesto.h/cpp
│   ├── citaagenda.h/cpp
│   └── historialservicio.h/cpp
├── dialogs/
│   ├── clientedialog.h/cpp/ui
│   ├── vehiculodialog.h/cpp/ui
│   ├── facturadialog.h/cpp
│   ├── presupuestodialog.h/cpp
│   ├── repuestodialog.h/cpp
│   ├── ordentrabajodialog.h/cpp
│   └── citadialog.h/cpp
├── database/
│   └── databasemanager.h/cpp
└── images/
    ├── Logo.png
    └── icon.ico
```

---

## 🔧 PATRONES DE DISEÑO

### Singleton
- `DatabaseManager` - Una única instancia global

### MVC (Model-View-Controller)
- **Model:** Clases en /models
- **View:** Archivos .ui
- **Controller:** MainWindow y Dialogs

### Factory (implícito)
- Creación de diferentes tipos de vehículos

### Template Method
- Métodos abstractos en clases base

---

## ✅ CHECKLIST DE REQUISITOS

- [x] Clase Abstracta
- [x] Herencia Simple
- [x] Herencia Múltiple
- [x] Composición
- [x] Agregación
- [x] Polimorfismo
- [x] Sobrecarga de Métodos
- [x] Sobrecarga de Operadores
- [x] Excepciones Personalizadas
- [x] CRUD con Base de Datos
- [x] Interfaz Gráfica Profesional
- [x] Funcionalidades Completas

---

## 🚀 CÓMO COMPILAR Y EJECUTAR

1. Abrir **Qt Creator**
2. Abrir proyecto: `TallerMecanico.pro`
3. Compilar: **Ctrl+B**
4. Ejecutar: **Ctrl+R**

---

## 📝 NOTAS ADICIONALES

- Base de datos se crea automáticamente en primera ejecución
- Datos de prueba pueden agregarse manualmente
- Sistema completo y funcional
- Cumple todos los requisitos de la evaluación

---

**Fecha:** Diciembre 2025  
**Autor:** Sistema de Gestión de Taller Mecánico  
**Versión:** 1.0


