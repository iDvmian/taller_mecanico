# 🏗️ DIAGRAMA DE ARQUITECTURA (VISUAL)

## CÓMO VER COMO IMAGEN:
1. Ve a: https://mermaid.live/
2. Copia el código del diagrama
3. Se genera automáticamente
4. Descarga como PNG o SVG

---

## ARQUITECTURA EN CAPAS DEL SISTEMA

```mermaid
graph TB
    subgraph "CAPA PRESENTACIÓN - Qt Widgets"
        MW[MainWindow.ui]
        CD[ClienteDialog.ui]
        VD[VehiculoDialog.ui]
        OD[OrdenTrabajoDialog]
        RD[RepuestoDialog]
        FD[FacturaDialog]
        PD[PresupuestoDialog]
        CA[CitaDialog]
    end
    
    subgraph "CAPA CONTROLADOR - Slots/Señales Qt"
        S1[onAgregarCliente]
        S2[onNuevaOrden]
        S3[onNuevaFactura]
        S4[onNuevaCita]
        S5[actualizarTablas]
    end
    
    subgraph "CAPA MODELO - Business Logic"
        M1[Cliente]
        M2[Vehiculo Abstract]
        M3[Auto]
        M4[Moto]
        M5[AutoHibrido]
        M6[Motor]
        M7[OrdenTrabajo]
        M8[Repuesto]
        M9[Factura]
        M10[Presupuesto]
        M11[CitaAgenda]
    end
    
    subgraph "CAPA ACCESO DATOS - Singleton"
        DM[DatabaseManager]
    end
    
    subgraph "BASE DE DATOS - SQLite"
        DB[(taller_mecanico.db)]
    end
    
    %% Relaciones
    MW --> S1
    CD --> S1
    VD --> S2
    OD --> S2
    RD --> S3
    FD --> S3
    PD --> S3
    CA --> S4
    
    S1 --> M1
    S2 --> M2
    S2 --> M7
    S3 --> M8
    S3 --> M9
    S3 --> M10
    S4 --> M11
    S5 --> DM
    
    M1 --> DM
    M2 --> DM
    M3 --> DM
    M4 --> DM
    M5 --> DM
    M7 --> DM
    M8 --> DM
    M9 --> DM
    M10 --> DM
    M11 --> DM
    
    DM --> DB
    
    style DM fill:#ea6f15,color:#fff
    style DB fill:#4a90e2,color:#fff
```

---

## FLUJO DE DATOS - CREAR FACTURA

```mermaid
sequenceDiagram
    actor Usuario
    participant MW as MainWindow
    participant FD as FacturaDialog
    participant F as Factura
    participant DM as DatabaseManager
    participant DB as SQLite DB
    
    Usuario->>MW: Click "Nueva Factura"
    MW->>FD: Abrir diálogo
    FD->>DM: Cargar clientes
    DM->>DB: SELECT clientes
    DB-->>DM: Datos
    DM-->>FD: Lista clientes
    
    FD->>DM: Cargar órdenes
    DM->>DB: SELECT ordenes
    DB-->>DM: Datos
    DM-->>FD: Lista órdenes
    
    Usuario->>FD: Completar datos
    Usuario->>FD: Agregar items
    Usuario->>FD: Click "Guardar"
    
    FD->>F: Crear objeto Factura
    F->>F: Validar datos
    F->>F: Calcular totales
    
    FD->>DM: insertarFactura()
    DM->>DB: BEGIN TRANSACTION
    DM->>DB: INSERT INTO facturas
    DM->>DB: INSERT INTO items_documento
    DM->>DB: COMMIT
    DB-->>DM: ID generado
    DM-->>FD: Éxito
    
    FD-->>MW: Cerrar diálogo
    MW->>MW: actualizarTablaFacturas()
    MW->>DM: obtenerTodasFacturas()
    DM->>DB: SELECT facturas
    DB-->>DM: Datos
    DM-->>MW: Lista actualizada
    MW->>Usuario: Mostrar mensaje éxito
```

---

## FLUJO DE DATOS - REGISTRAR CLIENTE

```mermaid
sequenceDiagram
    actor Usuario
    participant MW as MainWindow
    participant CD as ClienteDialog
    participant C as Cliente
    participant DM as DatabaseManager
    participant DB as SQLite DB
    
    Usuario->>MW: Click "Agregar Cliente"
    MW->>CD: new ClienteDialog()
    CD->>Usuario: Mostrar formulario
    
    Usuario->>CD: Completar datos
    Usuario->>CD: Click "Guardar"
    
    CD->>C: new Cliente(datos)
    CD->>C: validarRut()
    
    alt RUT válido
        C-->>CD: true
        CD->>DM: insertarCliente()
        DM->>DB: INSERT INTO clientes
        
        alt Inserción exitosa
            DB-->>DM: ID generado
            DM-->>CD: true
            CD-->>MW: QDialog::Accepted
            MW->>MW: actualizarTablaClientes()
            MW->>Usuario: "Cliente creado"
        else Error BD
            DB-->>DM: Error
            DM-->>CD: throw ErrorBaseDatos
            CD->>Usuario: Mostrar error
        end
    else RUT inválido
        C-->>CD: false
        CD->>Usuario: "RUT inválido"
    end
```

---

## PATRÓN MVC (Model-View-Controller)

```mermaid
graph LR
    subgraph "VIEW - Vista"
        V1[MainWindow.ui]
        V2[ClienteDialog.ui]
        V3[VehiculoDialog.ui]
        V4[Otros Dialogs]
    end
    
    subgraph "CONTROLLER - Controlador"
        C1[MainWindow.cpp]
        C2[ClienteDialog.cpp]
        C3[VehiculoDialog.cpp]
        C4[Slots/Señales]
    end
    
    subgraph "MODEL - Modelo"
        M1[Cliente]
        M2[Vehiculo]
        M3[Auto/Moto/Híbrido]
        M4[OrdenTrabajo]
        M5[Factura/Presupuesto]
        M6[DatabaseManager]
    end
    
    V1 -.->|Eventos UI| C1
    V2 -.->|Eventos UI| C2
    V3 -.->|Eventos UI| C3
    
    C1 -->|Manipula| M1
    C2 -->|Manipula| M2
    C3 -->|Manipula| M3
    C1 -->|Manipula| M4
    C1 -->|Manipula| M5
    
    C1 -->|Consulta| M6
    C2 -->|Consulta| M6
    C3 -->|Consulta| M6
    
    M6 -->|Actualiza| M1
    M6 -->|Actualiza| M2
    M6 -->|Actualiza| M3
    
    C1 -.->|Actualiza Vista| V1
    C2 -.->|Actualiza Vista| V2
    C3 -.->|Actualiza Vista| V3
    
    style M6 fill:#ea6f15,color:#fff
```

---

## PATRÓN SINGLETON - DatabaseManager

```mermaid
graph TB
    subgraph "PUNTO DE ACCESO ÚNICO"
        I1[MainWindow]
        I2[ClienteDialog]
        I3[VehiculoDialog]
        I4[FacturaDialog]
        I5[Otros...]
    end
    
    subgraph "SINGLETON"
        S[DatabaseManager::getInstance]
        INST[Instancia Única]
    end
    
    subgraph "BASE DE DATOS"
        DB[(SQLite DB)]
    end
    
    I1 -->|getInstance| S
    I2 -->|getInstance| S
    I3 -->|getInstance| S
    I4 -->|getInstance| S
    I5 -->|getInstance| S
    
    S -->|retorna| INST
    INST -->|conecta| DB
    
    style INST fill:#ea6f15,color:#fff
    style S fill:#f39c12,color:#fff
```

---

## JERARQUÍA DE HERENCIA

```mermaid
graph TB
    subgraph "VEHÍCULOS"
        V[Vehiculo Abstract]
        A[Auto]
        M[Moto]
        AH[AutoHibrido]
        IE[IElectrico Interface]
        
        V --> A
        V --> M
        A --> AH
        IE -.->|implementa| AH
    end
    
    subgraph "DOCUMENTOS"
        D[Documento Abstract]
        F[Factura]
        P[Presupuesto]
        
        D --> F
        D --> P
    end
    
    subgraph "EXCEPCIONES"
        EX[std::exception]
        EB[ErrorBaseDatos]
        EV[ErrorValidacion]
        
        EX --> EB
        EX --> EV
    end
    
    style V fill:#e74c3c,color:#fff
    style D fill:#e74c3c,color:#fff
    style IE fill:#9b59b6,color:#fff
    style AH fill:#27ae60,color:#fff
```

---

## COMPOSICIÓN Y AGREGACIÓN

```mermaid
graph LR
    subgraph "COMPOSICIÓN - Motor es PARTE de Vehículo"
        V1[Vehiculo]
        M1[Motor]
        V1 -.->|◆ composición| M1
    end
    
    subgraph "AGREGACIÓN - Cliente TIENE Vehículos"
        C1[Cliente]
        V2[Vehiculo]
        C1 -.->|◇ agregación| V2
    end
    
    style V1 fill:#3498db,color:#fff
    style M1 fill:#e67e22,color:#fff
    style C1 fill:#2ecc71,color:#fff
    style V2 fill:#3498db,color:#fff
```

---

## MÓDULOS DEL SISTEMA

```mermaid
graph TB
    subgraph "MÓDULO CLIENTES"
        MC1[Gestión Clientes]
        MC2[Validación RUT]
        MC3[Historial]
    end
    
    subgraph "MÓDULO VEHÍCULOS"
        MV1[Auto/Moto/Híbrido]
        MV2[Composición Motor]
        MV3[Asociación Cliente]
    end
    
    subgraph "MÓDULO ÓRDENES"
        MO1[Crear Órdenes]
        MO2[Estados]
        MO3[Repuestos Usados]
        MO4[Costos]
    end
    
    subgraph "MÓDULO INVENTARIO"
        MI1[CRUD Repuestos]
        MI2[Control Stock]
        MI3[Stock Crítico]
    end
    
    subgraph "MÓDULO FACTURACIÓN"
        MF1[Facturas]
        MF2[Presupuestos]
        MF3[Items]
        MF4[Pagos]
    end
    
    subgraph "MÓDULO AGENDA"
        MA1[Calendario]
        MA2[Citas]
        MA3[Estados Cita]
    end
    
    MC1 --> MV1
    MV1 --> MO1
    MO1 --> MI1
    MO1 --> MF1
    MV1 --> MA1
```

---

## ESTRUCTURA DE ARCHIVOS

```mermaid
graph TB
    ROOT[POOOO/]
    
    ROOT --> MAIN[main.cpp]
    ROOT --> MW[mainwindow.h/cpp/ui]
    ROOT --> PRO[TallerMecanico.pro]
    ROOT --> RES[resources.qrc]
    
    ROOT --> MODELS[models/]
    ROOT --> DIALOGS[dialogs/]
    ROOT --> DB[database/]
    ROOT --> IMG[images/]
    
    MODELS --> M1[vehiculo.h/cpp]
    MODELS --> M2[auto.h/cpp]
    MODELS --> M3[moto.h/cpp]
    MODELS --> M4[autohibrido.h/cpp]
    MODELS --> M5[motor.h/cpp]
    MODELS --> M6[cliente.h/cpp]
    MODELS --> M7[documento.h/cpp]
    MODELS --> M8[ordentrabajo.h/cpp]
    MODELS --> M9[repuesto.h/cpp]
    MODELS --> M10[citaagenda.h/cpp]
    
    DIALOGS --> D1[clientedialog.h/cpp/ui]
    DIALOGS --> D2[vehiculodialog.h/cpp/ui]
    DIALOGS --> D3[facturadialog.h/cpp]
    DIALOGS --> D4[presupuestodialog.h/cpp]
    DIALOGS --> D5[repuestodialog.h/cpp]
    DIALOGS --> D6[ordentrabajodialog.h/cpp]
    DIALOGS --> D7[citadialog.h/cpp]
    
    DB --> DB1[databasemanager.h/cpp]
    DB --> DB2[taller_mecanico.db]
    
    IMG --> IMG1[Logo.png]
    IMG --> IMG2[icon.ico]
    
    style MODELS fill:#3498db,color:#fff
    style DIALOGS fill:#e74c3c,color:#fff
    style DB fill:#ea6f15,color:#fff
    style IMG fill:#2ecc71,color:#fff
```

---

## FLUJO COMPLETO: ORDEN DE TRABAJO → FACTURA

```mermaid
graph TB
    START([Usuario])
    
    START --> A1[Crear Orden de Trabajo]
    A1 --> A2[Seleccionar Vehículo]
    A2 --> A3[Agregar Descripción]
    A3 --> A4[Estado: PENDIENTE]
    A4 --> B1[Cambiar a EN_PROCESO]
    
    B1 --> C1{Necesita<br/>Repuestos?}
    C1 -->|Sí| C2[Agregar Repuestos]
    C2 --> C3[Actualizar Stock]
    C3 --> C4[Estado: ESPERANDO_REPUESTOS]
    C4 --> C5[Recibir Repuestos]
    C5 --> B2
    C1 -->|No| B2[Realizar Trabajo]
    
    B2 --> D1[Calcular Costos]
    D1 --> D2[Mano de Obra + Repuestos]
    D2 --> D3[Estado: COMPLETADA]
    
    D3 --> E1[Crear Factura]
    E1 --> E2[Agregar Items]
    E2 --> E3[Calcular Total + IVA]
    E3 --> E4[Guardar Factura]
    E4 --> E5[Estado Factura: PENDIENTE]
    
    E5 --> F1{Cliente<br/>Paga?}
    F1 -->|Sí| F2[Registrar Pago]
    F2 --> F3[Estado: PAGADA]
    F3 --> G1[Estado Orden: ENTREGADA]
    
    F1 -->|Parcial| F4[Estado: PARCIAL]
    F1 -->|No| F5[Esperar...]
    
    G1 --> H1[Historial Servicio]
    H1 --> END([Fin])
    
    style A1 fill:#3498db,color:#fff
    style E1 fill:#e74c3c,color:#fff
    style F2 fill:#27ae60,color:#fff
    style G1 fill:#9b59b6,color:#fff
```

---

## TECNOLOGÍAS UTILIZADAS

```mermaid
graph LR
    subgraph "FRONTEND"
        QT[Qt 6.10.1]
        QTW[Qt Widgets]
        QSS[Qt Style Sheets]
    end
    
    subgraph "BACKEND"
        CPP[C++17]
        OOP[POO Avanzada]
        MINGW[MinGW 64-bit]
    end
    
    subgraph "DATABASE"
        SQL[SQLite 3]
        QSQLd[Qt SQL Driver]
    end
    
    subgraph "IDE"
        QTC[Qt Creator]
        QMAKE[qmake]
    end
    
    QT --> QTW
    QTW --> QSS
    CPP --> OOP
    CPP --> MINGW
    SQL --> QSQLd
    QTC --> QMAKE
    
    QTW -.-> CPP
    QSQLd -.-> CPP
    
    style QT fill:#27ae60,color:#fff
    style CPP fill:#e74c3c,color:#fff
    style SQL fill:#3498db,color:#fff
    style QTC fill:#f39c12,color:#fff
```

---

## 📸 GENERAR IMÁGENES PNG/SVG:

### ✅ MÉTODO RECOMENDADO: Mermaid Live
1. **Ir a:** https://mermaid.live/
2. **Copiar** el código Mermaid
3. **Pegar** en el editor
4. **Download PNG** o **Download SVG**

### ✅ VS Code con extensión
1. Instalar: **"Markdown Preview Mermaid Support"**
2. `Ctrl+Shift+V` para vista previa
3. Click derecho → **Copiar imagen**

---

**DIAGRAMAS PROFESIONALES LISTOS** ✅🎨

