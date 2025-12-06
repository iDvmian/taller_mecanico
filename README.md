# 🔧 Sistema Taller Mecánico - Qt + SQLite

Sistema completo de gestión de taller mecánico con interfaz gráfica Qt y base de datos **SQLite** (integrada, sin configuración).

## 📋 Características

### Módulos Principales
- **👥 Gestión de Clientes**: Agregar, editar, eliminar, consultar y ver historial
- **🚗 Gestión de Vehículos**: Registrar autos, motos y autos híbridos con historial
- **📝 Órdenes de Trabajo**: Crear, editar, cambiar estados, seguimiento completo
- **📦 Inventario de Repuestos**: Control de stock, alertas de stock crítico
- **📅 Agenda/Calendario**: Programar citas, ver citas del día/semana
- **💰 Facturación**: Facturas, presupuestos y registro de pagos
- **📊 Reportes**: Ingresos, trabajos realizados, stock crítico

### Base de Datos
- **SQLite integrado**: No requiere instalar servidores externos
- **Persistencia automática**: Los datos se guardan en un archivo local
- **Creación automática de tablas**: Al iniciar la aplicación

## 🎯 Conceptos POO Implementados

| Concepto | Implementación | Archivo |
|----------|----------------|---------|
| **Clase Abstracta** | `Vehiculo` con método virtual puro `getTipo()` | vehiculo.h |
| **Clase Abstracta** | `Documento` con métodos virtuales puros | documento.h |
| **Herencia Simple** | `Auto` y `Moto` heredan de `Vehiculo` | auto.h, moto.h |
| **Herencia Simple** | `Factura` y `Presupuesto` heredan de `Documento` | documento.h |
| **Herencia Múltiple** | `AutoHibrido` hereda de `Auto` e `IElectrico` | autohibrido.h |
| **Composición** | `Vehiculo` contiene un objeto `Motor` | vehiculo.h |
| **Composición** | `OrdenTrabajo` contiene `RepuestoUsado[]` | ordentrabajo.h |
| **Agregación** | `Cliente` tiene vehículos asociados | cliente.h |
| **Polimorfismo** | Punteros `Vehiculo*`, `Documento*` | databasemanager.cpp |
| **Sobrecarga Métodos** | Constructores con diferentes parámetros | todos los modelos |
| **Sobrecarga Operadores** | `==`, `!=`, `<`, `<<` | motor.h, vehiculo.h, etc. |
| **Excepciones** | `ErrorBaseDatos`, `DatoInvalido`, `VehiculoNoEncontrado` | databasemanager.h |
| **Enumeraciones** | Estados de OT, Facturas, Citas, etc. | ordentrabajo.h, etc. |

## 📦 Estructura del Proyecto

```
POOOO/
├── TallerMecanico.pro          # Archivo de proyecto Qt
├── main.cpp                     # Punto de entrada
├── mainwindow.h/cpp/ui          # Ventana principal con pestañas
├── database/
│   └── databasemanager.h/cpp    # Gestión de SQLite y CRUD
├── models/
│   ├── motor.h/cpp              # Clase Motor (Composición)
│   ├── vehiculo.h/cpp           # Clase Base Abstracta
│   ├── auto.h/cpp               # Clase Derivada Auto
│   ├── moto.h/cpp               # Clase Derivada Moto
│   ├── autohibrido.h/cpp        # Herencia Múltiple
│   ├── cliente.h/cpp            # Clase Cliente (Agregación)
│   ├── repuesto.h/cpp           # Inventario de repuestos
│   ├── ordentrabajo.h/cpp       # Órdenes de trabajo
│   ├── documento.h/cpp          # Base para Factura/Presupuesto
│   ├── citaagenda.h/cpp         # Citas del calendario
│   └── historialservicio.h/cpp  # Historial de servicios
└── dialogs/
    ├── clientedialog.*          # Diálogo para clientes
    ├── vehiculodialog.*         # Diálogo para vehículos
    ├── repuestodialog.*         # Diálogo para repuestos
    ├── ordentrabajodialog.*     # Diálogo para órdenes
    └── citadialog.*             # Diálogo para citas
```

## 🛠️ Requisitos

- **Qt 5.15+** o **Qt 6.x** con módulo SQL
- Compilador C++17 (MinGW, MSVC, o GCC)
- **No requiere servidor de base de datos** (SQLite integrado)

## 🚀 Compilación

### Opción 1: Qt Creator (Recomendado)

1. Abre **Qt Creator**
2. File → Open File or Project
3. Selecciona `TallerMecanico.pro`
4. Configura el Kit de compilación
5. Click en **Build** (Ctrl+B)
6. Click en **Run** (Ctrl+R)

### Opción 2: Línea de comandos

```bash
cd C:\Users\damia\Desktop\POOOO
qmake TallerMecanico.pro
mingw32-make
.\release\TallerMecanico.exe
```

## 💾 Esquema de Base de Datos

### Tablas Principales

| Tabla | Descripción |
|-------|-------------|
| `clientes` | Datos de clientes |
| `vehiculos` | Vehículos con FK a clientes |
| `repuestos` | Inventario de repuestos |
| `ordenes_trabajo` | Órdenes de trabajo |
| `repuestos_orden` | Relación OT ↔ Repuestos |
| `facturas` | Facturas emitidas |
| `presupuestos` | Presupuestos |
| `items_documento` | Items de facturas/presupuestos |
| `citas_agenda` | Citas programadas |
| `historial_servicios` | Historial de cada vehículo |

## 🎨 Interfaz de Usuario

La aplicación tiene una interfaz moderna con **6 pestañas**:

1. **👥 Clientes**: Gestión de clientes y sus vehículos
2. **📝 Órdenes**: Órdenes de trabajo activas
3. **📦 Inventario**: Control de repuestos y stock
4. **📅 Agenda**: Calendario con citas programadas
5. **💰 Facturación**: Facturas y presupuestos
6. **📊 Reportes**: Estadísticas y reportes

### Tema Visual
- Fondo gradiente oscuro
- Acentos en cyan (#00d9ff)
- Botones con colores semánticos (verde=agregar, rojo=eliminar)
- Tablas con selección destacada

## 📝 Uso

### Clientes y Vehículos
1. **Agregar Cliente**: Tab Clientes → Click "➕ Agregar"
2. **Agregar Vehículo**: Seleccionar cliente → Click Auto/Moto/Híbrido
3. **Ver Historial**: Seleccionar cliente/vehículo → Click "📜 Historial"

### Órdenes de Trabajo
1. **Nueva OT**: Tab Órdenes → "➕ Nueva OT"
2. **Cambiar Estado**: Seleccionar OT → "🔄 Cambiar Estado"

### Inventario
1. **Agregar Repuesto**: Tab Inventario → "➕ Nuevo"
2. **Ajustar Stock**: Seleccionar repuesto → "📊 Ajustar Stock"
3. Los repuestos con stock crítico se marcan en **rojo**

### Agenda
1. **Nueva Cita**: Tab Agenda → Seleccionar fecha → "➕ Nueva Cita"
2. Las citas del día aparecen en la lista derecha

### Reportes
- **Ingresos del Mes**: Muestra total facturado (pagado)
- **Trabajos Realizados**: OTs completadas y en proceso
- **Stock Crítico**: Lista repuestos bajo mínimo

## ⚠️ Solución de Problemas

### "No se pudo crear/abrir la base de datos SQLite"
- Verifica permisos de escritura en la carpeta del ejecutable
- La BD se crea como `taller_mecanico.db` junto al .exe

### La aplicación no inicia
- Verifica que tienes Qt instalado correctamente
- Comprueba que el kit de compilación es compatible

---

## 👨‍💻 Autor

Proyecto desarrollado para la asignatura de **Programación Orientada a Objetos**.

*Sistema desarrollado con Qt Framework, C++17 y SQLite*
