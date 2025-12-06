# DIAGRAMA ENTIDAD-RELACIÓN (ERD) - BASE DE DATOS

## ESQUEMA DE BASE DE DATOS SQLite

```
┌─────────────────────────────┐
│       CLIENTES              │
├─────────────────────────────┤
│ PK  id (INTEGER)            │
│     rut (TEXT) UNIQUE       │
│     nombre (TEXT)           │
│     telefono (TEXT)         │
│     direccion (TEXT)        │
└─────────────────────────────┘
            │ 1
            │
            │ tiene
            │
            │ *
┌───────────┴─────────────────┐
│       VEHICULOS             │
├─────────────────────────────┤
│ PK  id (INTEGER)            │
│ FK  cliente_id (INTEGER) ───┘
│     tipo (TEXT)             │
│     patente (TEXT) UNIQUE   │
│     modelo (TEXT)           │
│     año (INTEGER)           │
│     motor_tipo (TEXT)       │
│     motor_cilindrada (INT)  │
│     motor_potencia (INT)    │
│     motor_combustible (TEXT)│
│     puertas (INTEGER)       │
│     tipo_moto (TEXT)        │
│     nivel_bateria (TEXT)    │
└─────────────────────────────┘
            │ 1
            │
            ├──────────────────┐
            │                  │
            │ *                │ *
┌───────────┴──────────┐  ┌───┴──────────────────┐
│  ORDENES_TRABAJO     │  │  CITAS_AGENDA        │
├──────────────────────┤  ├──────────────────────┤
│ PK id (INTEGER)      │  │ PK id (INTEGER)      │
│ FK vehiculo_id (INT) │  │ FK vehiculo_id (INT) │
│    fecha_ingreso     │  │    fecha_hora_inicio │
│    descripcion (TEXT)│  │    fecha_hora_fin    │
│    estado (INTEGER)  │  │    titulo (TEXT)     │
│    costo_mano_obra   │  │    descripcion       │
│    observaciones     │  │    estado (INTEGER)  │
└──────────────────────┘  └──────────────────────┘
      │ 1                       
      │                         
      │ contiene                
      │                         
      │ *                       
┌─────┴────────────────────┐   
│ REPUESTOS_ORDEN          │   
├──────────────────────────┤   
│ PK id (INTEGER)          │   
│ FK orden_trabajo_id (INT)├───┘
│ FK repuesto_id (INTEGER) │───┐
│    cantidad (INTEGER)    │   │
│    precio_unitario (REAL)│   │
└──────────────────────────┘   │
                               │ *
                               │
                               │ referencia
                               │
                               │ 1
                    ┌──────────┴──────────┐
                    │  REPUESTOS          │
                    ├─────────────────────┤
                    │ PK id (INTEGER)     │
                    │    codigo (TEXT)    │
                    │    nombre (TEXT)    │
                    │    descripcion      │
                    │    precio (REAL)    │
                    │    stock_actual     │
                    │    stock_minimo     │
                    │    categoria (TEXT) │
                    └─────────────────────┘

┌─────────────────────────────────────┐
│       FACTURAS                      │
├─────────────────────────────────────┤
│ PK  id (INTEGER)                    │
│ FK  cliente_id (INTEGER) ───────────┼──┐
│ FK  orden_trabajo_id (INTEGER) *    │  │
│     numero (TEXT) UNIQUE            │  │
│     fecha (TEXT)                    │  │
│     fecha_vencimiento (TEXT)        │  │
│     subtotal (REAL)                 │  │
│     impuesto (REAL)                 │  │
│     descuento (REAL)                │  │
│     estado_pago (INTEGER)           │  │
│     monto_pagado (REAL)             │  │
│     metodo_pago (TEXT)              │  │
│     fecha_pago (TEXT)               │  │
│     observaciones (TEXT)            │  │
└─────────────────────────────────────┘  │
      │ 1                                 │
      │                                   │
      │ tiene                             │
      │                                   │
      │ *                                 │
┌─────┴──────────────────────┐            │
│  ITEMS_DOCUMENTO           │            │
├────────────────────────────┤            │
│ PK id (INTEGER)            │            │
│    tipo_documento (TEXT)   │            │
│    documento_id (INTEGER)  │────────────┘
│    descripcion (TEXT)      │
│    cantidad (INTEGER)      │
│    precio_unitario (REAL)  │
│    subtotal (REAL)         │
└────────────────────────────┘

┌─────────────────────────────────────┐
│       PRESUPUESTOS                  │
├─────────────────────────────────────┤
│ PK  id (INTEGER)                    │
│ FK  cliente_id (INTEGER) ───────────┼──┐
│ FK  orden_trabajo_id (INTEGER) *    │  │
│ FK  factura_generada_id (INTEGER) * │  │
│     numero (TEXT) UNIQUE            │  │
│     fecha (TEXT)                    │  │
│     fecha_vencimiento (TEXT)        │  │
│     subtotal (REAL)                 │  │
│     impuesto (REAL)                 │  │
│     descuento (REAL)                │  │
│     estado (INTEGER)                │  │
│     dias_validez (INTEGER)          │  │
│     observaciones (TEXT)            │  │
└─────────────────────────────────────┘  │
      │ 1                                 │
      │                                   │
      │ tiene                             │
      │                                   │
      │ *                                 │
      └───────────────────────────────────┼──→ ITEMS_DOCUMENTO
                                          │
                                          │
┌─────────────────────────────────────┐  │
│    HISTORIAL_SERVICIO               │  │
├─────────────────────────────────────┤  │
│ PK  id (INTEGER)                    │  │
│ FK  vehiculo_id (INTEGER) ──────────┼──┼──┐
│ FK  orden_trabajo_id (INTEGER) *    │  │  │
│     fecha (TEXT)                    │  │  │
│     tipo_servicio (TEXT)            │  │  │
│     descripcion (TEXT)              │  │  │
│     costo (REAL)                    │  │  │
│     kilometraje (INTEGER)           │  │  │
└─────────────────────────────────────┘  │  │
                                          │  │
                                          │  │
                    ┌─────────────────────┘  │
                    │                        │
                    │                 ┌──────┘
                    │                 │
                    └─────────┬───────┘
                              │
                    CLIENTES (cierra ciclo)
```

## RELACIONES PRINCIPALES

### 1:N (Uno a Muchos)
- **CLIENTES** ──→ **VEHICULOS**
  - Un cliente puede tener muchos vehículos
  
- **VEHICULOS** ──→ **ORDENES_TRABAJO**
  - Un vehículo puede tener muchas órdenes de trabajo
  
- **VEHICULOS** ──→ **CITAS_AGENDA**
  - Un vehículo puede tener muchas citas
  
- **VEHICULOS** ──→ **HISTORIAL_SERVICIO**
  - Un vehículo tiene un historial de servicios
  
- **CLIENTES** ──→ **FACTURAS**
  - Un cliente puede tener muchas facturas
  
- **CLIENTES** ──→ **PRESUPUESTOS**
  - Un cliente puede tener muchos presupuestos

### N:M (Muchos a Muchos)
- **ORDENES_TRABAJO** ←→ **REPUESTOS**
  - Una orden puede usar muchos repuestos
  - Un repuesto puede estar en muchas órdenes
  - **Tabla intermedia:** REPUESTOS_ORDEN

### 1:N Polimórfico
- **FACTURAS/PRESUPUESTOS** ──→ **ITEMS_DOCUMENTO**
  - Tanto facturas como presupuestos tienen items
  - Identificados por tipo_documento ('FACTURA' o 'PRESUPUESTO')

## ÍNDICES Y RESTRICCIONES

### UNIQUE CONSTRAINTS
- `clientes.rut` - Un RUT por cliente
- `vehiculos.patente` - Una patente única por vehículo
- `facturas.numero` - Número de factura único
- `presupuestos.numero` - Número de presupuesto único
- `repuestos.codigo` - Código único por repuesto

### FOREIGN KEYS
```
vehiculos.cliente_id → clientes.id
ordenes_trabajo.vehiculo_id → vehiculos.id
citas_agenda.vehiculo_id → vehiculos.id
repuestos_orden.orden_trabajo_id → ordenes_trabajo.id
repuestos_orden.repuesto_id → repuestos.id
facturas.cliente_id → clientes.id
facturas.orden_trabajo_id → ordenes_trabajo.id (nullable)
presupuestos.cliente_id → clientes.id
presupuestos.orden_trabajo_id → ordenes_trabajo.id (nullable)
presupuestos.factura_generada_id → facturas.id (nullable)
historial_servicio.vehiculo_id → vehiculos.id
historial_servicio.orden_trabajo_id → ordenes_trabajo.id (nullable)
```

## ENUMS EN LA BASE DE DATOS

### Estado Orden de Trabajo (INTEGER)
```
0 = PENDIENTE
1 = EN_PROCESO
2 = ESPERANDO_REPUESTOS
3 = COMPLETADA (error en original, debe ser 4)
4 = COMPLETADA
5 = ENTREGADA
6 = CANCELADA
```

### Estado Factura (INTEGER)
```
0 = PENDIENTE
1 = PAGADA
2 = PARCIAL
3 = VENCIDA
4 = ANULADA
```

### Estado Presupuesto (INTEGER)
```
0 = BORRADOR
1 = ENVIADO
2 = APROBADO
3 = RECHAZADO
4 = VENCIDO
5 = CONVERTIDO
```

### Estado Cita (INTEGER)
```
0 = PROGRAMADA
1 = CONFIRMADA
2 = EN_CURSO
3 = COMPLETADA
4 = CANCELADA
5 = NO_ASISTIO
```

## CONSULTAS SQL IMPORTANTES

### Stock Crítico
```sql
SELECT * FROM repuestos 
WHERE stock_actual <= stock_minimo
ORDER BY (stock_minimo - stock_actual) DESC;
```

### Ingresos del Mes
```sql
SELECT SUM(subtotal + (subtotal * impuesto / 100) - (subtotal * descuento / 100)) 
FROM facturas
WHERE estado_pago = 1  -- PAGADA
AND strftime('%m', fecha) = '05'
AND strftime('%Y', fecha) = '2024';
```

### Órdenes Activas
```sql
SELECT * FROM ordenes_trabajo
WHERE estado IN (0, 1, 2);  -- PENDIENTE, EN_PROCESO, ESPERANDO_REPUESTOS
```

### Facturas Vencidas
```sql
SELECT * FROM facturas
WHERE estado_pago != 1  -- No PAGADA
AND estado_pago != 4  -- No ANULADA
AND date(fecha_vencimiento) < date('now');
```


