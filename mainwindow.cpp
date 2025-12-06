#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/clientedialog.h"
#include "dialogs/vehiculodialog.h"
#include "dialogs/repuestodialog.h"
#include "dialogs/ordentrabajodialog.h"
#include "dialogs/citadialog.h"
#include "dialogs/facturadialog.h"
#include "dialogs/presupuestodialog.h"
#include <QHeaderView>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTabWidget>
#include <QSplitter>
#include <QDate>
#include <QPixmap>
#include <QFile>
#include <QIcon>
#include <QSet>
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ordenesTable(nullptr)
    , inventarioTable(nullptr)
    , facturasTable(nullptr)
    , calendario(nullptr)
    , citasDelDia(nullptr)
    , lblOrdenesActivas(nullptr)
    , lblCitasHoy(nullptr)
    , lblStockCritico(nullptr)
{
    ui->setupUi(this);

    // Inicializar base de datos SQLite (no requiere servidor)
    db = DatabaseManager::getInstance();
    
    // Conectar a SQLite - el archivo se crea automáticamente
    if (!db->connect("", 0, "", "", "")) {
        QMessageBox::critical(this, "Error de Base de Datos", 
            "No se pudo crear/abrir la base de datos SQLite.");
    }

    setupUI();
    setupConnections();
    setupDashboard();
    
    // Cargar datos iniciales de todas las tablas
    actualizarTablaClientes();
    actualizarTablaVehiculos();
    actualizarTablaOrdenes();
    actualizarTablaInventario();
    actualizarTablaFacturas();
    actualizarAgenda();
    marcarDiasConCitas();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupUI() {
    setWindowTitle("Taller San Juan");
    setMinimumSize(1200, 800);
    resize(1400, 900);

    // Cargar logo
    QPixmap logo(":/images/Logo.png");
    if (!logo.isNull()) {
        ui->logoLabel->setPixmap(logo.scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        setWindowIcon(QIcon(":/images/Logo.png"));
    } else {
        // Si no hay logo, mostrar un icono por defecto
        ui->logoLabel->setText("");
        ui->logoLabel->setStyleSheet("font-size: 40px; color: #f97316;");
    }

    // Configurar tabla de clientes
    ui->tablaClientes->setColumnCount(5);
    ui->tablaClientes->setHorizontalHeaderLabels({"ID", "RUT", "Nombre", "Teléfono", "Dirección"});
    ui->tablaClientes->horizontalHeader()->setStretchLastSection(true);
    ui->tablaClientes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablaClientes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablaClientes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaClientes->setColumnHidden(0, true);

    // Configurar tabla de vehículos
    ui->tablaVehiculos->setColumnCount(6);
    ui->tablaVehiculos->setHorizontalHeaderLabels({"ID", "Tipo", "Patente", "Modelo", "Año", "Detalles"});
    ui->tablaVehiculos->horizontalHeader()->setStretchLastSection(true);
    ui->tablaVehiculos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablaVehiculos->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablaVehiculos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaVehiculos->setColumnHidden(0, true);

    // Configurar tabla de órdenes
    ui->tablaOrdenes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablaOrdenes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablaOrdenes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaOrdenes->setColumnHidden(0, true);
    ui->tablaOrdenes->horizontalHeader()->setStretchLastSection(true);

    // Configurar tabla de inventario
    ui->tablaInventario->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablaInventario->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablaInventario->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaInventario->setColumnHidden(0, true);
    ui->tablaInventario->horizontalHeader()->setStretchLastSection(true);

    // Configurar tabla de facturas
    ui->tablaFacturas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tablaFacturas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tablaFacturas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tablaFacturas->setColumnHidden(0, true);
    ui->tablaFacturas->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::setupConnections() {
    // Botones de clientes
    connect(ui->btnAgregarCliente, &QPushButton::clicked, this, &MainWindow::onAgregarCliente);
    connect(ui->btnEditarCliente, &QPushButton::clicked, this, &MainWindow::onEditarCliente);
    connect(ui->btnEliminarCliente, &QPushButton::clicked, this, &MainWindow::onEliminarCliente);
    connect(ui->btnHistorialCliente, &QPushButton::clicked, this, &MainWindow::onVerHistorialCliente);
    connect(ui->tablaClientes, &QTableWidget::itemSelectionChanged, this, &MainWindow::onClienteSeleccionado);

    // Botones de vehículos
    connect(ui->btnAgregarAuto, &QPushButton::clicked, this, &MainWindow::onAgregarAuto);
    connect(ui->btnAgregarMoto, &QPushButton::clicked, this, &MainWindow::onAgregarMoto);
    connect(ui->btnAgregarHibrido, &QPushButton::clicked, this, &MainWindow::onAgregarHibrido);
    connect(ui->btnEliminarVehiculo, &QPushButton::clicked, this, &MainWindow::onEliminarVehiculo);
    connect(ui->btnHistorialVehiculo, &QPushButton::clicked, this, &MainWindow::onVerHistorialVehiculo);

    // Botones de órdenes de trabajo
    connect(ui->btnNuevaOrden, &QPushButton::clicked, this, &MainWindow::onNuevaOrden);
    connect(ui->btnEditarOrden, &QPushButton::clicked, this, &MainWindow::onEditarOrden);
    connect(ui->btnCambiarEstado, &QPushButton::clicked, this, &MainWindow::onCambiarEstadoOrden);

    // Botones de inventario
    connect(ui->btnNuevoRepuesto, &QPushButton::clicked, this, &MainWindow::onNuevoRepuesto);
    connect(ui->btnEditarRepuesto, &QPushButton::clicked, this, &MainWindow::onEditarRepuesto);
    connect(ui->btnEliminarRepuesto, &QPushButton::clicked, this, &MainWindow::onEliminarRepuesto);
    connect(ui->btnAjustarStock, &QPushButton::clicked, this, &MainWindow::onAjustarStock);

    // Botones de agenda
    connect(ui->btnNuevaCita, &QPushButton::clicked, this, &MainWindow::onNuevaCita);
    connect(ui->btnEditarCita, &QPushButton::clicked, this, &MainWindow::onEditarCita);
    connect(ui->btnEliminarCita, &QPushButton::clicked, this, &MainWindow::onEliminarCita);
    connect(ui->calendario, &QCalendarWidget::selectionChanged, this, [this]() {
        onFechaSeleccionada(ui->calendario->selectedDate());
    });
    
    // Actualizar marcas cuando se cambia de mes
    connect(ui->calendario, &QCalendarWidget::currentPageChanged, this, [this]() {
        marcarDiasConCitas();
    });

    // Botones de facturación
    connect(ui->btnNuevaFactura, &QPushButton::clicked, this, &MainWindow::onNuevaFactura);
    connect(ui->btnNuevoPresupuesto, &QPushButton::clicked, this, &MainWindow::onNuevoPresupuesto);
    connect(ui->btnRegistrarPago, &QPushButton::clicked, this, &MainWindow::onRegistrarPago);
    connect(ui->btnVerDetalle, &QPushButton::clicked, this, &MainWindow::onVerDetalleFactura);
    connect(ui->btnAnularFactura, &QPushButton::clicked, this, &MainWindow::onAnularFactura);
    connect(ui->btnConvertirFactura, &QPushButton::clicked, this, &MainWindow::onConvertirPresupuestoAFactura);

    // Asignar punteros a las tablas
    ordenesTable = ui->tablaOrdenes;
    inventarioTable = ui->tablaInventario;
    facturasTable = ui->tablaFacturas;
    calendario = ui->calendario;
    citasDelDia = ui->listaCitas;
}

// ==========================================
// SLOTS DE CLIENTES
// ==========================================
void MainWindow::onAgregarCliente() {
    ClienteDialog dialog(this);
    dialog.setWindowTitle("Agregar Cliente");

    if (dialog.exec() == QDialog::Accepted) {
        try {
            Cliente cliente = dialog.getCliente();
            db->insertarCliente(cliente);
            actualizarTablaClientes();
            QMessageBox::information(this, "Éxito", "Cliente registrado correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onEditarCliente() {
    int clienteId = getSelectedClienteId();
    if (clienteId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente para editar.");
        return;
    }

    try {
        Cliente cliente = db->obtenerCliente(clienteId);
        ClienteDialog dialog(this, &cliente);
        dialog.setWindowTitle("Editar Cliente");

        if (dialog.exec() == QDialog::Accepted) {
            Cliente clienteEditado = dialog.getCliente();
            clienteEditado.setId(clienteId);
            db->actualizarCliente(clienteEditado);
            actualizarTablaClientes();
            QMessageBox::information(this, "Éxito", "Cliente actualizado correctamente.");
        }
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onEliminarCliente() {
    int clienteId = getSelectedClienteId();
    if (clienteId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente para eliminar.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmar",
        "¿Está seguro de eliminar este cliente?\nSe eliminarán también sus vehículos.",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            db->eliminarCliente(clienteId);
            actualizarTablaClientes();
            actualizarTablaVehiculos();
            QMessageBox::information(this, "Éxito", "Cliente eliminado correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onClienteSeleccionado() {
    actualizarTablaVehiculos();
}

// ==========================================
// SLOTS DE VEHÍCULOS
// ==========================================
void MainWindow::onAgregarAuto() {
    int clienteId = getSelectedClienteId();
    if (clienteId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente primero.");
        return;
    }

    VehiculoDialog dialog(this, VehiculoDialog::TIPO_AUTO);
    dialog.setWindowTitle("Agregar Auto");

    if (dialog.exec() == QDialog::Accepted) {
        try {
            Auto *autoVeh = dialog.getAuto();
            db->insertarVehiculo(autoVeh, clienteId);
            delete autoVeh;
            actualizarTablaVehiculos();
            QMessageBox::information(this, "Éxito", "Auto agregado correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onAgregarMoto() {
    int clienteId = getSelectedClienteId();
    if (clienteId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente primero.");
        return;
    }

    VehiculoDialog dialog(this, VehiculoDialog::TIPO_MOTO);
    dialog.setWindowTitle("Agregar Moto");

    if (dialog.exec() == QDialog::Accepted) {
        try {
            Moto *moto = dialog.getMoto();
            db->insertarVehiculo(moto, clienteId);
            delete moto;
            actualizarTablaVehiculos();
            QMessageBox::information(this, "Éxito", "Moto agregada correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onAgregarHibrido() {
    int clienteId = getSelectedClienteId();
    if (clienteId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente primero.");
        return;
    }

    VehiculoDialog dialog(this, VehiculoDialog::TIPO_HIBRIDO);
    dialog.setWindowTitle("Agregar Auto Híbrido");

    if (dialog.exec() == QDialog::Accepted) {
        try {
            AutoHibrido *hibrido = dialog.getHibrido();
            db->insertarVehiculo(hibrido, clienteId);
            delete hibrido;
            actualizarTablaVehiculos();
            QMessageBox::information(this, "Éxito", "Auto híbrido agregado correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onEliminarVehiculo() {
    int vehiculoId = getSelectedVehiculoId();
    if (vehiculoId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un vehículo para eliminar.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmar",
        "¿Está seguro de eliminar este vehículo?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            db->eliminarVehiculo(vehiculoId);
            actualizarTablaVehiculos();
            QMessageBox::information(this, "Éxito", "Vehículo eliminado correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

// ==========================================
// ACTUALIZAR TABLAS
// ==========================================
void MainWindow::actualizarTablaClientes() {
    ui->tablaClientes->setRowCount(0);
    QVector<Cliente> clientes = db->obtenerTodosClientes();

    for (const Cliente &cliente : clientes) {
        int row = ui->tablaClientes->rowCount();
        ui->tablaClientes->insertRow(row);

        ui->tablaClientes->setItem(row, 0, new QTableWidgetItem(QString::number(cliente.getId())));
        ui->tablaClientes->setItem(row, 1, new QTableWidgetItem(cliente.getRut()));
        ui->tablaClientes->setItem(row, 2, new QTableWidgetItem(cliente.getNombreCompleto()));
        ui->tablaClientes->setItem(row, 3, new QTableWidgetItem(cliente.getTelefono()));
        ui->tablaClientes->setItem(row, 4, new QTableWidgetItem(cliente.getDireccion()));
    }

    ui->tablaClientes->resizeColumnsToContents();
    ui->tablaVehiculos->setRowCount(0); // Limpiar vehículos
}

void MainWindow::actualizarTablaVehiculos() {
    ui->tablaVehiculos->setRowCount(0);

    int clienteId = getSelectedClienteId();
    if (clienteId == -1) return;

    QVector<std::shared_ptr<Vehiculo>> vehiculos = db->obtenerVehiculosCliente(clienteId);

    for (const auto &vehiculo : vehiculos) {
        int row = ui->tablaVehiculos->rowCount();
        ui->tablaVehiculos->insertRow(row);

        ui->tablaVehiculos->setItem(row, 0, new QTableWidgetItem(QString::number(vehiculo->getId())));
        ui->tablaVehiculos->setItem(row, 1, new QTableWidgetItem(vehiculo->getTipo()));
        ui->tablaVehiculos->setItem(row, 2, new QTableWidgetItem(vehiculo->getPatente()));
        ui->tablaVehiculos->setItem(row, 3, new QTableWidgetItem(vehiculo->getModelo()));
        ui->tablaVehiculos->setItem(row, 4, new QTableWidgetItem(vehiculo->getAnio()));
        ui->tablaVehiculos->setItem(row, 5, new QTableWidgetItem(
            vehiculo->getMotor().getDetalles() + " | " + vehiculo->getInfoAdicional()));
    }

    ui->tablaVehiculos->resizeColumnsToContents();
}

// ==========================================
// UTILIDADES
// ==========================================
int MainWindow::getSelectedClienteId() {
    QList<QTableWidgetItem*> items = ui->tablaClientes->selectedItems();
    if (items.isEmpty()) return -1;
    return ui->tablaClientes->item(items.first()->row(), 0)->text().toInt();
}

int MainWindow::getSelectedVehiculoId() {
    QList<QTableWidgetItem*> items = ui->tablaVehiculos->selectedItems();
    if (items.isEmpty()) return -1;
    return ui->tablaVehiculos->item(items.first()->row(), 0)->text().toInt();
}

// ==========================================
// HISTORIAL
// ==========================================
void MainWindow::onVerHistorialCliente() {
    int clienteId = getSelectedClienteId();
    if (clienteId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente para ver su historial.");
        return;
    }
    
    auto historial = db->obtenerHistorialCliente(clienteId);
    QString info = "Historial del Cliente:\n\n";
    
    if (historial.isEmpty()) {
        info += "No hay servicios registrados.";
    } else {
        for (const auto &h : historial) {
            info += QString("%1 - %2 - $%3\n")
                .arg(h.getFecha().toString("dd/MM/yyyy"))
                .arg(h.getTipoServicioTexto())
                .arg(h.getCostoTotal());
        }
    }
    QMessageBox::information(this, "Historial de Servicios", info);
}

void MainWindow::onVerHistorialVehiculo() {
    int vehiculoId = getSelectedVehiculoId();
    if (vehiculoId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un vehículo para ver su historial.");
        return;
    }
    
    auto historial = db->obtenerHistorialVehiculo(vehiculoId);
    QString info = "Historial del Vehículo:\n\n";
    
    if (historial.isEmpty()) {
        info += "No hay servicios registrados.";
    } else {
        for (const auto &h : historial) {
            info += QString("%1 - %2 - %3 km - $%4\n")
                .arg(h.getFecha().toString("dd/MM/yyyy"))
                .arg(h.getTipoServicioTexto())
                .arg(h.getKilometraje())
                .arg(h.getCostoTotal());
        }
    }
    QMessageBox::information(this, "Historial de Servicios", info);
}

// ==========================================
// ÓRDENES DE TRABAJO
// ==========================================
void MainWindow::onNuevaOrden() {
    OrdenTrabajoDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        try {
            OrdenTrabajo ot = dialog.getOrdenTrabajo();
            db->insertarOrdenTrabajo(ot);
            actualizarTablaOrdenes();
            actualizarDashboard();
            QMessageBox::information(this, "Éxito", "Orden de trabajo creada: " + ot.getNumero());
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onEditarOrden() {
    int ordenId = getSelectedOrdenId();
    if (ordenId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una orden de trabajo.");
        return;
    }
    
    try {
        OrdenTrabajo ot = db->obtenerOrdenTrabajo(ordenId);
        OrdenTrabajoDialog dialog(ot, this);
        
        if (dialog.exec() == QDialog::Accepted) {
            OrdenTrabajo otEditada = dialog.getOrdenTrabajo();
            otEditada.setId(ordenId);
            db->actualizarOrdenTrabajo(otEditada);
            actualizarTablaOrdenes();
            actualizarDashboard();
            QMessageBox::information(this, "Éxito", "Orden actualizada correctamente.");
        }
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onCambiarEstadoOrden() {
    int ordenId = getSelectedOrdenId();
    if (ordenId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una orden de trabajo.");
        return;
    }
    
    QStringList estados = {"Pendiente", "En Proceso", "Esperando Repuestos", 
                           "Completada", "Entregada", "Cancelada"};
    bool ok;
    QString estado = QInputDialog::getItem(this, "Cambiar Estado", 
                                           "Seleccione el nuevo estado:", 
                                           estados, 0, false, &ok);
    if (ok) {
        try {
            OrdenTrabajo ot = db->obtenerOrdenTrabajo(ordenId);
            ot.setEstadoFromInt(estados.indexOf(estado));
            db->actualizarOrdenTrabajo(ot);
            actualizarTablaOrdenes();
            actualizarDashboard();
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::actualizarTablaOrdenes() {
    if (!ordenesTable) return;
    
    ordenesTable->setRowCount(0);
    auto ordenes = db->obtenerTodasOrdenes();
    
    for (const auto &ot : ordenes) {
        int row = ordenesTable->rowCount();
        ordenesTable->insertRow(row);
        
        ordenesTable->setItem(row, 0, new QTableWidgetItem(QString::number(ot.getId())));
        ordenesTable->setItem(row, 1, new QTableWidgetItem(ot.getNumero()));
        ordenesTable->setItem(row, 2, new QTableWidgetItem(ot.getEstadoTexto()));
        ordenesTable->setItem(row, 3, new QTableWidgetItem(ot.getFechaIngreso().toString("dd/MM/yyyy")));
        ordenesTable->setItem(row, 4, new QTableWidgetItem(QString("$%1").arg(ot.getCostoManoObra())));
    }
    ordenesTable->resizeColumnsToContents();
}

// ==========================================
// INVENTARIO
// ==========================================
void MainWindow::onNuevoRepuesto() {
    RepuestoDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        try {
            Repuesto repuesto = dialog.getRepuesto();
            db->insertarRepuesto(repuesto);
            actualizarTablaInventario();
            actualizarDashboard();
            QMessageBox::information(this, "Éxito", "Repuesto agregado al inventario.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onEditarRepuesto() {
    int repuestoId = getSelectedRepuestoId();
    if (repuestoId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un repuesto.");
        return;
    }
    
    try {
        Repuesto repuesto = db->obtenerRepuesto(repuestoId);
        RepuestoDialog dialog(repuesto, this);
        
        if (dialog.exec() == QDialog::Accepted) {
            Repuesto repuestoEditado = dialog.getRepuesto();
            repuestoEditado.setId(repuestoId);
            db->actualizarRepuesto(repuestoEditado);
            actualizarTablaInventario();
            QMessageBox::information(this, "Éxito", "Repuesto actualizado.");
        }
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onEliminarRepuesto() {
    int repuestoId = getSelectedRepuestoId();
    if (repuestoId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un repuesto.");
        return;
    }
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmar",
        "¿Está seguro de eliminar este repuesto?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        db->eliminarRepuesto(repuestoId);
        actualizarTablaInventario();
    }
}

void MainWindow::onAjustarStock() {
    int repuestoId = getSelectedRepuestoId();
    if (repuestoId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un repuesto.");
        return;
    }
    
    QStringList opciones = {"Agregar stock (ingreso)", "Descontar stock (salida)"};
    bool ok;
    QString opcion = QInputDialog::getItem(this, "Ajustar Stock", 
                                           "Tipo de ajuste:", opciones, 0, false, &ok);
    if (!ok) return;
    
    int cantidad = QInputDialog::getInt(this, "Cantidad", "Ingrese la cantidad:", 1, 1, 9999, 1, &ok);
    if (ok) {
        bool esIngreso = (opciones.indexOf(opcion) == 0);
        if (db->actualizarStock(repuestoId, cantidad, esIngreso)) {
            actualizarTablaInventario();
            actualizarDashboard();
            QMessageBox::information(this, "Éxito", "Stock actualizado.");
        } else {
            QMessageBox::warning(this, "Error", "No se pudo actualizar el stock.");
        }
    }
}

void MainWindow::actualizarTablaInventario() {
    if (!inventarioTable) return;
    
    inventarioTable->setRowCount(0);
    auto repuestos = db->obtenerTodosRepuestos();
    
    for (const auto &rep : repuestos) {
        int row = inventarioTable->rowCount();
        inventarioTable->insertRow(row);
        
        inventarioTable->setItem(row, 0, new QTableWidgetItem(QString::number(rep.getId())));
        inventarioTable->setItem(row, 1, new QTableWidgetItem(rep.getCodigo()));
        inventarioTable->setItem(row, 2, new QTableWidgetItem(rep.getNombre()));
        inventarioTable->setItem(row, 3, new QTableWidgetItem(rep.getCategoria()));
        inventarioTable->setItem(row, 4, new QTableWidgetItem(QString::number(rep.getStockActual())));
        inventarioTable->setItem(row, 5, new QTableWidgetItem(QString("$%1").arg(rep.getPrecioVenta())));
        
        // Marcar stock crítico
        if (rep.esStockCritico()) {
            for (int col = 0; col < inventarioTable->columnCount(); col++) {
                inventarioTable->item(row, col)->setBackground(QColor(255, 200, 200));
            }
        }
    }
    inventarioTable->resizeColumnsToContents();
}

// ==========================================
// AGENDA / CITAS
// ==========================================
void MainWindow::onNuevaCita() {
    CitaDialog dialog(this);
    
    if (dialog.exec() == QDialog::Accepted) {
        try {
            CitaAgenda cita = dialog.getCita();
            db->insertarCita(cita);
            actualizarAgenda();
            actualizarDashboard();
            QMessageBox::information(this, "Éxito", "Cita programada correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
}

void MainWindow::onEditarCita() {
    int citaId = getSelectedCitaId();
    if (citaId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una cita.");
        return;
    }
    
    try {
        CitaAgenda cita = db->obtenerCita(citaId);
        CitaDialog dialog(cita, this);
        
        if (dialog.exec() == QDialog::Accepted) {
            CitaAgenda citaEditada = dialog.getCita();
            citaEditada.setId(citaId);
            db->actualizarCita(citaEditada);
            actualizarAgenda();
            actualizarDashboard();
        }
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
    }
}

void MainWindow::onEliminarCita() {
    int citaId = getSelectedCitaId();
    if (citaId == -1) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una cita.");
        return;
    }
    
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmar",
        "¿Está seguro de eliminar esta cita?",
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        db->eliminarCita(citaId);
        actualizarAgenda();
        actualizarDashboard();
    }
}

void MainWindow::onFechaSeleccionada(const QDate &date) {
    if (!citasDelDia) return;
    
    citasDelDia->clear();
    auto citas = db->obtenerCitasPorFecha(date);
    
    for (const auto &cita : citas) {
        QString texto = QString("%1 - %2 [%3]")
            .arg(cita.getFechaHoraInicio().toString("hh:mm"))
            .arg(cita.getTitulo())
            .arg(cita.getEstadoTexto());
        
        QListWidgetItem *item = new QListWidgetItem(texto);
        item->setData(Qt::UserRole, cita.getId());
        item->setBackground(QColor(cita.getColorCalendario()));
        citasDelDia->addItem(item);
    }
}

void MainWindow::actualizarAgenda() {
    marcarDiasConCitas();
    if (calendario) {
        onFechaSeleccionada(calendario->selectedDate());
    }
}

void MainWindow::marcarDiasConCitas() {
    if (!calendario) return;
    
    // Limpiar formatos anteriores
    calendario->setDateTextFormat(QDate(), QTextCharFormat());
    
    // Obtener el mes actual visible
    QDate fechaActual = calendario->selectedDate();
    QDate primerDia(fechaActual.year(), fechaActual.month(), 1);
    QDate ultimoDia = primerDia.addMonths(1).addDays(-1);
    
    // También revisar el mes anterior y siguiente para el calendario
    primerDia = primerDia.addMonths(-1);
    ultimoDia = ultimoDia.addMonths(2);
    
    // Formato para días con citas
    QTextCharFormat formatoConCita;
    formatoConCita.setBackground(QColor("#ffecd2")); // Naranja muy claro
    formatoConCita.setForeground(QColor("#ea6f15")); // Naranja
    formatoConCita.setFontWeight(QFont::Bold);
    
    // Formato para el día de hoy
    QTextCharFormat formatoHoy;
    formatoHoy.setBackground(QColor("#ea6f15"));
    formatoHoy.setForeground(QColor("#ffffff"));
    formatoHoy.setFontWeight(QFont::Bold);
    
    // Obtener todas las citas del rango
    auto todasCitas = db->obtenerTodasCitas();
    
    QSet<QDate> diasConCitas;
    for (const auto &cita : todasCitas) {
        QDate fechaCita = cita.getFechaHoraInicio().date();
        if (fechaCita >= primerDia && fechaCita <= ultimoDia) {
            diasConCitas.insert(fechaCita);
        }
    }
    
    // Aplicar formato a los días con citas
    for (const QDate &fecha : diasConCitas) {
        if (fecha == QDate::currentDate()) {
            calendario->setDateTextFormat(fecha, formatoHoy);
        } else {
            calendario->setDateTextFormat(fecha, formatoConCita);
        }
    }
    
    // Marcar el día de hoy si no tiene citas
    if (!diasConCitas.contains(QDate::currentDate())) {
        QTextCharFormat formatoHoySinCita;
        formatoHoySinCita.setBackground(QColor("#e8e8e8"));
        formatoHoySinCita.setFontWeight(QFont::Bold);
        calendario->setDateTextFormat(QDate::currentDate(), formatoHoySinCita);
    }
}

// ==========================================
// FACTURACIÓN
// ==========================================
void MainWindow::onNuevaFactura() {
    FacturaDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        try {
            Factura factura = dialog.getFactura();
            db->insertarFactura(factura);
            actualizarTablaFacturas();
            actualizarDashboard();
            QMessageBox::information(this, "Éxito", "Factura creada correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Error al crear factura: %1").arg(e.what()));
        }
    }
}

void MainWindow::onNuevoPresupuesto() {
    PresupuestoDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        try {
            Presupuesto presupuesto = dialog.getPresupuesto();
            db->insertarPresupuesto(presupuesto);
            actualizarTablaFacturas();
            QMessageBox::information(this, "Éxito", "Presupuesto creado correctamente.");
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Error al crear presupuesto: %1").arg(e.what()));
        }
    }
}

void MainWindow::onRegistrarPago() {
    if (!facturasTable || facturasTable->currentRow() < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una factura para registrar el pago.");
        return;
    }
    
    // Obtener ID de la factura seleccionada
    int row = facturasTable->currentRow();
    QString numFactura = facturasTable->item(row, 1)->text();
    
    // Buscar la factura
    auto facturas = db->obtenerTodasFacturas();
    Factura facturaActual;
    bool encontrada = false;
    
    for (const auto &f : facturas) {
        if (f.getNumero() == numFactura) {
            facturaActual = f;
            encontrada = true;
            break;
        }
    }
    
    if (!encontrada) {
        QMessageBox::warning(this, "Advertencia", "No se pudo encontrar la factura seleccionada.");
        return;
    }
    
    if (facturaActual.getEstadoPago() == Factura::PAGADA) {
        QMessageBox::information(this, "Información", "Esta factura ya está pagada completamente.");
        return;
    }
    
    if (facturaActual.getEstadoPago() == Factura::ANULADA) {
        QMessageBox::warning(this, "Advertencia", "No se puede registrar pagos en una factura anulada.");
        return;
    }
    
    // Solicitar monto y método de pago
    double saldoPendiente = facturaActual.getSaldoPendiente();
    bool ok;
    double monto = QInputDialog::getDouble(this, "Registrar Pago",
                                           QString("Saldo pendiente: $%1\nIngrese el monto del pago:")
                                           .arg(saldoPendiente, 0, 'f', 0),
                                           saldoPendiente, 0, saldoPendiente, 0, &ok);
    
    if (!ok) return;
    
    QStringList metodos = {"Efectivo", "Tarjeta", "Transferencia", "Cheque"};
    QString metodo = QInputDialog::getItem(this, "Registrar Pago", "Seleccione método de pago:",
                                          metodos, 0, false, &ok);
    
    if (!ok) return;
    
    // Registrar pago
    if (facturaActual.registrarPago(monto, metodo)) {
        db->actualizarFactura(facturaActual);
        actualizarTablaFacturas();
        actualizarDashboard();
        QMessageBox::information(this, "Éxito", "Pago registrado correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo registrar el pago.");
    }
}

void MainWindow::onVerDetalleFactura() {
    if (!facturasTable || facturasTable->currentRow() < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una factura para ver los detalles.");
        return;
    }
    
    int row = facturasTable->currentRow();
    QString numDoc = facturasTable->item(row, 1)->text();
    QString tipo = facturasTable->item(row, 0)->text(); // Tipo de documento
    
    QString detalles;
    
    // Verificar si es factura o presupuesto
    if (numDoc.startsWith("F-")) {
        // Es una factura
        auto facturas = db->obtenerTodasFacturas();
        for (const auto &f : facturas) {
            if (f.getNumero() == numDoc) {
                detalles = QString(
                    "═══════════════════════════════════\n"
                    "          FACTURA\n"
                    "═══════════════════════════════════\n\n"
                    "Número: %1\n"
                    "Fecha: %2\n"
                    "Vencimiento: %3\n"
                    "Cliente ID: %4\n\n"
                    "▶ ITEMS:\n"
                ).arg(f.getNumero())
                 .arg(f.getFecha().toString("dd/MM/yyyy hh:mm"))
                 .arg(f.getFechaVencimiento().toString("dd/MM/yyyy"))
                 .arg(f.getClienteId());
                
                for (const auto &item : f.getItems()) {
                    detalles += QString("  • %1\n    %2 x $%3 = $%4\n")
                        .arg(item.descripcion)
                        .arg(item.cantidad)
                        .arg(item.precioUnitario, 0, 'f', 0)
                        .arg(item.subtotal, 0, 'f', 0);
                }
                
                detalles += QString(
                    "\n▶ TOTALES:\n"
                    "  Subtotal: $%1\n"
                    "  Descuento: %2%\n"
                    "  IVA: %3%\n"
                    "  TOTAL: $%4\n\n"
                    "▶ ESTADO DE PAGO:\n"
                    "  Estado: %5\n"
                    "  Pagado: $%6\n"
                    "  Saldo: $%7\n"
                ).arg(f.getSubtotal(), 0, 'f', 0)
                 .arg(f.getDescuento(), 0, 'f', 1)
                 .arg(f.getImpuesto(), 0, 'f', 1)
                 .arg(f.getTotal(), 0, 'f', 0)
                 .arg(f.getEstado())
                 .arg(f.getMontoPagado(), 0, 'f', 0)
                 .arg(f.getSaldoPendiente(), 0, 'f', 0);
                
                if (!f.getObservaciones().isEmpty()) {
                    detalles += QString("\n▶ OBSERVACIONES:\n  %1\n").arg(f.getObservaciones());
                }
                
                detalles += "\n═══════════════════════════════════\n";
                break;
            }
        }
    } else if (numDoc.startsWith("P-")) {
        // Es un presupuesto
        auto presupuestos = db->obtenerTodosPresupuestos();
        for (const auto &p : presupuestos) {
            if (p.getNumero() == numDoc) {
                detalles = QString(
                    "═══════════════════════════════════\n"
                    "        PRESUPUESTO\n"
                    "═══════════════════════════════════\n\n"
                    "Número: %1\n"
                    "Fecha: %2\n"
                    "Validez: %3 días\n"
                    "Vence: %4\n"
                    "Cliente ID: %5\n\n"
                    "▶ ITEMS:\n"
                ).arg(p.getNumero())
                 .arg(p.getFecha().toString("dd/MM/yyyy"))
                 .arg(p.getDiasValidez())
                 .arg(p.getFechaVencimiento().toString("dd/MM/yyyy"))
                 .arg(p.getClienteId());
                
                for (const auto &item : p.getItems()) {
                    detalles += QString("  • %1\n    %2 x $%3 = $%4\n")
                        .arg(item.descripcion)
                        .arg(item.cantidad)
                        .arg(item.precioUnitario, 0, 'f', 0)
                        .arg(item.subtotal, 0, 'f', 0);
                }
                
                detalles += QString(
                    "\n▶ TOTALES:\n"
                    "  Subtotal: $%1\n"
                    "  Descuento: %2%\n"
                    "  IVA: %3%\n"
                    "  TOTAL: $%4\n\n"
                    "▶ ESTADO:\n"
                    "  Estado: %5\n"
                ).arg(p.getSubtotal(), 0, 'f', 0)
                 .arg(p.getDescuento(), 0, 'f', 1)
                 .arg(p.getImpuesto(), 0, 'f', 1)
                 .arg(p.getTotal(), 0, 'f', 0)
                 .arg(p.getEstado());
                
                if (!p.getObservaciones().isEmpty()) {
                    detalles += QString("\n▶ OBSERVACIONES:\n  %1\n").arg(p.getObservaciones());
                }
                
                detalles += "\n═══════════════════════════════════\n";
                break;
            }
        }
    }
    
    QMessageBox msgBox;
    msgBox.setWindowTitle("Detalles del Documento");
    msgBox.setText(detalles);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void MainWindow::onAnularFactura() {
    if (!facturasTable || facturasTable->currentRow() < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione una factura para anular.");
        return;
    }
    
    int row = facturasTable->currentRow();
    QString numFactura = facturasTable->item(row, 1)->text();
    
    if (!numFactura.startsWith("F-")) {
        QMessageBox::warning(this, "Advertencia", "Solo se pueden anular facturas, no presupuestos.");
        return;
    }
    
    auto reply = QMessageBox::question(this, "Confirmar Anulación",
                                      QString("¿Está seguro de anular la factura %1?\nEsta acción no se puede deshacer.")
                                      .arg(numFactura),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        auto facturas = db->obtenerTodasFacturas();
        for (auto &f : facturas) {
            if (f.getNumero() == numFactura) {
                if (f.anular()) {
                    db->actualizarFactura(f);
                    actualizarTablaFacturas();
                    actualizarDashboard();
                    QMessageBox::information(this, "Éxito", "Factura anulada correctamente.");
                } else {
                    QMessageBox::warning(this, "Advertencia", "No se puede anular una factura ya pagada.");
                }
                break;
            }
        }
    }
}

void MainWindow::onConvertirPresupuestoAFactura() {
    if (!facturasTable || facturasTable->currentRow() < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un presupuesto para convertir.");
        return;
    }
    
    int row = facturasTable->currentRow();
    QString numDoc = facturasTable->item(row, 1)->text();
    
    if (!numDoc.startsWith("P-")) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un presupuesto (no una factura).");
        return;
    }
    
    auto presupuestos = db->obtenerTodosPresupuestos();
    Presupuesto presupuestoActual;
    bool encontrado = false;
    
    for (auto &p : presupuestos) {
        if (p.getNumero() == numDoc) {
            presupuestoActual = p;
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        QMessageBox::warning(this, "Advertencia", "No se pudo encontrar el presupuesto.");
        return;
    }
    
    if (presupuestoActual.getEstadoPresupuesto() != Presupuesto::APROBADO) {
        QMessageBox::warning(this, "Advertencia", "El presupuesto debe estar aprobado para convertirlo a factura.");
        return;
    }
    
    auto reply = QMessageBox::question(this, "Confirmar Conversión",
                                      QString("¿Convertir el presupuesto %1 a factura?")
                                      .arg(numDoc),
                                      QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        // Crear nueva factura basada en el presupuesto
        auto facturas = db->obtenerTodasFacturas();
        Factura nuevaFactura(QString("F-%1").arg(facturas.size() + 1, 6, 10, QChar('0')), 
                            presupuestoActual.getClienteId());
        
        nuevaFactura.setOrdenTrabajoId(presupuestoActual.getOrdenTrabajoId());
        nuevaFactura.setDescuento(presupuestoActual.getDescuento());
        nuevaFactura.setImpuesto(presupuestoActual.getImpuesto());
        nuevaFactura.setObservaciones(QString("Generada desde presupuesto %1\n%2")
                                     .arg(presupuestoActual.getNumero())
                                     .arg(presupuestoActual.getObservaciones()));
        
        // Copiar items
        for (const auto &item : presupuestoActual.getItems()) {
            nuevaFactura.agregarItem(item);
        }
        
        try {
            db->insertarFactura(nuevaFactura);
            
            // Marcar presupuesto como convertido
            presupuestoActual.convertirAFactura(nuevaFactura.getId());
            db->actualizarPresupuesto(presupuestoActual);
            
            actualizarTablaFacturas();
            actualizarDashboard();
            QMessageBox::information(this, "Éxito", 
                                   QString("Presupuesto convertido a factura %1")
                                   .arg(nuevaFactura.getNumero()));
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", QString("Error al convertir: %1").arg(e.what()));
        }
    }
}

void MainWindow::actualizarTablaFacturas() {
    if (!facturasTable) return;
    
    facturasTable->setRowCount(0);
    
    // Agregar facturas
    auto facturas = db->obtenerTodasFacturas();
    for (const auto &f : facturas) {
        int row = facturasTable->rowCount();
        facturasTable->insertRow(row);
        
        facturasTable->setItem(row, 0, new QTableWidgetItem("FACTURA"));
        facturasTable->setItem(row, 1, new QTableWidgetItem(f.getNumero()));
        facturasTable->setItem(row, 2, new QTableWidgetItem(f.getFecha().toString("dd/MM/yyyy")));
        facturasTable->setItem(row, 3, new QTableWidgetItem(QString("$%L1").arg(f.getTotal(), 0, 'f', 0)));
        facturasTable->setItem(row, 4, new QTableWidgetItem(f.getEstado()));
    }
    
    // Agregar presupuestos
    auto presupuestos = db->obtenerTodosPresupuestos();
    for (const auto &p : presupuestos) {
        int row = facturasTable->rowCount();
        facturasTable->insertRow(row);
        
        facturasTable->setItem(row, 0, new QTableWidgetItem("PRESUPUESTO"));
        facturasTable->setItem(row, 1, new QTableWidgetItem(p.getNumero()));
        facturasTable->setItem(row, 2, new QTableWidgetItem(p.getFecha().toString("dd/MM/yyyy")));
        facturasTable->setItem(row, 3, new QTableWidgetItem(QString("$%L1").arg(p.getTotal(), 0, 'f', 0)));
        facturasTable->setItem(row, 4, new QTableWidgetItem(p.getEstado()));
    }
    
    facturasTable->resizeColumnsToContents();
}

// ==========================================
// DASHBOARD
// ==========================================
void MainWindow::actualizarDashboard() {
    if (lblOrdenesActivas) {
        auto ordenes = db->obtenerOrdenesPorEstado(1);
        lblOrdenesActivas->setText(QString::number(ordenes.size()));
    }
    
    if (lblCitasHoy) {
        auto citas = db->obtenerCitasHoy();
        lblCitasHoy->setText(QString::number(citas.size()));
    }
    
    if (lblStockCritico) {
        auto criticos = db->obtenerRepuestosStockCritico();
        lblStockCritico->setText(QString::number(criticos.size()));
        if (!criticos.isEmpty()) {
            lblStockCritico->setStyleSheet("color: red; font-weight: bold;");
        }
    }
}

// ==========================================
// UTILIDADES ADICIONALES
// ==========================================
int MainWindow::getSelectedOrdenId() {
    if (!ordenesTable) return -1;
    QList<QTableWidgetItem*> items = ordenesTable->selectedItems();
    if (items.isEmpty()) return -1;
    return ordenesTable->item(items.first()->row(), 0)->text().toInt();
}

int MainWindow::getSelectedRepuestoId() {
    if (!inventarioTable) return -1;
    QList<QTableWidgetItem*> items = inventarioTable->selectedItems();
    if (items.isEmpty()) return -1;
    return inventarioTable->item(items.first()->row(), 0)->text().toInt();
}

int MainWindow::getSelectedCitaId() {
    if (!citasDelDia) return -1;
    QListWidgetItem *item = citasDelDia->currentItem();
    if (!item) return -1;
    return item->data(Qt::UserRole).toInt();
}

void MainWindow::setupNuevasPestanas() {
    // Esta función se llamará desde setupUI si el usuario quiere pestañas adicionales
    // Por ahora, las funcionalidades están disponibles a través del menú
}

void MainWindow::setupDashboard() {
    // Inicializar labels del dashboard (se crearán dinámicamente si es necesario)
    lblOrdenesActivas = nullptr;
    lblCitasHoy = nullptr;
    lblStockCritico = nullptr;
}

