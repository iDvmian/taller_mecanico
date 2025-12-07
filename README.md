# 🔧 Sistema Taller Mecánico - Qt + SQLite

Sistema completo de gestión de taller mecánico con interfaz gráfica Qt y base de datos **SQLite** (integrada, sin configuración).

[![Qt](https://img.shields.io/badge/Qt-6.10.1-green.svg)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![SQLite](https://img.shields.io/badge/SQLite-3-orange.svg)](https://www.sqlite.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](https://github.com/)

---

## 📑 Tabla de Contenidos

- [Características](#-características)
- [Conceptos POO Implementados](#-conceptos-poo-implementados)
- [Estructura del Proyecto](#-estructura-del-proyecto)
- [Requisitos](#️-requisitos)
- [Inicio Rápido](#-inicio-rápido)
- [Compilación](#-compilación)
- [Base de Datos](#-esquema-de-base-de-datos) → [Diagrama Completo](DIAGRAMA_BD.md)
- [Interfaz de Usuario](#-interfaz-de-usuario)
- [Guía de Uso](#-guía-de-uso)
- [Características Técnicas](#-características-técnicas)
- [Solución de Problemas](#️-solución-de-problemas)
- [Capturas de Pantalla](#-capturas-de-pantalla)
- [Conceptos Avanzados](#-conceptos-avanzados-implementados)
- [Recursos Adicionales](#-recursos-adicionales)
- [Mejoras Futuras](#-mejoras-futuras)
- [Licencia](#-licencia)
- [Contribuciones](#-contribuciones)

---

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
taller_mecanico/
├── TallerMecanico.pro          # Archivo de proyecto Qt
├── main.cpp                     # Punto de entrada
├── mainwindow.h/cpp/ui          # Ventana principal con pestañas
├── README.md                    # Documentación principal
├── RESUMEN_PROYECTO.md          # Resumen ejecutivo del proyecto
├── DIAGRAMA_ARQUITECTURA.md     # Diagrama de arquitectura
├── resources.qrc                # Archivo de recursos Qt
├── database/
│   ├── databasemanager.h        # Interfaz de gestión de BD
│   └── databasemanager.cpp      # Gestión de SQLite y CRUD
├── clases/
│   ├── motor.h/cpp              # Clase Motor (Composición)
│   ├── vehiculo.h/cpp           # Clase Base Abstracta
│   ├── auto.h/cpp               # Clase Derivada Auto
│   ├── moto.h/cpp               # Clase Derivada Moto
│   ├── autohibrido.h/cpp        # Herencia Múltiple
│   ├── cliente.h/cpp            # Clase Cliente (Agregación)
│   ├── repuesto.h/cpp           # Inventario de repuestos
│   ├── ordentrabajo.h/cpp       # Órdenes de trabajo
│   ├── documento.h/cpp          # Base abstracta para documentos
│   ├── citaagenda.h/cpp         # Citas del calendario
│   └── historialservicio.h/cpp  # Historial de servicios
├── ventanas/
│   ├── clientedialog.*          # Ventana para gestión de clientes
│   ├── vehiculodialog.*         # Ventana para vehículos
│   ├── repuestodialog.*         # Ventana para repuestos
│   ├── ordentrabajodialog.*     # Ventana para órdenes de trabajo
│   ├── citadialog.*             # Ventana para citas
│   ├── facturadialog.*          # Ventana para facturas
│   └── presupuestodialog.*      # Ventana para presupuestos
├── imagenes/
│   ├── Logo.png                 # Logo de la aplicación
│   └── icon.ico                 # Icono para Windows
└── build/
    └── Desktop_Qt_*             # Carpeta de compilación
        └── debug/
            └── taller_mecanico.db  # Base de datos SQLite
```

## 🛠️ Requisitos

### Software Necesario
- **Qt 5.15+** o **Qt 6.x** con módulos:
  - Qt Core
  - Qt Widgets
  - Qt SQL (SQLite incluido)
- **Compilador C++17** compatible:
  - Windows: MinGW 64-bit o MSVC 2019+
  - Linux: GCC 7+ o Clang 5+
  - macOS: Clang (Xcode)
- **Qt Creator** (recomendado para desarrollo)

### Características del Sistema
- ✅ **Sin dependencias externas**: SQLite viene integrado con Qt
- ✅ **Multiplataforma**: Windows, Linux, macOS
- ✅ **Base de datos embebida**: No requiere configuración de servidor
- ✅ **Portátil**: El archivo .db contiene todos los datos

## ⚡ Inicio Rápido

### Primera vez que usas el proyecto

1. **Clonar/Descargar** el repositorio
2. **Abrir** `TallerMecanico.pro` en Qt Creator
3. **Configurar** tu kit de compilación (MinGW/MSVC/GCC)
4. **Compilar** con Ctrl+B
5. **Ejecutar** con Ctrl+R
6. La base de datos se crea automáticamente al iniciar

### Datos de Prueba
La aplicación inicia vacía. Puedes:
- Agregar clientes de ejemplo
- Registrar vehículos (Auto, Moto, Auto Híbrido)
- Crear órdenes de trabajo
- Programar citas en el calendario
- Agregar repuestos al inventario

## 🚀 Compilación

### Opción 1: Qt Creator (Recomendado)

1. Abre **Qt Creator**
2. File → Open File or Project
3. Selecciona `TallerMecanico.pro`
4. Configura el Kit de compilación (Desktop Qt 6.x MinGW 64-bit)
5. Click en **Build** (Ctrl+B) o 🔨 Build
6. Click en **Run** (Ctrl+R) o ▶️ Run
7. ¡Listo! La aplicación se ejecutará y creará la BD automáticamente

### Opción 2: Línea de comandos

**Windows (MinGW):**
```bash
cd C:\Users\damia\Desktop\taller_mecanico
qmake TallerMecanico.pro
mingw32-make
.\build\Desktop_Qt_*\debug\TallerMecanico.exe
```

**Linux/Mac:**
```bash
cd ~/Desktop/taller_mecanico
qmake TallerMecanico.pro
make
./TallerMecanico
```

## 💾 Esquema de Base de Datos

### Tablas Principales

| Tabla | Descripción | Relaciones |
|-------|-------------|------------|
| `clientes` | Datos de clientes | → vehiculos, ordenes, facturas |
| `vehiculos` | Vehículos con FK a clientes | ← clientes → ordenes, citas |
| `repuestos` | Inventario de repuestos | → repuestos_orden |
| `ordenes_trabajo` | Órdenes de trabajo | ← clientes, vehiculos → repuestos |
| `repuestos_orden` | Relación OT ↔ Repuestos | ← ordenes ← repuestos |
| `facturas` | Facturas emitidas | ← clientes, ordenes |
| `presupuestos` | Presupuestos | ← clientes → facturas |
| `items_documento` | Items de facturas/presupuestos | ← facturas, presupuestos |
| `citas_agenda` | Citas programadas | ← clientes, vehiculos |
| `historial_servicios` | Historial de cada vehículo | ← clientes, vehiculos, ordenes |

### 📊 Ver Diagramas Completos

**Disponibles en dos formatos:**

1️⃣ **[DIAGRAMA_BD.md](DIAGRAMA_BD.md)** - Documentación técnica completa
   - 🔗 Diagrama ER en formato Mermaid (interactivo)
   - 📋 Especificación detallada de cada tabla (10 tablas)
   - 🔐 Integridad referencial y restricciones
   - 📈 Consultas SQL comunes listas para usar
   - 🔄 Estrategias de backup y mantenimiento

2️⃣ **[DIAGRAMA_BD_VISUAL.md](DIAGRAMA_BD_VISUAL.md)** - Versión visual ASCII
   - 📊 Diagrama visual en formato de texto (ASCII art)
   - 🎨 Fácil visualización sin extensiones
   - 🔄 Flujo de trabajo típico ilustrado
   - 📋 Tabla de estados y códigos
   - 💡 Ejemplo práctico de uso

**Cómo visualizar:**
- **Mermaid**: Abre `DIAGRAMA_BD.md` y presiona `Ctrl+Shift+V` (Vista previa Markdown)
- **ASCII**: Abre `DIAGRAMA_BD_VISUAL.md` directamente en cualquier editor

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

## 📝 Guía de Uso

### 👥 Gestión de Clientes y Vehículos

#### Agregar un Cliente
1. Ve a la pestaña **"Clientes"**
2. Click en **"➕ Agregar Cliente"**
3. Completa el formulario:
   - RUT (formato: 12345678-9, con validación)
   - Nombre completo
   - Teléfono (opcional)
   - Email (validado)
   - Dirección (opcional)
4. Click en **"Guardar"**

#### Registrar un Vehículo
1. **Selecciona un cliente** de la tabla
2. Elige el tipo de vehículo:
   - 🚗 **Auto**: Vehículo estándar a combustión
   - 🏍️ **Moto**: Motocicleta
   - ⚡ **Auto Híbrido**: Con motor eléctrico adicional
3. Completa los datos del vehículo:
   - Patente (validada)
   - Marca y modelo
   - Año
   - Color
   - Datos del motor (cilindrada, potencia, combustible)
   - Si es híbrido: capacidad de batería y autonomía
4. Click en **"Guardar"**

#### Ver Historial
- Selecciona un cliente o vehículo
- Click en **"📜 Ver Historial"**
- Verás todas las órdenes de trabajo y servicios realizados

### 📝 Órdenes de Trabajo

#### Crear una Orden de Trabajo
1. Ve a la pestaña **"Órdenes"**
2. Click en **"➕ Nueva Orden"**
3. Selecciona el vehículo
4. Completa:
   - Descripción del problema
   - Diagnóstico
   - Repuestos a usar (del inventario)
   - Mano de obra
   - Fecha estimada de entrega
5. Estado inicial: **"Pendiente"**

#### Cambiar Estado de OT
Estados disponibles:
- 🔵 **Pendiente**: Recién creada
- 🟡 **En Proceso**: Trabajo iniciado
- 🟢 **Completada**: Trabajo terminado
- 🔴 **Cancelada**: Orden cancelada

Pasos:
1. Selecciona una orden
2. Click en **"🔄 Cambiar Estado"**
3. Elige el nuevo estado
4. Se registra automáticamente en el historial

### 📦 Gestión de Inventario

#### Agregar Repuesto
1. Tab **"Inventario"** → **"➕ Nuevo Repuesto"**
2. Completa:
   - Código (único)
   - Nombre
   - Descripción
   - Precio
   - Stock actual
   - Stock mínimo (para alertas)
3. Click en **"Guardar"**

#### Ajustar Stock
1. Selecciona un repuesto
2. Click en **"📊 Ajustar Stock"**
3. Ingresa:
   - Cantidad a añadir (+) o restar (-)
   - Motivo (venta, compra, devolución)
4. El stock se actualiza automáticamente

**⚠️ Alertas de Stock Crítico:**
- Los repuestos con stock **≤ stock mínimo** se marcan en **ROJO**
- Aparecen en la pestaña **"Reportes"** → **"Stock Crítico"**

### 📅 Agenda y Citas

#### Programar una Cita
1. Ve a **"Agenda"**
2. Selecciona una **fecha** en el calendario
3. Click en **"➕ Nueva Cita"**
4. Completa:
   - Cliente y vehículo
   - Hora de la cita
   - Motivo/Descripción
   - Técnico asignado (opcional)
5. Click en **"Guardar"**

#### Visualización
- **Calendario visual**: Marca los días con citas
- **Lista lateral**: Muestra citas del día seleccionado
- **Estados**: Pendiente, Confirmada, Completada, Cancelada

### 💰 Facturación

#### Generar una Factura
1. Tab **"Facturación"** → **"➕ Nueva Factura"**
2. Asocia a una Orden de Trabajo (opcional)
3. Agrega ítems:
   - Descripción
   - Cantidad
   - Precio unitario
   - Subtotal calculado automáticamente
4. Total: Suma automática + IVA (configurable)
5. Estados: Pendiente, Pagada, Anulada

#### Crear Presupuesto
Similar a factura, pero:
- Estado inicial: **"Borrador"**
- Puede convertirse en factura
- No afecta reportes de ingresos hasta que se facture

### 📊 Reportes y Estadísticas

#### Ingresos del Mes
- Muestra el total de **facturas pagadas** del mes actual
- Desglose por día/semana
- Gráfico de tendencia (si implementado)

#### Trabajos Realizados
- Total de **OTs completadas** en el período
- OTs en proceso
- Tiempo promedio de resolución

#### Stock Crítico
- Lista de repuestos con stock **≤ mínimo**
- Cantidad faltante para alcanzar stock mínimo
- Opción de generar orden de compra

#### Estadísticas Generales
- Clientes registrados
- Vehículos en cartera
- Órdenes activas
- Citas programadas

## 🔧 Características Técnicas

### Arquitectura
- **Patrón MVC**: Separación entre modelos, vistas y lógica
- **Capa de Base de Datos**: Abstracción completa con DatabaseManager
- **Diálogos modales**: Interfaz consistente para todas las operaciones
- **Manejo de errores**: Excepciones personalizadas para cada tipo de error

### Persistencia de Datos
- **Ubicación de BD**: `build/Desktop_Qt_*/debug/taller_mecanico.db`
- **Creación automática**: Tablas se crean al primer inicio
- **Integridad referencial**: Foreign keys y constraints activos
- **Transacciones**: Operaciones atómicas para mantener consistencia

### Validaciones
- ✅ RUT chileno con dígito verificador
- ✅ Patentes en formato válido (LLNNN, NNLLNN)
- ✅ Emails con formato correcto
- ✅ Fechas y horarios de citas sin conflictos
- ✅ Stock no negativo en inventario

## ⚠️ Solución de Problemas

### "No se pudo crear/abrir la base de datos SQLite"
**Posibles causas:**
- Sin permisos de escritura en la carpeta del ejecutable
- Ruta con caracteres especiales o espacios problemáticos
- Archivo de BD corrupto

**Soluciones:**
1. Ejecutar la aplicación con permisos de administrador
2. Mover el ejecutable a una carpeta sin espacios en la ruta
3. Eliminar `taller_mecanico.db` para recrear la BD
4. Verificar que el driver SQLite está disponible

### La aplicación no inicia
**Soluciones:**
- Verifica que tienes Qt instalado correctamente
- Comprueba que el kit de compilación es compatible con tu sistema
- Asegúrate de que las DLLs de Qt estén en el PATH o junto al .exe
- En Windows, instala Visual C++ Redistributable si usas MSVC

### Errores de compilación
**Si faltan headers de Qt:**
```bash
# Verifica que tienes el módulo SQL instalado
qmake -query QT_INSTALL_HEADERS
```

**Si hay errores de enlazado:**
- Limpia el proyecto: Build → Clean All
- Regenera el Makefile: Run qmake
- Compila de nuevo: Build → Build All

### La base de datos no persiste
- Verifica que el archivo `taller_mecanico.db` se crea en la carpeta del ejecutable
- No ejecutes desde carpetas de solo lectura (ej: Program Files)
- Comprueba que la aplicación no está en modo sandbox

---

## 📸 Capturas de Pantalla

La aplicación cuenta con una interfaz moderna y profesional:
- 🎨 **Tema oscuro** con gradientes y acentos cyan
- 📊 **Tablas interactivas** con filas seleccionables
- 🔘 **Botones con iconos** para mejor UX
- 📝 **Formularios validados** con mensajes de error claros
- 📅 **Calendario visual** para gestión de citas
- 💾 **Estado persistente** de pestañas y preferencias

## 🎓 Conceptos Avanzados Implementados

### Manejo de Memoria
- Smart pointers cuando es apropiado
- RAII (Resource Acquisition Is Initialization)
- Destrucción automática de objetos Qt (parent-child)

### Patrones de Diseño
- **Singleton**: DatabaseManager (instancia única)
- **Factory**: Creación polimórfica de vehículos
- **Observer**: Señales y slots de Qt
- **DTO**: Objetos de transferencia para diálogos

### C++ Moderno (C++17)
- `auto` para inferencia de tipos
- Range-based for loops
- Inicialización uniforme
- `nullptr` en lugar de NULL
- `override` y `final` para métodos virtuales

## 📚 Recursos Adicionales

- **[DIAGRAMA_ARQUITECTURA.md](DIAGRAMA_ARQUITECTURA.md)**: Diagrama UML completo del sistema
- **[DIAGRAMA_BD.md](DIAGRAMA_BD.md)**: Esquema técnico completo de base de datos (Mermaid + SQL)
- **[DIAGRAMA_BD_VISUAL.md](DIAGRAMA_BD_VISUAL.md)**: Diagrama visual ASCII de base de datos
- **[RELACIONES_BD.md](RELACIONES_BD.md)**: Guía completa de relaciones entre tablas ⭐
- **[RESUMEN_PROYECTO.md](RESUMEN_PROYECTO.md)**: Resumen ejecutivo y decisiones de diseño
- **Comentarios en código**: Documentación inline en headers y archivos .cpp

## 👨‍💻 Autor

Proyecto desarrollado para la asignatura de **Programación Orientada a Objetos**.

### Tecnologías Utilizadas
- **Framework**: Qt 6.10.1
- **Lenguaje**: C++17
- **Base de Datos**: SQLite 3
- **IDE**: Qt Creator / Visual Studio Code
- **Control de Versiones**: Git

*Sistema completo de gestión empresarial con arquitectura profesional*

## 🚀 Mejoras Futuras

### Funcionalidades Planificadas
- [ ] **Asignación de Mecánicos**: Campo preparado en BD (`mecanico_asignado`)
- [ ] **Recordatorios de Citas**: Campo preparado en BD (`recordatorio_enviado`)
- [ ] **Reportes PDF**: Exportar facturas y reportes a PDF
- [ ] **Gráficos estadísticos**: Charts con Qt Charts module
- [ ] **Backup automático**: Copias de seguridad programadas de la BD
- [ ] **Usuarios y permisos**: Sistema de login con roles (admin, técnico, recepción)
- [ ] **Notificaciones**: Alertas de citas próximas, stock bajo, pagos pendientes
- [ ] **Búsqueda avanzada**: Filtros múltiples en todas las tablas
- [ ] **Historial de cambios**: Auditoría de modificaciones
- [ ] **API REST**: Para integración con sistemas externos
- [ ] **Modo oscuro/claro**: Selector de tema
- [ ] **Multi-idioma**: Soporte para inglés y español

### Optimizaciones Técnicas
- [ ] **Índices en BD**: Para consultas más rápidas
- [ ] **Paginación**: Para tablas con muchos registros
- [ ] **Cache de consultas**: Reducir accesos a BD
- [ ] **Lazy loading**: Cargar datos bajo demanda
- [ ] **Pruebas unitarias**: Test coverage con Qt Test
- [ ] **Documentación Doxygen**: API docs autogenerada

## 📄 Licencia

Este proyecto es de código abierto con fines educativos.

**Uso permitido:**
- ✅ Uso académico y educativo
- ✅ Modificación y extensión
- ✅ Uso como base para proyectos personales

**Restricciones:**
- ❌ No usar con fines comerciales sin autorización
- ❌ No redistribuir sin dar crédito al autor

## 🤝 Contribuciones

Si deseas contribuir al proyecto:

1. **Fork** el repositorio
2. Crea una **rama** para tu feature (`git checkout -b feature/nueva-funcionalidad`)
3. **Commit** tus cambios (`git commit -m 'Agrega nueva funcionalidad'`)
4. **Push** a la rama (`git push origin feature/nueva-funcionalidad`)
5. Abre un **Pull Request**

### Guías de Contribución
- Sigue el estilo de código existente
- Comenta funciones complejas
- Actualiza la documentación si es necesario
- Prueba tus cambios antes de hacer commit

## 📞 Soporte

Si encuentras algún bug o tienes sugerencias:

- **Issues**: Abre un issue en GitHub
- **Email**: Contacta al autor para consultas específicas
- **Documentación**: Revisa DIAGRAMA_ARQUITECTURA.md y RESUMEN_PROYECTO.md

---

## ⭐ Agradecimientos

- **Qt Framework**: Por proveer herramientas robustas para desarrollo
- **SQLite**: Por la base de datos embebida más confiable
- **Comunidad Qt**: Por la documentación y ejemplos

---

**Última actualización**: Diciembre 2025  
**Versión**: 1.0.0  
**Estado**: ✅ Completado y funcional
