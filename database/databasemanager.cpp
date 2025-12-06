#include "databasemanager.h"
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() 
    : host(""), port(0), databaseName("taller_mecanico.db"),
      username(""), password("") {}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = new DatabaseManager();
    }
    return instance;
}

// ==========================================
// CONEXIÓN SQLITE
// ==========================================
bool DatabaseManager::connect(const QString &host, int port, 
                               const QString &dbName, const QString &user, 
                               const QString &pass) {
    Q_UNUSED(host);
    Q_UNUSED(port);
    Q_UNUSED(dbName);
    Q_UNUSED(user);
    Q_UNUSED(pass);

    // Usar driver SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    
    // Ruta del archivo de base de datos
    QString dbPath = QCoreApplication::applicationDirPath() + "/taller_mecanico.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Error al abrir SQLite:" << db.lastError().text();
        return false;
    }

    qDebug() << "✅ Conexión exitosa a SQLite";
    qDebug() << "📁 Base de datos:" << dbPath;
    createTables();
    return true;
}

void DatabaseManager::disconnect() {
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::isConnected() const {
    return db.isOpen();
}

void DatabaseManager::createTables() {
    QSqlQuery query;

    // Habilitar foreign keys en SQLite
    query.exec("PRAGMA foreign_keys = ON");

    // Tabla Clientes
    QString createClientes = R"(
        CREATE TABLE IF NOT EXISTS clientes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            rut TEXT UNIQUE NOT NULL,
            nombre TEXT NOT NULL,
            apellido TEXT NOT NULL,
            telefono TEXT,
            direccion TEXT
        )
    )";
    if (!query.exec(createClientes)) {
        qDebug() << "Error creando tabla clientes:" << query.lastError().text();
    }

    // Tabla Vehículos
    QString createVehiculos = R"(
        CREATE TABLE IF NOT EXISTS vehiculos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            patente TEXT UNIQUE NOT NULL,
            modelo TEXT NOT NULL,
            anio TEXT,
            motor_serie TEXT,
            motor_cc INTEGER,
            tipo TEXT NOT NULL,
            puertas INTEGER DEFAULT 0,
            tiene_cajon INTEGER DEFAULT 0,
            porcentaje_bateria INTEGER DEFAULT 0,
            cliente_id INTEGER REFERENCES clientes(id) ON DELETE CASCADE
        )
    )";
    if (!query.exec(createVehiculos)) {
        qDebug() << "Error creando tabla vehiculos:" << query.lastError().text();
    }

    // Tabla Repuestos (Inventario)
    QString createRepuestos = R"(
        CREATE TABLE IF NOT EXISTS repuestos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            codigo TEXT UNIQUE NOT NULL,
            nombre TEXT NOT NULL,
            descripcion TEXT,
            categoria TEXT,
            precio_compra REAL DEFAULT 0,
            precio_venta REAL DEFAULT 0,
            stock_actual INTEGER DEFAULT 0,
            stock_minimo INTEGER DEFAULT 5
        )
    )";
    if (!query.exec(createRepuestos)) {
        qDebug() << "Error creando tabla repuestos:" << query.lastError().text();
    }

    // Tabla Órdenes de Trabajo
    QString createOrdenes = R"(
        CREATE TABLE IF NOT EXISTS ordenes_trabajo (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            numero TEXT UNIQUE NOT NULL,
            cliente_id INTEGER REFERENCES clientes(id),
            vehiculo_id INTEGER REFERENCES vehiculos(id),
            descripcion_problema TEXT,
            diagnostico TEXT,
            trabajo_realizado TEXT,
            estado INTEGER DEFAULT 0,
            fecha_ingreso TEXT,
            fecha_estimada_entrega TEXT,
            fecha_entrega TEXT,
            costo_mano_obra REAL DEFAULT 0,
            costo_repuestos REAL DEFAULT 0,
            descuento REAL DEFAULT 0,
            observaciones TEXT,
            mecanico_asignado INTEGER DEFAULT 0
        )
    )";
    if (!query.exec(createOrdenes)) {
        qDebug() << "Error creando tabla ordenes_trabajo:" << query.lastError().text();
    }

    // Tabla intermedia Repuestos usados en OT
    QString createRepuestosOrden = R"(
        CREATE TABLE IF NOT EXISTS repuestos_orden (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            orden_id INTEGER REFERENCES ordenes_trabajo(id) ON DELETE CASCADE,
            repuesto_id INTEGER REFERENCES repuestos(id),
            cantidad INTEGER,
            precio_unitario REAL
        )
    )";
    if (!query.exec(createRepuestosOrden)) {
        qDebug() << "Error creando tabla repuestos_orden:" << query.lastError().text();
    }

    // Tabla Facturas
    QString createFacturas = R"(
        CREATE TABLE IF NOT EXISTS facturas (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            numero TEXT UNIQUE NOT NULL,
            cliente_id INTEGER REFERENCES clientes(id),
            orden_trabajo_id INTEGER,
            fecha TEXT,
            fecha_vencimiento TEXT,
            subtotal REAL DEFAULT 0,
            impuesto REAL DEFAULT 19,
            descuento REAL DEFAULT 0,
            estado_pago INTEGER DEFAULT 0,
            monto_pagado REAL DEFAULT 0,
            fecha_pago TEXT,
            metodo_pago TEXT,
            observaciones TEXT
        )
    )";
    if (!query.exec(createFacturas)) {
        qDebug() << "Error creando tabla facturas:" << query.lastError().text();
    }

    // Tabla Presupuestos
    QString createPresupuestos = R"(
        CREATE TABLE IF NOT EXISTS presupuestos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            numero TEXT UNIQUE NOT NULL,
            cliente_id INTEGER REFERENCES clientes(id),
            orden_trabajo_id INTEGER,
            fecha TEXT,
            fecha_vencimiento TEXT,
            subtotal REAL DEFAULT 0,
            impuesto REAL DEFAULT 19,
            descuento REAL DEFAULT 0,
            estado INTEGER DEFAULT 0,
            dias_validez INTEGER DEFAULT 15,
            factura_generada_id INTEGER,
            observaciones TEXT
        )
    )";
    if (!query.exec(createPresupuestos)) {
        qDebug() << "Error creando tabla presupuestos:" << query.lastError().text();
    }

    // Tabla Items de Documento (para facturas y presupuestos)
    QString createItems = R"(
        CREATE TABLE IF NOT EXISTS items_documento (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            tipo_documento TEXT,
            documento_id INTEGER,
            descripcion TEXT,
            cantidad INTEGER,
            precio_unitario REAL,
            subtotal REAL
        )
    )";
    if (!query.exec(createItems)) {
        qDebug() << "Error creando tabla items_documento:" << query.lastError().text();
    }

    // Tabla Citas/Agenda
    QString createCitas = R"(
        CREATE TABLE IF NOT EXISTS citas_agenda (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            cliente_id INTEGER REFERENCES clientes(id),
            vehiculo_id INTEGER REFERENCES vehiculos(id),
            orden_trabajo_id INTEGER,
            titulo TEXT,
            descripcion TEXT,
            tipo INTEGER DEFAULT 0,
            estado INTEGER DEFAULT 0,
            fecha_hora_inicio TEXT,
            fecha_hora_fin TEXT,
            duracion_minutos INTEGER DEFAULT 60,
            color TEXT,
            recordatorio_enviado INTEGER DEFAULT 0,
            notas TEXT
        )
    )";
    if (!query.exec(createCitas)) {
        qDebug() << "Error creando tabla citas_agenda:" << query.lastError().text();
    }

    // Tabla Historial de Servicios
    QString createHistorial = R"(
        CREATE TABLE IF NOT EXISTS historial_servicios (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            vehiculo_id INTEGER REFERENCES vehiculos(id),
            cliente_id INTEGER REFERENCES clientes(id),
            orden_trabajo_id INTEGER,
            tipo_servicio INTEGER,
            descripcion TEXT,
            trabajo_realizado TEXT,
            kilometraje INTEGER,
            fecha TEXT,
            costo_total REAL,
            repuestos_utilizados TEXT,
            observaciones TEXT,
            proximo_servicio_km INTEGER,
            proximo_servicio_fecha TEXT,
            tecnico_responsable TEXT
        )
    )";
    if (!query.exec(createHistorial)) {
        qDebug() << "Error creando tabla historial_servicios:" << query.lastError().text();
    }

    qDebug() << "✅ Todas las tablas creadas correctamente";
}

// ==========================================
// CRUD CLIENTES
// ==========================================
bool DatabaseManager::insertarCliente(Cliente &cliente) {
    if (!Cliente::validarRut(cliente.getRut())) {
        throw DatoInvalido("El RUT es muy corto (mínimo 8 caracteres).");
    }

    if (existeClienteRut(cliente.getRut())) {
        throw DatoInvalido("Ya existe un cliente con ese RUT.");
    }

    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO clientes (rut, nombre, apellido, telefono, direccion)
        VALUES (:rut, :nombre, :apellido, :telefono, :direccion)
    )");

    query.bindValue(":rut", cliente.getRut());
    query.bindValue(":nombre", cliente.getNombre());
    query.bindValue(":apellido", cliente.getApellido());
    query.bindValue(":telefono", cliente.getTelefono());
    query.bindValue(":direccion", cliente.getDireccion());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }

    cliente.setId(query.lastInsertId().toInt());
    return true;
}

bool DatabaseManager::actualizarCliente(const Cliente &cliente) {
    QSqlQuery query;
    query.prepare(R"(
        UPDATE clientes SET
            rut = :rut,
            nombre = :nombre,
            apellido = :apellido,
            telefono = :telefono,
            direccion = :direccion
        WHERE id = :id
    )");

    query.bindValue(":id", cliente.getId());
    query.bindValue(":rut", cliente.getRut());
    query.bindValue(":nombre", cliente.getNombre());
    query.bindValue(":apellido", cliente.getApellido());
    query.bindValue(":telefono", cliente.getTelefono());
    query.bindValue(":direccion", cliente.getDireccion());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }

    return query.numRowsAffected() > 0;
}

bool DatabaseManager::eliminarCliente(int clienteId) {
    QSqlQuery query;
    query.prepare("DELETE FROM clientes WHERE id = :id");
    query.bindValue(":id", clienteId);

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }

    if (query.numRowsAffected() == 0) {
        throw DatoInvalido("Cliente no encontrado.");
    }

    return true;
}

Cliente DatabaseManager::obtenerCliente(int clienteId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM clientes WHERE id = :id");
    query.bindValue(":id", clienteId);

    if (!query.exec() || !query.next()) {
        throw DatoInvalido("Cliente no encontrado.");
    }

    Cliente cliente;
    cliente.setId(query.value("id").toInt());
    cliente.setRut(query.value("rut").toString());
    cliente.setNombre(query.value("nombre").toString());
    cliente.setApellido(query.value("apellido").toString());
    cliente.setTelefono(query.value("telefono").toString());
    cliente.setDireccion(query.value("direccion").toString());

    return cliente;
}

Cliente DatabaseManager::obtenerClientePorRut(const QString &rut) {
    QSqlQuery query;
    query.prepare("SELECT * FROM clientes WHERE rut = :rut");
    query.bindValue(":rut", rut);

    if (!query.exec() || !query.next()) {
        throw DatoInvalido("Cliente no encontrado.");
    }

    Cliente cliente;
    cliente.setId(query.value("id").toInt());
    cliente.setRut(query.value("rut").toString());
    cliente.setNombre(query.value("nombre").toString());
    cliente.setApellido(query.value("apellido").toString());
    cliente.setTelefono(query.value("telefono").toString());
    cliente.setDireccion(query.value("direccion").toString());

    return cliente;
}

QVector<Cliente> DatabaseManager::obtenerTodosClientes() {
    QVector<Cliente> clientes;
    QSqlQuery query("SELECT * FROM clientes ORDER BY apellido, nombre");

    while (query.next()) {
        Cliente cliente;
        cliente.setId(query.value("id").toInt());
        cliente.setRut(query.value("rut").toString());
        cliente.setNombre(query.value("nombre").toString());
        cliente.setApellido(query.value("apellido").toString());
        cliente.setTelefono(query.value("telefono").toString());
        cliente.setDireccion(query.value("direccion").toString());
        clientes.append(cliente);
    }

    return clientes;
}

bool DatabaseManager::existeClienteRut(const QString &rut) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM clientes WHERE rut = :rut");
    query.bindValue(":rut", rut);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

// ==========================================
// CRUD VEHÍCULOS
// ==========================================
bool DatabaseManager::insertarVehiculo(Vehiculo *vehiculo, int clienteId) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO vehiculos (patente, modelo, anio, motor_serie, motor_cc, tipo,
                               puertas, tiene_cajon, porcentaje_bateria, cliente_id)
        VALUES (:patente, :modelo, :anio, :motor_serie, :motor_cc, :tipo,
                :puertas, :tiene_cajon, :porcentaje_bateria, :cliente_id)
    )");

    query.bindValue(":patente", vehiculo->getPatente());
    query.bindValue(":modelo", vehiculo->getModelo());
    query.bindValue(":anio", vehiculo->getAnio());
    query.bindValue(":motor_serie", vehiculo->getMotor().getNumeroSerie());
    query.bindValue(":motor_cc", vehiculo->getMotor().getCilindrada());
    query.bindValue(":tipo", vehiculo->getTipo());
    query.bindValue(":cliente_id", clienteId);

    // Valores específicos según tipo
    if (Auto *autoVeh = dynamic_cast<Auto*>(vehiculo)) {
        query.bindValue(":puertas", autoVeh->getPuertas());
        query.bindValue(":tiene_cajon", 0);

        if (AutoHibrido *hibrido = dynamic_cast<AutoHibrido*>(vehiculo)) {
            query.bindValue(":porcentaje_bateria", hibrido->getPorcentajeBateria());
        } else {
            query.bindValue(":porcentaje_bateria", 0);
        }
    } else if (Moto *moto = dynamic_cast<Moto*>(vehiculo)) {
        query.bindValue(":puertas", 0);
        query.bindValue(":tiene_cajon", moto->getTieneCajon() ? 1 : 0);
        query.bindValue(":porcentaje_bateria", 0);
    } else {
        query.bindValue(":puertas", 0);
        query.bindValue(":tiene_cajon", 0);
        query.bindValue(":porcentaje_bateria", 0);
    }

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }

    vehiculo->setId(query.lastInsertId().toInt());
    vehiculo->setClienteId(clienteId);
    return true;
}

bool DatabaseManager::eliminarVehiculo(int vehiculoId) {
    QSqlQuery query;
    query.prepare("DELETE FROM vehiculos WHERE id = :id");
    query.bindValue(":id", vehiculoId);

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }

    if (query.numRowsAffected() == 0) {
        throw VehiculoNoEncontrado();
    }

    return true;
}

QVector<std::shared_ptr<Vehiculo>> DatabaseManager::obtenerVehiculosCliente(int clienteId) {
    QVector<std::shared_ptr<Vehiculo>> vehiculos;
    QSqlQuery query;
    query.prepare("SELECT * FROM vehiculos WHERE cliente_id = :cliente_id");
    query.bindValue(":cliente_id", clienteId);

    if (!query.exec()) {
        return vehiculos;
    }

    while (query.next()) {
        QString tipo = query.value("tipo").toString();
        std::shared_ptr<Vehiculo> vehiculo;

        if (tipo == "AUTO") {
            auto autoVeh = std::make_shared<Auto>(
                query.value("patente").toString(),
                query.value("modelo").toString(),
                query.value("anio").toString(),
                query.value("motor_serie").toString(),
                query.value("motor_cc").toInt(),
                query.value("puertas").toInt()
            );
            vehiculo = autoVeh;
        } else if (tipo == "MOTO") {
            auto moto = std::make_shared<Moto>(
                query.value("patente").toString(),
                query.value("modelo").toString(),
                query.value("anio").toString(),
                query.value("motor_serie").toString(),
                query.value("motor_cc").toInt(),
                query.value("tiene_cajon").toBool()
            );
            vehiculo = moto;
        } else if (tipo == "HIBRIDO") {
            auto hibrido = std::make_shared<AutoHibrido>(
                query.value("patente").toString(),
                query.value("modelo").toString(),
                query.value("anio").toString(),
                query.value("motor_serie").toString(),
                query.value("motor_cc").toInt(),
                query.value("puertas").toInt(),
                query.value("porcentaje_bateria").toInt()
            );
            vehiculo = hibrido;
        }

        if (vehiculo) {
            vehiculo->setId(query.value("id").toInt());
            vehiculo->setClienteId(clienteId);
            vehiculos.append(vehiculo);
        }
    }

    return vehiculos;
}

QVector<std::shared_ptr<Vehiculo>> DatabaseManager::obtenerTodosVehiculos() {
    QVector<std::shared_ptr<Vehiculo>> vehiculos;
    QSqlQuery query("SELECT * FROM vehiculos");

    while (query.next()) {
        QString tipo = query.value("tipo").toString();
        std::shared_ptr<Vehiculo> vehiculo;

        if (tipo == "AUTO") {
            auto autoVeh = std::make_shared<Auto>(
                query.value("patente").toString(),
                query.value("modelo").toString(),
                query.value("anio").toString(),
                query.value("motor_serie").toString(),
                query.value("motor_cc").toInt(),
                query.value("puertas").toInt()
            );
            vehiculo = autoVeh;
        } else if (tipo == "MOTO") {
            auto moto = std::make_shared<Moto>(
                query.value("patente").toString(),
                query.value("modelo").toString(),
                query.value("anio").toString(),
                query.value("motor_serie").toString(),
                query.value("motor_cc").toInt(),
                query.value("tiene_cajon").toBool()
            );
            vehiculo = moto;
        } else if (tipo == "HIBRIDO") {
            auto hibrido = std::make_shared<AutoHibrido>(
                query.value("patente").toString(),
                query.value("modelo").toString(),
                query.value("anio").toString(),
                query.value("motor_serie").toString(),
                query.value("motor_cc").toInt(),
                query.value("puertas").toInt(),
                query.value("porcentaje_bateria").toInt()
            );
            vehiculo = hibrido;
        }

        if (vehiculo) {
            vehiculo->setId(query.value("id").toInt());
            vehiculo->setClienteId(query.value("cliente_id").toInt());
            vehiculos.append(vehiculo);
        }
    }

    return vehiculos;
}

QString DatabaseManager::getLastError() const {
    return db.lastError().text();
}

// ==========================================
// CRUD REPUESTOS (INVENTARIO)
// ==========================================
bool DatabaseManager::insertarRepuesto(Repuesto &repuesto) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO repuestos (codigo, nombre, descripcion, categoria, 
                               precio_compra, precio_venta, stock_actual, stock_minimo)
        VALUES (:codigo, :nombre, :descripcion, :categoria,
                :precio_compra, :precio_venta, :stock_actual, :stock_minimo)
    )");
    query.bindValue(":codigo", repuesto.getCodigo());
    query.bindValue(":nombre", repuesto.getNombre());
    query.bindValue(":descripcion", repuesto.getDescripcion());
    query.bindValue(":categoria", repuesto.getCategoria());
    query.bindValue(":precio_compra", repuesto.getPrecioCompra());
    query.bindValue(":precio_venta", repuesto.getPrecioVenta());
    query.bindValue(":stock_actual", repuesto.getStockActual());
    query.bindValue(":stock_minimo", repuesto.getStockMinimo());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    repuesto.setId(query.lastInsertId().toInt());
    return true;
}

bool DatabaseManager::actualizarRepuesto(const Repuesto &repuesto) {
    QSqlQuery query;
    query.prepare(R"(
        UPDATE repuestos SET codigo = :codigo, nombre = :nombre, descripcion = :descripcion,
               categoria = :categoria, precio_compra = :precio_compra, precio_venta = :precio_venta,
               stock_actual = :stock_actual, stock_minimo = :stock_minimo
        WHERE id = :id
    )");
    query.bindValue(":id", repuesto.getId());
    query.bindValue(":codigo", repuesto.getCodigo());
    query.bindValue(":nombre", repuesto.getNombre());
    query.bindValue(":descripcion", repuesto.getDescripcion());
    query.bindValue(":categoria", repuesto.getCategoria());
    query.bindValue(":precio_compra", repuesto.getPrecioCompra());
    query.bindValue(":precio_venta", repuesto.getPrecioVenta());
    query.bindValue(":stock_actual", repuesto.getStockActual());
    query.bindValue(":stock_minimo", repuesto.getStockMinimo());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    return query.numRowsAffected() > 0;
}

bool DatabaseManager::eliminarRepuesto(int repuestoId) {
    QSqlQuery query;
    query.prepare("DELETE FROM repuestos WHERE id = :id");
    query.bindValue(":id", repuestoId);
    return query.exec();
}

Repuesto DatabaseManager::obtenerRepuesto(int repuestoId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM repuestos WHERE id = :id");
    query.bindValue(":id", repuestoId);

    Repuesto repuesto;
    if (query.exec() && query.next()) {
        repuesto.setId(query.value("id").toInt());
        repuesto.setCodigo(query.value("codigo").toString());
        repuesto.setNombre(query.value("nombre").toString());
        repuesto.setDescripcion(query.value("descripcion").toString());
        repuesto.setCategoria(query.value("categoria").toString());
        repuesto.setPrecioCompra(query.value("precio_compra").toDouble());
        repuesto.setPrecioVenta(query.value("precio_venta").toDouble());
        repuesto.setStockActual(query.value("stock_actual").toInt());
        repuesto.setStockMinimo(query.value("stock_minimo").toInt());
    }
    return repuesto;
}

QVector<Repuesto> DatabaseManager::obtenerTodosRepuestos() {
    QVector<Repuesto> repuestos;
    QSqlQuery query("SELECT * FROM repuestos ORDER BY nombre");

    while (query.next()) {
        Repuesto repuesto;
        repuesto.setId(query.value("id").toInt());
        repuesto.setCodigo(query.value("codigo").toString());
        repuesto.setNombre(query.value("nombre").toString());
        repuesto.setDescripcion(query.value("descripcion").toString());
        repuesto.setCategoria(query.value("categoria").toString());
        repuesto.setPrecioCompra(query.value("precio_compra").toDouble());
        repuesto.setPrecioVenta(query.value("precio_venta").toDouble());
        repuesto.setStockActual(query.value("stock_actual").toInt());
        repuesto.setStockMinimo(query.value("stock_minimo").toInt());
        repuestos.append(repuesto);
    }
    return repuestos;
}

QVector<Repuesto> DatabaseManager::obtenerRepuestosStockCritico() {
    QVector<Repuesto> repuestos;
    QSqlQuery query("SELECT * FROM repuestos WHERE stock_actual <= stock_minimo ORDER BY stock_actual");

    while (query.next()) {
        Repuesto repuesto;
        repuesto.setId(query.value("id").toInt());
        repuesto.setCodigo(query.value("codigo").toString());
        repuesto.setNombre(query.value("nombre").toString());
        repuesto.setDescripcion(query.value("descripcion").toString());
        repuesto.setCategoria(query.value("categoria").toString());
        repuesto.setPrecioCompra(query.value("precio_compra").toDouble());
        repuesto.setPrecioVenta(query.value("precio_venta").toDouble());
        repuesto.setStockActual(query.value("stock_actual").toInt());
        repuesto.setStockMinimo(query.value("stock_minimo").toInt());
        repuestos.append(repuesto);
    }
    return repuestos;
}

bool DatabaseManager::actualizarStock(int repuestoId, int cantidad, bool esIngreso) {
    QString sql = esIngreso 
        ? "UPDATE repuestos SET stock_actual = stock_actual + :cantidad WHERE id = :id"
        : "UPDATE repuestos SET stock_actual = stock_actual - :cantidad WHERE id = :id AND stock_actual >= :cantidad";
    
    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":cantidad", cantidad);
    query.bindValue(":id", repuestoId);
    return query.exec() && query.numRowsAffected() > 0;
}

// ==========================================
// CRUD ÓRDENES DE TRABAJO
// ==========================================
bool DatabaseManager::insertarOrdenTrabajo(OrdenTrabajo &ot) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO ordenes_trabajo (numero, cliente_id, vehiculo_id, descripcion_problema,
                                     diagnostico, trabajo_realizado, estado, fecha_ingreso,
                                     fecha_estimada_entrega, costo_mano_obra, descuento, observaciones)
        VALUES (:numero, :cliente_id, :vehiculo_id, :descripcion, :diagnostico, :trabajo,
                :estado, :fecha_ingreso, :fecha_estimada, :costo_mo, :descuento, :obs)
    )");
    query.bindValue(":numero", ot.getNumero());
    query.bindValue(":cliente_id", ot.getClienteId());
    query.bindValue(":vehiculo_id", ot.getVehiculoId());
    query.bindValue(":descripcion", ot.getDescripcionProblema());
    query.bindValue(":diagnostico", ot.getDiagnostico());
    query.bindValue(":trabajo", ot.getTrabajoRealizado());
    query.bindValue(":estado", static_cast<int>(ot.getEstado()));
    query.bindValue(":fecha_ingreso", ot.getFechaIngreso().toString(Qt::ISODate));
    query.bindValue(":fecha_estimada", ot.getFechaEstimadaEntrega().toString(Qt::ISODate));
    query.bindValue(":costo_mo", ot.getCostoManoObra());
    query.bindValue(":descuento", ot.getDescuento());
    query.bindValue(":obs", ot.getObservaciones());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    ot.setId(query.lastInsertId().toInt());
    return true;
}

bool DatabaseManager::actualizarOrdenTrabajo(const OrdenTrabajo &ot) {
    QSqlQuery query;
    query.prepare(R"(
        UPDATE ordenes_trabajo SET descripcion_problema = :descripcion, diagnostico = :diagnostico,
               trabajo_realizado = :trabajo, estado = :estado, fecha_estimada_entrega = :fecha_estimada,
               fecha_entrega = :fecha_entrega, costo_mano_obra = :costo_mo, costo_repuestos = :costo_rep,
               descuento = :descuento, observaciones = :obs
        WHERE id = :id
    )");
    query.bindValue(":id", ot.getId());
    query.bindValue(":descripcion", ot.getDescripcionProblema());
    query.bindValue(":diagnostico", ot.getDiagnostico());
    query.bindValue(":trabajo", ot.getTrabajoRealizado());
    query.bindValue(":estado", static_cast<int>(ot.getEstado()));
    query.bindValue(":fecha_estimada", ot.getFechaEstimadaEntrega().toString(Qt::ISODate));
    query.bindValue(":fecha_entrega", ot.getFechaEntrega().toString(Qt::ISODate));
    query.bindValue(":costo_mo", ot.getCostoManoObra());
    query.bindValue(":costo_rep", ot.getCostoRepuestos());
    query.bindValue(":descuento", ot.getDescuento());
    query.bindValue(":obs", ot.getObservaciones());

    return query.exec();
}

bool DatabaseManager::eliminarOrdenTrabajo(int otId) {
    QSqlQuery query;
    query.prepare("DELETE FROM ordenes_trabajo WHERE id = :id");
    query.bindValue(":id", otId);
    return query.exec();
}

OrdenTrabajo DatabaseManager::obtenerOrdenTrabajo(int otId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM ordenes_trabajo WHERE id = :id");
    query.bindValue(":id", otId);

    OrdenTrabajo ot;
    if (query.exec() && query.next()) {
        ot.setId(query.value("id").toInt());
        ot.setNumero(query.value("numero").toString());
        ot.setClienteId(query.value("cliente_id").toInt());
        ot.setVehiculoId(query.value("vehiculo_id").toInt());
        ot.setDescripcionProblema(query.value("descripcion_problema").toString());
        ot.setDiagnostico(query.value("diagnostico").toString());
        ot.setTrabajoRealizado(query.value("trabajo_realizado").toString());
        ot.setEstadoFromInt(query.value("estado").toInt());
        ot.setFechaIngreso(QDateTime::fromString(query.value("fecha_ingreso").toString(), Qt::ISODate));
        ot.setFechaEstimadaEntrega(QDateTime::fromString(query.value("fecha_estimada_entrega").toString(), Qt::ISODate));
        ot.setFechaEntrega(QDateTime::fromString(query.value("fecha_entrega").toString(), Qt::ISODate));
        ot.setCostoManoObra(query.value("costo_mano_obra").toDouble());
        ot.setDescuento(query.value("descuento").toDouble());
        ot.setObservaciones(query.value("observaciones").toString());
    }
    return ot;
}

QVector<OrdenTrabajo> DatabaseManager::obtenerTodasOrdenes() {
    QVector<OrdenTrabajo> ordenes;
    QSqlQuery query("SELECT * FROM ordenes_trabajo ORDER BY fecha_ingreso DESC");

    while (query.next()) {
        OrdenTrabajo ot;
        ot.setId(query.value("id").toInt());
        ot.setNumero(query.value("numero").toString());
        ot.setClienteId(query.value("cliente_id").toInt());
        ot.setVehiculoId(query.value("vehiculo_id").toInt());
        ot.setDescripcionProblema(query.value("descripcion_problema").toString());
        ot.setEstadoFromInt(query.value("estado").toInt());
        ot.setFechaIngreso(QDateTime::fromString(query.value("fecha_ingreso").toString(), Qt::ISODate));
        ot.setCostoManoObra(query.value("costo_mano_obra").toDouble());
        ordenes.append(ot);
    }
    return ordenes;
}

QVector<OrdenTrabajo> DatabaseManager::obtenerOrdenesCliente(int clienteId) {
    QVector<OrdenTrabajo> ordenes;
    QSqlQuery query;
    query.prepare("SELECT * FROM ordenes_trabajo WHERE cliente_id = :cliente_id ORDER BY fecha_ingreso DESC");
    query.bindValue(":cliente_id", clienteId);

    if (query.exec()) {
        while (query.next()) {
            OrdenTrabajo ot;
            ot.setId(query.value("id").toInt());
            ot.setNumero(query.value("numero").toString());
            ot.setClienteId(query.value("cliente_id").toInt());
            ot.setVehiculoId(query.value("vehiculo_id").toInt());
            ot.setDescripcionProblema(query.value("descripcion_problema").toString());
            ot.setEstadoFromInt(query.value("estado").toInt());
            ot.setFechaIngreso(QDateTime::fromString(query.value("fecha_ingreso").toString(), Qt::ISODate));
            ordenes.append(ot);
        }
    }
    return ordenes;
}

QVector<OrdenTrabajo> DatabaseManager::obtenerOrdenesVehiculo(int vehiculoId) {
    QVector<OrdenTrabajo> ordenes;
    QSqlQuery query;
    query.prepare("SELECT * FROM ordenes_trabajo WHERE vehiculo_id = :vehiculo_id ORDER BY fecha_ingreso DESC");
    query.bindValue(":vehiculo_id", vehiculoId);

    if (query.exec()) {
        while (query.next()) {
            OrdenTrabajo ot;
            ot.setId(query.value("id").toInt());
            ot.setNumero(query.value("numero").toString());
            ot.setEstadoFromInt(query.value("estado").toInt());
            ot.setFechaIngreso(QDateTime::fromString(query.value("fecha_ingreso").toString(), Qt::ISODate));
            ordenes.append(ot);
        }
    }
    return ordenes;
}

QVector<OrdenTrabajo> DatabaseManager::obtenerOrdenesPorEstado(int estado) {
    QVector<OrdenTrabajo> ordenes;
    QSqlQuery query;
    query.prepare("SELECT * FROM ordenes_trabajo WHERE estado = :estado ORDER BY fecha_ingreso");
    query.bindValue(":estado", estado);

    if (query.exec()) {
        while (query.next()) {
            OrdenTrabajo ot;
            ot.setId(query.value("id").toInt());
            ot.setNumero(query.value("numero").toString());
            ot.setClienteId(query.value("cliente_id").toInt());
            ot.setVehiculoId(query.value("vehiculo_id").toInt());
            ot.setEstadoFromInt(query.value("estado").toInt());
            ot.setFechaIngreso(QDateTime::fromString(query.value("fecha_ingreso").toString(), Qt::ISODate));
            ordenes.append(ot);
        }
    }
    return ordenes;
}

QString DatabaseManager::generarNumeroOT() {
    QSqlQuery query("SELECT MAX(id) FROM ordenes_trabajo");
    int nextId = 1;
    if (query.exec() && query.next()) {
        nextId = query.value(0).toInt() + 1;
    }
    return QString("OT-%1-%2").arg(QDate::currentDate().year()).arg(nextId, 4, 10, QChar('0'));
}

bool DatabaseManager::agregarRepuestoAOrden(int otId, int repuestoId, int cantidad, double precio) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO repuestos_orden (orden_id, repuesto_id, cantidad, precio_unitario)
        VALUES (:orden_id, :repuesto_id, :cantidad, :precio)
    )");
    query.bindValue(":orden_id", otId);
    query.bindValue(":repuesto_id", repuestoId);
    query.bindValue(":cantidad", cantidad);
    query.bindValue(":precio", precio);
    
    if (query.exec()) {
        // Actualizar costo de repuestos en la orden
        QSqlQuery updateQuery;
        updateQuery.prepare(R"(
            UPDATE ordenes_trabajo SET costo_repuestos = (
                SELECT SUM(cantidad * precio_unitario) FROM repuestos_orden WHERE orden_id = :orden_id
            ) WHERE id = :orden_id
        )");
        updateQuery.bindValue(":orden_id", otId);
        updateQuery.exec();
        
        // Descontar stock
        actualizarStock(repuestoId, cantidad, false);
        return true;
    }
    return false;
}

// ==========================================
// CRUD FACTURAS
// ==========================================
bool DatabaseManager::insertarFactura(Factura &factura) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO facturas (numero, cliente_id, orden_trabajo_id, fecha, fecha_vencimiento,
                              subtotal, impuesto, descuento, estado_pago, observaciones)
        VALUES (:numero, :cliente_id, :ot_id, :fecha, :vencimiento, :subtotal, :impuesto,
                :descuento, :estado, :obs)
    )");
    query.bindValue(":numero", factura.getNumero());
    query.bindValue(":cliente_id", factura.getClienteId());
    query.bindValue(":ot_id", factura.getOrdenTrabajoId());
    query.bindValue(":fecha", factura.getFecha().toString(Qt::ISODate));
    query.bindValue(":vencimiento", factura.getFechaVencimiento().toString(Qt::ISODate));
    query.bindValue(":subtotal", factura.getSubtotal());
    query.bindValue(":impuesto", factura.getImpuesto());
    query.bindValue(":descuento", factura.getDescuento());
    query.bindValue(":estado", static_cast<int>(factura.getEstadoPago()));
    query.bindValue(":obs", factura.getObservaciones());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    factura.setId(query.lastInsertId().toInt());
    
    // Insertar items de la factura
    for (const auto &item : factura.getItems()) {
        QSqlQuery itemQuery;
        itemQuery.prepare(R"(
            INSERT INTO items_documento (tipo_documento, documento_id, descripcion, cantidad, precio_unitario, subtotal)
            VALUES (:tipo, :doc_id, :desc, :cant, :precio, :subtotal)
        )");
        itemQuery.bindValue(":tipo", "FACTURA");
        itemQuery.bindValue(":doc_id", factura.getId());
        itemQuery.bindValue(":desc", item.descripcion);
        itemQuery.bindValue(":cant", item.cantidad);
        itemQuery.bindValue(":precio", item.precioUnitario);
        itemQuery.bindValue(":subtotal", item.subtotal);
        
        if (!itemQuery.exec()) {
            throw ErrorBaseDatos(itemQuery.lastError().text().toStdString());
        }
    }
    
    return true;
}

bool DatabaseManager::actualizarFactura(const Factura &factura) {
    QSqlQuery query;
    query.prepare(R"(
        UPDATE facturas SET subtotal = :subtotal, impuesto = :impuesto, descuento = :descuento,
               estado_pago = :estado, monto_pagado = :pagado, fecha_pago = :fecha_pago,
               metodo_pago = :metodo, observaciones = :obs
        WHERE id = :id
    )");
    query.bindValue(":id", factura.getId());
    query.bindValue(":subtotal", factura.getSubtotal());
    query.bindValue(":impuesto", factura.getImpuesto());
    query.bindValue(":descuento", factura.getDescuento());
    query.bindValue(":estado", static_cast<int>(factura.getEstadoPago()));
    query.bindValue(":pagado", factura.getMontoPagado());
    query.bindValue(":fecha_pago", factura.getFechaPago().toString(Qt::ISODate));
    query.bindValue(":metodo", factura.getMetodoPago());
    query.bindValue(":obs", factura.getObservaciones());

    return query.exec();
}

Factura DatabaseManager::obtenerFactura(int facturaId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM facturas WHERE id = :id");
    query.bindValue(":id", facturaId);

    Factura factura;
    if (query.exec() && query.next()) {
        factura.setId(query.value("id").toInt());
        factura.setNumero(query.value("numero").toString());
        factura.setClienteId(query.value("cliente_id").toInt());
        factura.setOrdenTrabajoId(query.value("orden_trabajo_id").toInt());
        factura.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
        factura.setFechaVencimiento(QDateTime::fromString(query.value("fecha_vencimiento").toString(), Qt::ISODate));
        factura.setSubtotal(query.value("subtotal").toDouble());
        factura.setImpuesto(query.value("impuesto").toDouble());
        factura.setDescuento(query.value("descuento").toDouble());
        factura.setEstadoPagoFromInt(query.value("estado_pago").toInt());
        factura.setMontoPagado(query.value("monto_pagado").toDouble());
        factura.setMetodoPago(query.value("metodo_pago").toString());
        factura.setObservaciones(query.value("observaciones").toString());
        
        // Cargar items
        QSqlQuery itemQuery;
        itemQuery.prepare("SELECT * FROM items_documento WHERE tipo_documento = 'FACTURA' AND documento_id = :id");
        itemQuery.bindValue(":id", facturaId);
        
        if (itemQuery.exec()) {
            while (itemQuery.next()) {
                ItemDocumento item;
                item.descripcion = itemQuery.value("descripcion").toString();
                item.cantidad = itemQuery.value("cantidad").toInt();
                item.precioUnitario = itemQuery.value("precio_unitario").toDouble();
                item.subtotal = itemQuery.value("subtotal").toDouble();
                factura.agregarItem(item);
            }
        }
    }
    return factura;
}

QVector<Factura> DatabaseManager::obtenerTodasFacturas() {
    QVector<Factura> facturas;
    QSqlQuery query("SELECT * FROM facturas ORDER BY fecha DESC");

    while (query.next()) {
        Factura factura;
        factura.setId(query.value("id").toInt());
        factura.setNumero(query.value("numero").toString());
        factura.setClienteId(query.value("cliente_id").toInt());
        factura.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
        factura.setSubtotal(query.value("subtotal").toDouble());
        factura.setEstadoPagoFromInt(query.value("estado_pago").toInt());
        facturas.append(factura);
    }
    return facturas;
}

QVector<Factura> DatabaseManager::obtenerFacturasCliente(int clienteId) {
    QVector<Factura> facturas;
    QSqlQuery query;
    query.prepare("SELECT * FROM facturas WHERE cliente_id = :cliente_id ORDER BY fecha DESC");
    query.bindValue(":cliente_id", clienteId);

    if (query.exec()) {
        while (query.next()) {
            Factura factura;
            factura.setId(query.value("id").toInt());
            factura.setNumero(query.value("numero").toString());
            factura.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
            factura.setSubtotal(query.value("subtotal").toDouble());
            factura.setEstadoPagoFromInt(query.value("estado_pago").toInt());
            facturas.append(factura);
        }
    }
    return facturas;
}

QVector<Factura> DatabaseManager::obtenerFacturasPendientes() {
    QVector<Factura> facturas;
    QSqlQuery query("SELECT * FROM facturas WHERE estado_pago IN (0, 2) ORDER BY fecha_vencimiento");

    while (query.next()) {
        Factura factura;
        factura.setId(query.value("id").toInt());
        factura.setNumero(query.value("numero").toString());
        factura.setClienteId(query.value("cliente_id").toInt());
        factura.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
        factura.setFechaVencimiento(QDateTime::fromString(query.value("fecha_vencimiento").toString(), Qt::ISODate));
        factura.setSubtotal(query.value("subtotal").toDouble());
        factura.setEstadoPagoFromInt(query.value("estado_pago").toInt());
        facturas.append(factura);
    }
    return facturas;
}

QString DatabaseManager::generarNumeroFactura() {
    QSqlQuery query("SELECT MAX(id) FROM facturas");
    int nextId = 1;
    if (query.exec() && query.next()) {
        nextId = query.value(0).toInt() + 1;
    }
    return QString("F-%1-%2").arg(QDate::currentDate().year()).arg(nextId, 6, 10, QChar('0'));
}

// ==========================================
// CRUD PRESUPUESTOS
// ==========================================
bool DatabaseManager::insertarPresupuesto(Presupuesto &presupuesto) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO presupuestos (numero, cliente_id, orden_trabajo_id, fecha, fecha_vencimiento,
                                  subtotal, impuesto, descuento, estado, dias_validez, observaciones)
        VALUES (:numero, :cliente_id, :ot_id, :fecha, :vencimiento, :subtotal, :impuesto,
                :descuento, :estado, :dias, :obs)
    )");
    query.bindValue(":numero", presupuesto.getNumero());
    query.bindValue(":cliente_id", presupuesto.getClienteId());
    query.bindValue(":ot_id", presupuesto.getOrdenTrabajoId());
    query.bindValue(":fecha", presupuesto.getFecha().toString(Qt::ISODate));
    query.bindValue(":vencimiento", presupuesto.getFechaVencimiento().toString(Qt::ISODate));
    query.bindValue(":subtotal", presupuesto.getSubtotal());
    query.bindValue(":impuesto", presupuesto.getImpuesto());
    query.bindValue(":descuento", presupuesto.getDescuento());
    query.bindValue(":estado", static_cast<int>(presupuesto.getEstadoPresupuesto()));
    query.bindValue(":dias", presupuesto.getDiasValidez());
    query.bindValue(":obs", presupuesto.getObservaciones());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    presupuesto.setId(query.lastInsertId().toInt());
    
    // Insertar items del presupuesto
    for (const auto &item : presupuesto.getItems()) {
        QSqlQuery itemQuery;
        itemQuery.prepare(R"(
            INSERT INTO items_documento (tipo_documento, documento_id, descripcion, cantidad, precio_unitario, subtotal)
            VALUES (:tipo, :doc_id, :desc, :cant, :precio, :subtotal)
        )");
        itemQuery.bindValue(":tipo", "PRESUPUESTO");
        itemQuery.bindValue(":doc_id", presupuesto.getId());
        itemQuery.bindValue(":desc", item.descripcion);
        itemQuery.bindValue(":cant", item.cantidad);
        itemQuery.bindValue(":precio", item.precioUnitario);
        itemQuery.bindValue(":subtotal", item.subtotal);
        
        if (!itemQuery.exec()) {
            throw ErrorBaseDatos(itemQuery.lastError().text().toStdString());
        }
    }
    
    return true;
}

bool DatabaseManager::actualizarPresupuesto(const Presupuesto &presupuesto) {
    QSqlQuery query;
    query.prepare(R"(
        UPDATE presupuestos SET subtotal = :subtotal, impuesto = :impuesto, descuento = :descuento,
               estado = :estado, factura_generada_id = :factura_id, observaciones = :obs
        WHERE id = :id
    )");
    query.bindValue(":id", presupuesto.getId());
    query.bindValue(":subtotal", presupuesto.getSubtotal());
    query.bindValue(":impuesto", presupuesto.getImpuesto());
    query.bindValue(":descuento", presupuesto.getDescuento());
    query.bindValue(":estado", static_cast<int>(presupuesto.getEstadoPresupuesto()));
    query.bindValue(":factura_id", presupuesto.getFacturaGeneradaId());
    query.bindValue(":obs", presupuesto.getObservaciones());

    return query.exec();
}

Presupuesto DatabaseManager::obtenerPresupuesto(int presupuestoId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM presupuestos WHERE id = :id");
    query.bindValue(":id", presupuestoId);

    Presupuesto presupuesto;
    if (query.exec() && query.next()) {
        presupuesto.setId(query.value("id").toInt());
        presupuesto.setNumero(query.value("numero").toString());
        presupuesto.setClienteId(query.value("cliente_id").toInt());
        presupuesto.setOrdenTrabajoId(query.value("orden_trabajo_id").toInt());
        presupuesto.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
        presupuesto.setFechaVencimiento(QDateTime::fromString(query.value("fecha_vencimiento").toString(), Qt::ISODate));
        presupuesto.setSubtotal(query.value("subtotal").toDouble());
        presupuesto.setImpuesto(query.value("impuesto").toDouble());
        presupuesto.setDescuento(query.value("descuento").toDouble());
        presupuesto.setEstadoPresupuestoFromInt(query.value("estado").toInt());
        presupuesto.setDiasValidez(query.value("dias_validez").toInt());
        presupuesto.setFacturaGeneradaId(query.value("factura_generada_id").toInt());
        presupuesto.setObservaciones(query.value("observaciones").toString());
        
        // Cargar items
        QSqlQuery itemQuery;
        itemQuery.prepare("SELECT * FROM items_documento WHERE tipo_documento = 'PRESUPUESTO' AND documento_id = :id");
        itemQuery.bindValue(":id", presupuestoId);
        
        if (itemQuery.exec()) {
            while (itemQuery.next()) {
                ItemDocumento item;
                item.descripcion = itemQuery.value("descripcion").toString();
                item.cantidad = itemQuery.value("cantidad").toInt();
                item.precioUnitario = itemQuery.value("precio_unitario").toDouble();
                item.subtotal = itemQuery.value("subtotal").toDouble();
                presupuesto.agregarItem(item);
            }
        }
    }
    return presupuesto;
}

QVector<Presupuesto> DatabaseManager::obtenerPresupuestosCliente(int clienteId) {
    QVector<Presupuesto> presupuestos;
    QSqlQuery query;
    query.prepare("SELECT * FROM presupuestos WHERE cliente_id = :cliente_id ORDER BY fecha DESC");
    query.bindValue(":cliente_id", clienteId);

    if (query.exec()) {
        while (query.next()) {
            Presupuesto p;
            p.setId(query.value("id").toInt());
            p.setNumero(query.value("numero").toString());
            p.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
            p.setSubtotal(query.value("subtotal").toDouble());
            p.setEstadoPresupuestoFromInt(query.value("estado").toInt());
            presupuestos.append(p);
        }
    }
    return presupuestos;
}

QVector<Presupuesto> DatabaseManager::obtenerTodosPresupuestos() {
    QVector<Presupuesto> presupuestos;
    QSqlQuery query("SELECT * FROM presupuestos ORDER BY fecha DESC");

    while (query.next()) {
        Presupuesto p;
        p.setId(query.value("id").toInt());
        p.setNumero(query.value("numero").toString());
        p.setClienteId(query.value("cliente_id").toInt());
        p.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
        p.setSubtotal(query.value("subtotal").toDouble());
        p.setEstadoPresupuestoFromInt(query.value("estado").toInt());
        presupuestos.append(p);
    }
    return presupuestos;
}

QString DatabaseManager::generarNumeroPresupuesto() {
    QSqlQuery query("SELECT MAX(id) FROM presupuestos");
    int nextId = 1;
    if (query.exec() && query.next()) {
        nextId = query.value(0).toInt() + 1;
    }
    return QString("P-%1-%2").arg(QDate::currentDate().year()).arg(nextId, 6, 10, QChar('0'));
}

// ==========================================
// CRUD CITAS / AGENDA
// ==========================================
bool DatabaseManager::insertarCita(CitaAgenda &cita) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO citas_agenda (cliente_id, vehiculo_id, orden_trabajo_id, titulo, descripcion,
                                  tipo, estado, fecha_hora_inicio, fecha_hora_fin, duracion_minutos,
                                  color, notas)
        VALUES (:cliente_id, :vehiculo_id, :ot_id, :titulo, :descripcion, :tipo, :estado,
                :inicio, :fin, :duracion, :color, :notas)
    )");
    query.bindValue(":cliente_id", cita.getClienteId());
    query.bindValue(":vehiculo_id", cita.getVehiculoId());
    query.bindValue(":ot_id", cita.getOrdenTrabajoId());
    query.bindValue(":titulo", cita.getTitulo());
    query.bindValue(":descripcion", cita.getDescripcion());
    query.bindValue(":tipo", static_cast<int>(cita.getTipo()));
    query.bindValue(":estado", static_cast<int>(cita.getEstado()));
    query.bindValue(":inicio", cita.getFechaHoraInicio().toString(Qt::ISODate));
    query.bindValue(":fin", cita.getFechaHoraFin().toString(Qt::ISODate));
    query.bindValue(":duracion", cita.getDuracionEstimadaMin());
    query.bindValue(":color", cita.getColorCalendario());
    query.bindValue(":notas", cita.getNotas());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    cita.setId(query.lastInsertId().toInt());
    return true;
}

bool DatabaseManager::actualizarCita(const CitaAgenda &cita) {
    QSqlQuery query;
    query.prepare(R"(
        UPDATE citas_agenda SET titulo = :titulo, descripcion = :descripcion, tipo = :tipo,
               estado = :estado, fecha_hora_inicio = :inicio, fecha_hora_fin = :fin,
               duracion_minutos = :duracion, color = :color, notas = :notas
        WHERE id = :id
    )");
    query.bindValue(":id", cita.getId());
    query.bindValue(":titulo", cita.getTitulo());
    query.bindValue(":descripcion", cita.getDescripcion());
    query.bindValue(":tipo", static_cast<int>(cita.getTipo()));
    query.bindValue(":estado", static_cast<int>(cita.getEstado()));
    query.bindValue(":inicio", cita.getFechaHoraInicio().toString(Qt::ISODate));
    query.bindValue(":fin", cita.getFechaHoraFin().toString(Qt::ISODate));
    query.bindValue(":duracion", cita.getDuracionEstimadaMin());
    query.bindValue(":color", cita.getColorCalendario());
    query.bindValue(":notas", cita.getNotas());

    return query.exec();
}

bool DatabaseManager::eliminarCita(int citaId) {
    QSqlQuery query;
    query.prepare("DELETE FROM citas_agenda WHERE id = :id");
    query.bindValue(":id", citaId);
    return query.exec();
}

CitaAgenda DatabaseManager::obtenerCita(int citaId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM citas_agenda WHERE id = :id");
    query.bindValue(":id", citaId);

    CitaAgenda cita;
    if (query.exec() && query.next()) {
        cita.setId(query.value("id").toInt());
        cita.setClienteId(query.value("cliente_id").toInt());
        cita.setVehiculoId(query.value("vehiculo_id").toInt());
        cita.setTitulo(query.value("titulo").toString());
        cita.setDescripcion(query.value("descripcion").toString());
        cita.setTipoFromInt(query.value("tipo").toInt());
        cita.setEstadoFromInt(query.value("estado").toInt());
        cita.setFechaHoraInicio(QDateTime::fromString(query.value("fecha_hora_inicio").toString(), Qt::ISODate));
        cita.setFechaHoraFin(QDateTime::fromString(query.value("fecha_hora_fin").toString(), Qt::ISODate));
        cita.setDuracionEstimadaMin(query.value("duracion_minutos").toInt());
        cita.setColorCalendario(query.value("color").toString());
        cita.setNotas(query.value("notas").toString());
    }
    return cita;
}

QVector<CitaAgenda> DatabaseManager::obtenerCitasPorFecha(const QDate &fecha) {
    QVector<CitaAgenda> citas;
    QSqlQuery query;
    query.prepare("SELECT * FROM citas_agenda WHERE DATE(fecha_hora_inicio) = :fecha ORDER BY fecha_hora_inicio");
    query.bindValue(":fecha", fecha.toString(Qt::ISODate));

    if (query.exec()) {
        while (query.next()) {
            CitaAgenda cita;
            cita.setId(query.value("id").toInt());
            cita.setClienteId(query.value("cliente_id").toInt());
            cita.setVehiculoId(query.value("vehiculo_id").toInt());
            cita.setTitulo(query.value("titulo").toString());
            cita.setTipoFromInt(query.value("tipo").toInt());
            cita.setEstadoFromInt(query.value("estado").toInt());
            cita.setFechaHoraInicio(QDateTime::fromString(query.value("fecha_hora_inicio").toString(), Qt::ISODate));
            cita.setFechaHoraFin(QDateTime::fromString(query.value("fecha_hora_fin").toString(), Qt::ISODate));
            cita.setColorCalendario(query.value("color").toString());
            citas.append(cita);
        }
    }
    return citas;
}

QVector<CitaAgenda> DatabaseManager::obtenerCitasHoy() {
    return obtenerCitasPorFecha(QDate::currentDate());
}

QVector<CitaAgenda> DatabaseManager::obtenerCitasSemana() {
    QVector<CitaAgenda> citas;
    QDate hoy = QDate::currentDate();
    QDate finSemana = hoy.addDays(7);

    QSqlQuery query;
    query.prepare("SELECT * FROM citas_agenda WHERE DATE(fecha_hora_inicio) BETWEEN :inicio AND :fin ORDER BY fecha_hora_inicio");
    query.bindValue(":inicio", hoy.toString(Qt::ISODate));
    query.bindValue(":fin", finSemana.toString(Qt::ISODate));

    if (query.exec()) {
        while (query.next()) {
            CitaAgenda cita;
            cita.setId(query.value("id").toInt());
            cita.setClienteId(query.value("cliente_id").toInt());
            cita.setTitulo(query.value("titulo").toString());
            cita.setTipoFromInt(query.value("tipo").toInt());
            cita.setEstadoFromInt(query.value("estado").toInt());
            cita.setFechaHoraInicio(QDateTime::fromString(query.value("fecha_hora_inicio").toString(), Qt::ISODate));
            cita.setColorCalendario(query.value("color").toString());
            citas.append(cita);
        }
    }
    return citas;
}

QVector<CitaAgenda> DatabaseManager::obtenerCitasCliente(int clienteId) {
    QVector<CitaAgenda> citas;
    QSqlQuery query;
    query.prepare("SELECT * FROM citas_agenda WHERE cliente_id = :cliente_id ORDER BY fecha_hora_inicio DESC");
    query.bindValue(":cliente_id", clienteId);

    if (query.exec()) {
        while (query.next()) {
            CitaAgenda cita;
            cita.setId(query.value("id").toInt());
            cita.setTitulo(query.value("titulo").toString());
            cita.setTipoFromInt(query.value("tipo").toInt());
            cita.setEstadoFromInt(query.value("estado").toInt());
            cita.setFechaHoraInicio(QDateTime::fromString(query.value("fecha_hora_inicio").toString(), Qt::ISODate));
            citas.append(cita);
        }
    }
    return citas;
}

QVector<CitaAgenda> DatabaseManager::obtenerTodasCitas() {
    QVector<CitaAgenda> citas;
    QSqlQuery query("SELECT * FROM citas_agenda ORDER BY fecha_hora_inicio DESC");

    while (query.next()) {
        CitaAgenda cita;
        cita.setId(query.value("id").toInt());
        cita.setClienteId(query.value("cliente_id").toInt());
        cita.setVehiculoId(query.value("vehiculo_id").toInt());
        cita.setTitulo(query.value("titulo").toString());
        cita.setTipoFromInt(query.value("tipo").toInt());
        cita.setEstadoFromInt(query.value("estado").toInt());
        cita.setFechaHoraInicio(QDateTime::fromString(query.value("fecha_hora_inicio").toString(), Qt::ISODate));
        cita.setColorCalendario(query.value("color").toString());
        citas.append(cita);
    }
    return citas;
}

// ==========================================
// CRUD HISTORIAL DE SERVICIOS
// ==========================================
bool DatabaseManager::insertarHistorial(HistorialServicio &historial) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO historial_servicios (vehiculo_id, cliente_id, orden_trabajo_id, tipo_servicio,
                                         descripcion, trabajo_realizado, kilometraje, fecha, costo_total,
                                         repuestos_utilizados, observaciones, proximo_servicio_km,
                                         proximo_servicio_fecha, tecnico_responsable)
        VALUES (:vehiculo_id, :cliente_id, :ot_id, :tipo, :descripcion, :trabajo, :km, :fecha,
                :costo, :repuestos, :obs, :proximo_km, :proximo_fecha, :tecnico)
    )");
    query.bindValue(":vehiculo_id", historial.getVehiculoId());
    query.bindValue(":cliente_id", historial.getClienteId());
    query.bindValue(":ot_id", historial.getOrdenTrabajoId());
    query.bindValue(":tipo", static_cast<int>(historial.getTipoServicio()));
    query.bindValue(":descripcion", historial.getDescripcion());
    query.bindValue(":trabajo", historial.getTrabajoRealizado());
    query.bindValue(":km", historial.getKilometraje());
    query.bindValue(":fecha", historial.getFecha().toString(Qt::ISODate));
    query.bindValue(":costo", historial.getCostoTotal());
    query.bindValue(":repuestos", historial.getRepuestosUtilizados());
    query.bindValue(":obs", historial.getObservaciones());
    query.bindValue(":proximo_km", historial.getProximoServicioKm());
    query.bindValue(":proximo_fecha", historial.getProximoServicioFecha().toString(Qt::ISODate));
    query.bindValue(":tecnico", historial.getTecnicoResponsable());

    if (!query.exec()) {
        throw ErrorBaseDatos(query.lastError().text().toStdString());
    }
    historial.setId(query.lastInsertId().toInt());
    return true;
}

QVector<HistorialServicio> DatabaseManager::obtenerHistorialVehiculo(int vehiculoId) {
    QVector<HistorialServicio> historial;
    QSqlQuery query;
    query.prepare("SELECT * FROM historial_servicios WHERE vehiculo_id = :vehiculo_id ORDER BY fecha DESC");
    query.bindValue(":vehiculo_id", vehiculoId);

    if (query.exec()) {
        while (query.next()) {
            HistorialServicio h;
            h.setId(query.value("id").toInt());
            h.setVehiculoId(query.value("vehiculo_id").toInt());
            h.setClienteId(query.value("cliente_id").toInt());
            h.setTipoServicioFromInt(query.value("tipo_servicio").toInt());
            h.setDescripcion(query.value("descripcion").toString());
            h.setKilometraje(query.value("kilometraje").toInt());
            h.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
            h.setCostoTotal(query.value("costo_total").toDouble());
            historial.append(h);
        }
    }
    return historial;
}

QVector<HistorialServicio> DatabaseManager::obtenerHistorialCliente(int clienteId) {
    QVector<HistorialServicio> historial;
    QSqlQuery query;
    query.prepare("SELECT * FROM historial_servicios WHERE cliente_id = :cliente_id ORDER BY fecha DESC");
    query.bindValue(":cliente_id", clienteId);

    if (query.exec()) {
        while (query.next()) {
            HistorialServicio h;
            h.setId(query.value("id").toInt());
            h.setVehiculoId(query.value("vehiculo_id").toInt());
            h.setTipoServicioFromInt(query.value("tipo_servicio").toInt());
            h.setDescripcion(query.value("descripcion").toString());
            h.setKilometraje(query.value("kilometraje").toInt());
            h.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
            h.setCostoTotal(query.value("costo_total").toDouble());
            historial.append(h);
        }
    }
    return historial;
}

QVector<HistorialServicio> DatabaseManager::obtenerTodoHistorial() {
    QVector<HistorialServicio> historial;
    QSqlQuery query("SELECT * FROM historial_servicios ORDER BY fecha DESC");

    while (query.next()) {
        HistorialServicio h;
        h.setId(query.value("id").toInt());
        h.setVehiculoId(query.value("vehiculo_id").toInt());
        h.setClienteId(query.value("cliente_id").toInt());
        h.setTipoServicioFromInt(query.value("tipo_servicio").toInt());
        h.setDescripcion(query.value("descripcion").toString());
        h.setKilometraje(query.value("kilometraje").toInt());
        h.setFecha(QDateTime::fromString(query.value("fecha").toString(), Qt::ISODate));
        h.setCostoTotal(query.value("costo_total").toDouble());
        historial.append(h);
    }
    return historial;
}
