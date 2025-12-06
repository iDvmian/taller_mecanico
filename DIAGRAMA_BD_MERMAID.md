# 🗄️ DIAGRAMA DE BASE DE DATOS (VISUAL)

## CÓMO VER COMO IMAGEN:
1. Ve a: https://mermaid.live/
2. Copia el código del diagrama
3. Se genera automáticamente como imagen bonita
4. Descarga como PNG o SVG

---

## DIAGRAMA ENTIDAD-RELACIÓN COMPLETO

```mermaid
erDiagram
    CLIENTES ||--o{ VEHICULOS : "tiene"
    CLIENTES ||--o{ FACTURAS : "recibe"
    CLIENTES ||--o{ PRESUPUESTOS : "recibe"
    
    VEHICULOS ||--o{ ORDENES_TRABAJO : "tiene"
    VEHICULOS ||--o{ CITAS_AGENDA : "programa"
    VEHICULOS ||--o{ HISTORIAL_SERVICIO : "registra"
    
    ORDENES_TRABAJO ||--o{ REPUESTOS_ORDEN : "usa"
    REPUESTOS ||--o{ REPUESTOS_ORDEN : "usado-en"
    
    ORDENES_TRABAJO ||--o| FACTURAS : "genera"
    ORDENES_TRABAJO ||--o| PRESUPUESTOS : "estima"
    ORDENES_TRABAJO ||--o| HISTORIAL_SERVICIO : "registra"
    
    FACTURAS ||--o{ ITEMS_DOCUMENTO : "contiene"
    PRESUPUESTOS ||--o{ ITEMS_DOCUMENTO : "contiene"
    PRESUPUESTOS ||--o| FACTURAS : "convierte-a"
    
    CLIENTES {
        int id PK
        string rut UK "UNIQUE"
        string nombre
        string apellido
        string telefono
        string direccion
    }
    
    VEHICULOS {
        int id PK
        int cliente_id FK
        string tipo "AUTO/MOTO/HIBRIDO"
        string patente UK "UNIQUE"
        string modelo
        int anio
        string motor_tipo
        int motor_cilindrada
        int motor_potencia
        string motor_combustible
        int puertas "NULL si moto"
        string tipo_moto "NULL si auto"
        string nivel_bateria "NULL si no híbrido"
    }
    
    ORDENES_TRABAJO {
        int id PK
        int vehiculo_id FK
        datetime fecha_ingreso
        datetime fecha_entrega
        string descripcion
        int estado "ENUM 0-6"
        real costo_mano_obra
        string observaciones
    }
    
    REPUESTOS {
        int id PK
        string codigo UK "UNIQUE"
        string nombre
        string descripcion
        real precio
        int stock_actual
        int stock_minimo
        string categoria
    }
    
    REPUESTOS_ORDEN {
        int id PK
        int orden_trabajo_id FK
        int repuesto_id FK
        int cantidad
        real precio_unitario
    }
    
    FACTURAS {
        int id PK
        int cliente_id FK
        int orden_trabajo_id FK "NULL"
        string numero UK "UNIQUE"
        datetime fecha
        datetime fecha_vencimiento
        real subtotal
        real impuesto
        real descuento
        int estado_pago "ENUM 0-4"
        real monto_pagado
        string metodo_pago
        datetime fecha_pago
        string observaciones
    }
    
    PRESUPUESTOS {
        int id PK
        int cliente_id FK
        int orden_trabajo_id FK "NULL"
        int factura_generada_id FK "NULL"
        string numero UK "UNIQUE"
        datetime fecha
        datetime fecha_vencimiento
        real subtotal
        real impuesto
        real descuento
        int estado "ENUM 0-5"
        int dias_validez
        string observaciones
    }
    
    ITEMS_DOCUMENTO {
        int id PK
        string tipo_documento "FACTURA/PRESUPUESTO"
        int documento_id FK
        string descripcion
        int cantidad
        real precio_unitario
        real subtotal
    }
    
    CITAS_AGENDA {
        int id PK
        int vehiculo_id FK
        string cliente_nombre
        string vehiculo_patente
        datetime fecha_hora_inicio
        datetime fecha_hora_fin
        string titulo
        string descripcion
        int estado "ENUM 0-5"
    }
    
    HISTORIAL_SERVICIO {
        int id PK
        int vehiculo_id FK
        int orden_trabajo_id FK "NULL"
        datetime fecha
        string tipo_servicio
        string descripcion
        real costo
        int kilometraje
    }
```

---

## RELACIONES DETALLADAS

### 1:N (Uno a Muchos)

```mermaid
erDiagram
    CLIENTES ||--o{ VEHICULOS : "1 cliente N vehículos"
    CLIENTES ||--o{ FACTURAS : "1 cliente N facturas"
    CLIENTES ||--o{ PRESUPUESTOS : "1 cliente N presupuestos"
    VEHICULOS ||--o{ ORDENES_TRABAJO : "1 vehículo N órdenes"
    VEHICULOS ||--o{ CITAS_AGENDA : "1 vehículo N citas"
    
    CLIENTES {
        int id PK
        string rut
        string nombre
    }
    
    VEHICULOS {
        int id PK
        int cliente_id FK
        string patente
    }
    
    ORDENES_TRABAJO {
        int id PK
        int vehiculo_id FK
    }
    
    CITAS_AGENDA {
        int id PK
        int vehiculo_id FK
    }
    
    FACTURAS {
        int id PK
        int cliente_id FK
    }
    
    PRESUPUESTOS {
        int id PK
        int cliente_id FK
    }
```

---

### N:M (Muchos a Muchos)

```mermaid
erDiagram
    ORDENES_TRABAJO }o--o{ REPUESTOS : "N órdenes M repuestos"
    
    ORDENES_TRABAJO ||--o{ REPUESTOS_ORDEN : "tiene"
    REPUESTOS ||--o{ REPUESTOS_ORDEN : "usado-en"
    
    ORDENES_TRABAJO {
        int id PK
        string descripcion
    }
    
    REPUESTOS_ORDEN {
        int id PK
        int orden_trabajo_id FK
        int repuesto_id FK
        int cantidad
        real precio_unitario
    }
    
    REPUESTOS {
        int id PK
        string codigo
        string nombre
        real precio
    }
```

---

## DIAGRAMA POR MÓDULO

### MÓDULO: GESTIÓN DE CLIENTES Y VEHÍCULOS

```mermaid
erDiagram
    CLIENTES ||--o{ VEHICULOS : posee
    
    CLIENTES {
        int id PK
        string rut UK
        string nombre
        string apellido
        string telefono
        string direccion
    }
    
    VEHICULOS {
        int id PK
        int cliente_id FK
        string tipo
        string patente UK
        string modelo
        int anio
        string motor_tipo
        int motor_cilindrada
        int motor_potencia
    }
```

---

### MÓDULO: ÓRDENES DE TRABAJO

```mermaid
erDiagram
    VEHICULOS ||--o{ ORDENES_TRABAJO : tiene
    ORDENES_TRABAJO ||--o{ REPUESTOS_ORDEN : usa
    REPUESTOS ||--o{ REPUESTOS_ORDEN : incluido-en
    
    VEHICULOS {
        int id PK
        string patente
    }
    
    ORDENES_TRABAJO {
        int id PK
        int vehiculo_id FK
        datetime fecha_ingreso
        string descripcion
        int estado
        real costo_mano_obra
    }
    
    REPUESTOS_ORDEN {
        int id PK
        int orden_trabajo_id FK
        int repuesto_id FK
        int cantidad
        real precio_unitario
    }
    
    REPUESTOS {
        int id PK
        string codigo UK
        string nombre
        real precio
        int stock_actual
        int stock_minimo
    }
```

---

### MÓDULO: FACTURACIÓN

```mermaid
erDiagram
    CLIENTES ||--o{ FACTURAS : recibe
    CLIENTES ||--o{ PRESUPUESTOS : solicita
    FACTURAS ||--o{ ITEMS_DOCUMENTO : contiene
    PRESUPUESTOS ||--o{ ITEMS_DOCUMENTO : contiene
    PRESUPUESTOS ||--o| FACTURAS : convierte-a
    ORDENES_TRABAJO ||--o| FACTURAS : genera
    
    CLIENTES {
        int id PK
        string nombre
    }
    
    ORDENES_TRABAJO {
        int id PK
        int vehiculo_id FK
    }
    
    FACTURAS {
        int id PK
        int cliente_id FK
        int orden_trabajo_id FK
        string numero UK
        datetime fecha
        real subtotal
        real impuesto
        int estado_pago
    }
    
    PRESUPUESTOS {
        int id PK
        int cliente_id FK
        int orden_trabajo_id FK
        int factura_generada_id FK
        string numero UK
        datetime fecha
        int estado
    }
    
    ITEMS_DOCUMENTO {
        int id PK
        string tipo_documento
        int documento_id FK
        string descripcion
        int cantidad
        real precio_unitario
    }
```

---

### MÓDULO: AGENDA

```mermaid
erDiagram
    VEHICULOS ||--o{ CITAS_AGENDA : programa
    
    VEHICULOS {
        int id PK
        string patente
        int cliente_id FK
    }
    
    CITAS_AGENDA {
        int id PK
        int vehiculo_id FK
        string cliente_nombre
        datetime fecha_hora_inicio
        datetime fecha_hora_fin
        string titulo
        int estado
    }
```

---

## ENUMS Y ESTADOS

### Estados de Órdenes

```mermaid
stateDiagram-v2
    [*] --> PENDIENTE
    PENDIENTE --> EN_PROCESO
    EN_PROCESO --> ESPERANDO_REPUESTOS
    ESPERANDO_REPUESTOS --> EN_PROCESO
    EN_PROCESO --> COMPLETADA
    COMPLETADA --> ENTREGADA
    ENTREGADA --> [*]
    
    PENDIENTE --> CANCELADA
    EN_PROCESO --> CANCELADA
    ESPERANDO_REPUESTOS --> CANCELADA
    CANCELADA --> [*]
```

---

### Estados de Facturas

```mermaid
stateDiagram-v2
    [*] --> PENDIENTE
    PENDIENTE --> PARCIAL : pago parcial
    PENDIENTE --> PAGADA : pago total
    PARCIAL --> PAGADA : completar pago
    PENDIENTE --> VENCIDA : vencimiento
    PARCIAL --> VENCIDA : vencimiento
    PENDIENTE --> ANULADA
    PARCIAL --> ANULADA
    VENCIDA --> ANULADA
    PAGADA --> [*]
    ANULADA --> [*]
```

---

### Estados de Presupuestos

```mermaid
stateDiagram-v2
    [*] --> BORRADOR
    BORRADOR --> ENVIADO
    ENVIADO --> APROBADO
    ENVIADO --> RECHAZADO
    ENVIADO --> VENCIDO : timeout
    APROBADO --> CONVERTIDO : genera factura
    CONVERTIDO --> [*]
    RECHAZADO --> [*]
    VENCIDO --> [*]
```

---

### Estados de Citas

```mermaid
stateDiagram-v2
    [*] --> PROGRAMADA
    PROGRAMADA --> CONFIRMADA
    CONFIRMADA --> EN_CURSO
    EN_CURSO --> COMPLETADA
    COMPLETADA --> [*]
    
    PROGRAMADA --> CANCELADA
    CONFIRMADA --> CANCELADA
    CONFIRMADA --> NO_ASISTIO
    
    CANCELADA --> [*]
    NO_ASISTIO --> [*]
```

---

## ÍNDICES Y CONSTRAINTS

```mermaid
graph TD
    subgraph "UNIQUE CONSTRAINTS"
        A[clientes.rut]
        B[vehiculos.patente]
        C[repuestos.codigo]
        D[facturas.numero]
        E[presupuestos.numero]
    end
    
    subgraph "FOREIGN KEYS"
        F[vehiculos.cliente_id → clientes.id]
        G[ordenes_trabajo.vehiculo_id → vehiculos.id]
        H[repuestos_orden.orden_trabajo_id → ordenes_trabajo.id]
        I[repuestos_orden.repuesto_id → repuestos.id]
        J[facturas.cliente_id → clientes.id]
        K[presupuestos.cliente_id → clientes.id]
        L[citas_agenda.vehiculo_id → vehiculos.id]
    end
```

---

## ARQUITECTURA DE DATOS

```mermaid
graph TB
    subgraph "CAPA APLICACIÓN"
        A[MainWindow]
        B[Dialogs]
    end
    
    subgraph "CAPA LÓGICA"
        C[DatabaseManager Singleton]
    end
    
    subgraph "CAPA DATOS - SQLite"
        D[(clientes)]
        E[(vehiculos)]
        F[(ordenes_trabajo)]
        G[(repuestos)]
        H[(facturas)]
        I[(presupuestos)]
        J[(citas_agenda)]
    end
    
    A --> C
    B --> C
    C --> D
    C --> E
    C --> F
    C --> G
    C --> H
    C --> I
    C --> J
    
    style C fill:#ea6f15,color:#fff
    style D fill:#4a90e2,color:#fff
    style E fill:#4a90e2,color:#fff
    style F fill:#4a90e2,color:#fff
    style G fill:#4a90e2,color:#fff
    style H fill:#4a90e2,color:#fff
    style I fill:#4a90e2,color:#fff
    style J fill:#4a90e2,color:#fff
```

---

## 📸 CÓMO GENERAR IMÁGENES:

### ✅ Opción 1: Mermaid Live (MÁS FÁCIL)
1. **Ir a:** https://mermaid.live/
2. **Copiar** cualquier bloque de código Mermaid de arriba
3. **Pegar** en el editor
4. Se genera **automáticamente** el diagrama
5. Click **"Download PNG"** o **"Download SVG"**

### ✅ Opción 2: VS Code
1. Instalar extensión: **"Markdown Preview Mermaid Support"**
2. Abrir este archivo en VS Code
3. Presionar `Ctrl+Shift+V` para vista previa
4. Click derecho en el diagrama → **"Copy Image"**

### ✅ Opción 3: GitHub
- Subir este archivo a GitHub
- Se renderiza automáticamente

---

**TODOS LOS DIAGRAMAS SE VEN COMO IMÁGENES PROFESIONALES** ✅🎨

