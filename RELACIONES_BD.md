# 🔗 Relaciones de Base de Datos - Sistema Taller Mecánico

## 📖 Guía Completa de Relaciones entre Tablas

---

## 🎯 Tipos de Relaciones

### **1:1** (Uno a Uno)
- Una fila de la tabla A se relaciona con **exactamente una** fila de la tabla B
- Ejemplo: Una orden puede generar **una** factura específica

### **1:N** (Uno a Muchos)
- Una fila de la tabla A se relaciona con **varias** filas de la tabla B
- Ejemplo: Un cliente puede tener **varios** vehículos

### **N:M** (Muchos a Muchos)
- Varias filas de la tabla A se relacionan con **varias** filas de la tabla B
- Requiere una **tabla intermedia**
- Ejemplo: Una orden usa varios repuestos, un repuesto se usa en varias órdenes

---

## 📊 Todas las Relaciones del Sistema

### 1️⃣ **CLIENTES ↔ VEHICULOS**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Agregación (el cliente "tiene" vehículos)

┌─────────────┐         ┌──────────────┐
│  CLIENTES   │ 1    N  │  VEHICULOS   │
│             ├─────────┤              │
│ id (PK)     │         │ id (PK)      │
│             │         │ cliente_id   │ ← Foreign Key
└─────────────┘         └──────────────┘
```

**Significado:**
- 👤 **Un cliente** puede tener **múltiples vehículos** (0, 1, 2, 3... N)
- 🚗 **Un vehículo** pertenece a **un solo cliente**

**Ejemplo Real:**
```
Cliente: Juan Pérez (id=1)
├── Vehículo 1: Toyota Corolla (patente ABC-123, cliente_id=1)
├── Vehículo 2: Honda Civic   (patente XYZ-789, cliente_id=1)
└── Vehículo 3: Yamaha MT-07  (patente DEF-456, cliente_id=1)
```

**Cómo funciona:**
- La tabla `vehiculos` tiene la columna `cliente_id` (FK)
- `cliente_id` apunta al `id` de la tabla `clientes`
- Si eliminas un cliente → se eliminan todos sus vehículos (CASCADE)

**SQL para consultar:**
```sql
-- Obtener todos los vehículos de un cliente
SELECT v.* 
FROM vehiculos v
WHERE v.cliente_id = 1;

-- Obtener cliente con sus vehículos
SELECT c.nombre, v.patente, v.modelo
FROM clientes c
LEFT JOIN vehiculos v ON c.id = v.cliente_id
WHERE c.id = 1;
```

---

### 2️⃣ **CLIENTES ↔ ORDENES_TRABAJO**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Asociación

┌─────────────┐         ┌────────────────────┐
│  CLIENTES   │ 1    N  │ ORDENES_TRABAJO    │
│             ├─────────┤                    │
│ id (PK)     │         │ id (PK)            │
│             │         │ cliente_id (FK)    │
└─────────────┘         └────────────────────┘
```

**Significado:**
- 👤 **Un cliente** puede solicitar **múltiples órdenes de trabajo**
- 📝 **Una orden** es solicitada por **un solo cliente**

**Ejemplo Real:**
```
Cliente: María González (id=5)
├── Orden OT-2025-0001: Cambio de aceite (cliente_id=5)
├── Orden OT-2025-0015: Reparación frenos (cliente_id=5)
└── Orden OT-2025-0023: Revisión técnica (cliente_id=5)
```

**SQL:**
```sql
-- Obtener todas las órdenes de un cliente
SELECT o.numero, o.descripcion_problema, o.estado
FROM ordenes_trabajo o
WHERE o.cliente_id = 5;
```

---

### 3️⃣ **VEHICULOS ↔ ORDENES_TRABAJO**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Asociación

┌──────────────┐         ┌────────────────────┐
│  VEHICULOS   │ 1    N  │ ORDENES_TRABAJO    │
│              ├─────────┤                    │
│ id (PK)      │         │ id (PK)            │
│              │         │ vehiculo_id (FK)   │
└──────────────┘         └────────────────────┘
```

**Significado:**
- 🚗 **Un vehículo** puede tener **múltiples órdenes** (historial de reparaciones)
- 📝 **Una orden** es para **un solo vehículo**

**Ejemplo Real:**
```
Vehículo: Toyota Corolla ABC-123 (id=10)
├── OT-2024-0100: Cambio aceite 10,000 km (vehiculo_id=10)
├── OT-2024-0250: Alineación 15,000 km (vehiculo_id=10)
├── OT-2025-0050: Cambio aceite 20,000 km (vehiculo_id=10)
└── OT-2025-0088: Cambio frenos 22,000 km (vehiculo_id=10)
```

**SQL:**
```sql
-- Historial de órdenes de un vehículo
SELECT o.numero, o.fecha_ingreso, o.descripcion_problema
FROM ordenes_trabajo o
WHERE o.vehiculo_id = 10
ORDER BY o.fecha_ingreso DESC;
```

---

### 4️⃣ **ORDENES_TRABAJO ↔ REPUESTOS** (a través de REPUESTOS_ORDEN)

```
RELACIÓN: N:M (Muchos a Muchos)
TIPO: Asociación con tabla intermedia

┌────────────────────┐         ┌──────────────────┐         ┌──────────────┐
│ ORDENES_TRABAJO    │ 1    N  │ REPUESTOS_ORDEN  │ N    1  │  REPUESTOS   │
│                    ├─────────┤  (INTERMEDIA)    ├─────────┤              │
│ id (PK)            │         │ id (PK)          │         │ id (PK)      │
│                    │         │ orden_id (FK)    │         │              │
│                    │         │ repuesto_id (FK) │         │              │
│                    │         │ cantidad         │         │              │
│                    │         │ precio_unitario  │         │              │
└────────────────────┘         └──────────────────┘         └──────────────┘
```

**Significado:**
- 📝 **Una orden** puede usar **múltiples repuestos**
- 📦 **Un repuesto** puede usarse en **múltiples órdenes**
- La tabla `repuestos_orden` guarda: qué repuesto, en qué orden, cuántos, a qué precio

**Ejemplo Real:**
```
Orden: OT-2025-0042 (Cambio de frenos)
├── Repuesto: Pastillas freno (id=15) → cantidad: 1, precio: $25,000
├── Repuesto: Disco freno (id=16) → cantidad: 2, precio: $40,000 c/u
└── Repuesto: Líquido frenos (id=30) → cantidad: 1, precio: $8,000

Repuesto: Filtro de aceite (id=5)
├── Usado en OT-2025-0001
├── Usado en OT-2025-0015
├── Usado en OT-2025-0023
└── Usado en OT-2025-0042
```

**SQL:**
```sql
-- Obtener repuestos usados en una orden
SELECT r.nombre, ro.cantidad, ro.precio_unitario,
       (ro.cantidad * ro.precio_unitario) AS subtotal
FROM repuestos_orden ro
JOIN repuestos r ON ro.repuesto_id = r.id
WHERE ro.orden_id = 42;

-- Obtener órdenes donde se usó un repuesto
SELECT o.numero, ro.cantidad, ro.precio_unitario
FROM repuestos_orden ro
JOIN ordenes_trabajo o ON ro.orden_id = o.id
WHERE ro.repuesto_id = 5;
```

---

### 5️⃣ **CLIENTES ↔ FACTURAS**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Asociación

┌─────────────┐         ┌──────────────┐
│  CLIENTES   │ 1    N  │  FACTURAS    │
│             ├─────────┤              │
│ id (PK)     │         │ id (PK)      │
│             │         │ cliente_id   │ ← FK
└─────────────┘         └──────────────┘
```

**Significado:**
- 👤 **Un cliente** puede tener **múltiples facturas**
- 💰 **Una factura** es para **un solo cliente**

**Ejemplo Real:**
```
Cliente: Pedro Ramírez (id=8)
├── Factura F-2025-000015: $50,000 (Pagada)
├── Factura F-2025-000023: $35,000 (Pendiente)
└── Factura F-2025-000041: $80,000 (Pagada)
```

---

### 6️⃣ **ORDENES_TRABAJO ↔ FACTURAS**

```
RELACIÓN: 1:1 (Uno a Uno) - OPCIONAL
TIPO: Asociación

┌────────────────────┐         ┌──────────────┐
│ ORDENES_TRABAJO    │ 1    1  │  FACTURAS    │
│                    ├─────────┤              │
│ id (PK)            │         │ id (PK)      │
│                    │         │ orden_trabajo_id │ ← FK (opcional)
└────────────────────┘         └──────────────┘
```

**Significado:**
- 📝 **Una orden completada** puede generar **una factura**
- 💰 **Una factura** puede estar asociada a **una orden** (o ser independiente)
- Es opcional porque puedes facturar sin orden o tener órdenes sin facturar

**Ejemplo Real:**
```
Orden: OT-2025-0050 (Completada)
└── genera → Factura: F-2025-000030

Factura: F-2025-000030
└── por servicio de → Orden: OT-2025-0050
```

---

### 7️⃣ **CLIENTES ↔ PRESUPUESTOS**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Asociación

┌─────────────┐         ┌────────────────────┐
│  CLIENTES   │ 1    N  │  PRESUPUESTOS      │
│             ├─────────┤                    │
│ id (PK)     │         │ id (PK)            │
│             │         │ cliente_id (FK)    │
└─────────────┘         └────────────────────┘
```

**Significado:**
- 👤 **Un cliente** puede solicitar **múltiples presupuestos**
- 📋 **Un presupuesto** es para **un solo cliente**

---

### 8️⃣ **PRESUPUESTOS ↔ FACTURAS**

```
RELACIÓN: 1:1 (Uno a Uno) - OPCIONAL
TIPO: Conversión

┌────────────────────┐         ┌──────────────┐
│  PRESUPUESTOS      │ 1    1  │  FACTURAS    │
│                    ├─────────┤              │
│ id (PK)            │         │ id (PK)      │
│ factura_generada_id│ ────→   │              │
└────────────────────┘         └──────────────┘
```

**Significado:**
- 📋 **Un presupuesto aceptado** puede convertirse en **una factura**
- La columna `factura_generada_id` guarda qué factura se generó

**Ejemplo Real:**
```
Presupuesto: P-2025-000010 (Estado: Aceptado)
├── Cliente acepta presupuesto
└── Se genera → Factura: F-2025-000045
    └── Presupuesto marca: factura_generada_id = 45
```

---

### 9️⃣ **FACTURAS ↔ ITEMS_DOCUMENTO**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Composición

┌──────────────┐         ┌────────────────────┐
│  FACTURAS    │ 1    N  │ ITEMS_DOCUMENTO    │
│              ├─────────┤                    │
│ id (PK)      │         │ id (PK)            │
│              │         │ tipo_documento='FACTURA' │
│              │         │ documento_id (FK)  │
└──────────────┘         └────────────────────┘
```

**Significado:**
- 💰 **Una factura** contiene **múltiples ítems/líneas**
- 📄 **Un ítem** pertenece a **una factura** (o presupuesto)

**Ejemplo Real:**
```
Factura: F-2025-000050
├── Item 1: Cambio de aceite - Cantidad: 1 - Precio: $20,000
├── Item 2: Filtro de aceite - Cantidad: 1 - Precio: $8,000
└── Item 3: Mano de obra - Cantidad: 1 - Precio: $15,000
    └── TOTAL: $43,000
```

---

### 🔟 **PRESUPUESTOS ↔ ITEMS_DOCUMENTO**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Composición

┌────────────────┐         ┌────────────────────┐
│ PRESUPUESTOS   │ 1    N  │ ITEMS_DOCUMENTO    │
│                ├─────────┤                    │
│ id (PK)        │         │ id (PK)            │
│                │         │ tipo_documento='PRESUPUESTO' │
│                │         │ documento_id (FK)  │
└────────────────┘         └────────────────────┘
```

**Significado:**
- 📋 **Un presupuesto** contiene **múltiples ítems**
- Igual que facturas pero con `tipo_documento = 'PRESUPUESTO'`

---

### 1️⃣1️⃣ **CLIENTES ↔ CITAS_AGENDA**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Asociación

┌─────────────┐         ┌────────────────┐
│  CLIENTES   │ 1    N  │ CITAS_AGENDA   │
│             ├─────────┤                │
│ id (PK)     │         │ id (PK)        │
│             │         │ cliente_id (FK)│
└─────────────┘         └────────────────┘
```

**Significado:**
- 👤 **Un cliente** puede programar **múltiples citas**
- 📅 **Una cita** es para **un solo cliente**

---

### 1️⃣2️⃣ **VEHICULOS ↔ CITAS_AGENDA**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Asociación

┌──────────────┐         ┌────────────────┐
│  VEHICULOS   │ 1    N  │ CITAS_AGENDA   │
│              ├─────────┤                │
│ id (PK)      │         │ id (PK)        │
│              │         │ vehiculo_id (FK)│
└──────────────┘         └────────────────┘
```

**Significado:**
- 🚗 **Un vehículo** puede tener **múltiples citas** programadas
- 📅 **Una cita** es para **un solo vehículo**

**Ejemplo Real:**
```
Vehículo: Honda Civic XYZ-789
├── Cita 2025-01-15 09:00 - Revisión preventiva
├── Cita 2025-02-20 14:00 - Cambio de aceite
└── Cita 2025-03-15 10:00 - Alineación
```

---

### 1️⃣3️⃣ **VEHICULOS ↔ HISTORIAL_SERVICIOS**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Composición

┌──────────────┐         ┌─────────────────────────┐
│  VEHICULOS   │ 1    N  │ HISTORIAL_SERVICIOS     │
│              ├─────────┤                         │
│ id (PK)      │         │ id (PK)                 │
│              │         │ vehiculo_id (FK)        │
└──────────────┘         └─────────────────────────┘
```

**Significado:**
- 🚗 **Un vehículo** tiene **múltiples registros** en su historial
- 📜 **Un registro de historial** es para **un solo vehículo**
- Guarda todo lo que se le ha hecho al vehículo

**Ejemplo Real:**
```
Vehículo: Mazda 3 (id=25)
├── 2024-05-10 | 10,000 km | Cambio aceite | $30,000
├── 2024-08-15 | 15,000 km | Alineación | $20,000
├── 2024-11-20 | 20,000 km | Cambio aceite | $30,000
└── 2025-01-05 | 22,000 km | Cambio frenos | $80,000
```

---

### 1️⃣4️⃣ **CLIENTES ↔ HISTORIAL_SERVICIOS**

```
RELACIÓN: 1:N (Uno a Muchos)
TIPO: Asociación

┌─────────────┐         ┌─────────────────────────┐
│  CLIENTES   │ 1    N  │ HISTORIAL_SERVICIOS     │
│             ├─────────┤                         │
│ id (PK)     │         │ id (PK)                 │
│             │         │ cliente_id (FK)         │
└─────────────┘         └─────────────────────────┘
```

**Significado:**
- 👤 **Un cliente** tiene **historial** de todos sus servicios
- Agrupa servicios de todos los vehículos del cliente

---

## 🎯 Resumen Visual de Relaciones

```
                        ┌─────────────┐
                        │  CLIENTES   │
                        └──────┬──────┘
                               │
                 ┌─────────────┼─────────────┬─────────────┐
                 │             │             │             │
                 ▼             ▼             ▼             ▼
          ┌──────────┐  ┌────────────┐  ┌─────────┐  ┌──────────┐
          │VEHICULOS │  │  ORDENES   │  │FACTURAS │  │  CITAS   │
          └────┬─────┘  └─────┬──────┘  └─────────┘  └──────────┘
               │              │
               ▼              ▼
          ┌──────────┐  ┌──────────┐
          │HISTORIAL │  │REPUESTOS │
          └──────────┘  │  (N:M)   │
                        └──────────┘
```

---

## 📋 Tabla Resumen

| Relación | Tipo | Cardinalidad | Clave Foránea | ON DELETE |
|----------|------|--------------|---------------|-----------|
| Cliente → Vehículo | 1:N | 1 cliente : N vehículos | vehiculos.cliente_id | CASCADE |
| Cliente → Orden | 1:N | 1 cliente : N órdenes | ordenes.cliente_id | - |
| Vehículo → Orden | 1:N | 1 vehículo : N órdenes | ordenes.vehiculo_id | - |
| Orden ↔ Repuesto | N:M | N órdenes : M repuestos | repuestos_orden | CASCADE |
| Cliente → Factura | 1:N | 1 cliente : N facturas | facturas.cliente_id | - |
| Orden → Factura | 1:1 | 1 orden : 1 factura (opcional) | facturas.orden_trabajo_id | - |
| Cliente → Presupuesto | 1:N | 1 cliente : N presupuestos | presupuestos.cliente_id | - |
| Presupuesto → Factura | 1:1 | 1 presupuesto : 1 factura (opcional) | presupuestos.factura_generada_id | - |
| Factura → Items | 1:N | 1 factura : N items | items.documento_id | - |
| Presupuesto → Items | 1:N | 1 presupuesto : N items | items.documento_id | - |
| Cliente → Cita | 1:N | 1 cliente : N citas | citas.cliente_id | - |
| Vehículo → Cita | 1:N | 1 vehículo : N citas | citas.vehiculo_id | - |
| Vehículo → Historial | 1:N | 1 vehículo : N registros | historial.vehiculo_id | - |
| Cliente → Historial | 1:N | 1 cliente : N registros | historial.cliente_id | - |

---

## 💡 Conceptos Clave

### **Foreign Key (Clave Foránea)**
- Campo que apunta al ID de otra tabla
- Establece la relación entre tablas
- Ejemplo: `vehiculos.cliente_id` → `clientes.id`

### **ON DELETE CASCADE**
- Cuando eliminas un registro padre, se eliminan automáticamente sus hijos
- Ejemplo: Eliminar cliente → elimina sus vehículos

### **Cardinalidad**
- **1:1** = Relación única bilateral
- **1:N** = Un padre, múltiples hijos
- **N:M** = Múltiples en ambos lados (requiere tabla intermedia)

---

**📌 Este documento explica TODAS las relaciones del sistema de forma clara y con ejemplos prácticos.**

