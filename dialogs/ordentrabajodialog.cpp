#include "ordentrabajodialog.h"
#include "../database/databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QTabWidget>

OrdenTrabajoDialog::OrdenTrabajoDialog(QWidget *parent)
    : QDialog(parent), modoEdicion(false) {
    setupUI();
    setWindowTitle("Nueva Orden de Trabajo");
    
    // Generar número de OT
    DatabaseManager *db = DatabaseManager::getInstance();
    numeroEdit->setText(db->generarNumeroOT());
    fechaIngresoEdit->setDateTime(QDateTime::currentDateTime());
    fechaEstimadaEdit->setDateTime(QDateTime::currentDateTime().addDays(3));
}

OrdenTrabajoDialog::OrdenTrabajoDialog(const OrdenTrabajo &ot, QWidget *parent)
    : QDialog(parent), ordenTrabajo(ot), modoEdicion(true) {
    setupUI();
    setWindowTitle("Editar Orden de Trabajo: " + ot.getNumero());
    cargarDatos();
}

void OrdenTrabajoDialog::setupUI() {
    setMinimumSize(750, 650);
    setStyleSheet(R"(
        QDialog { background-color: #f5f5f5; }
        QLabel { color: #333333; font-size: 13px; font-weight: bold; }
        QTabWidget::pane { border: 1px solid #d0d0d0; background-color: #ffffff; border-radius: 6px; }
        QTabBar::tab { background-color: #e8e8e8; color: #555555; padding: 10px 20px; border-radius: 6px; margin-right: 3px; font-weight: 600; }
        QTabBar::tab:selected { background-color: #ea6f15; color: #ffffff; }
        QTabBar::tab:hover:!selected { background-color: #d0d0d0; }
        QGroupBox { 
            background-color: #ffffff; border: 1px solid #d0d0d0; border-radius: 6px; 
            margin-top: 16px; padding: 16px 12px 12px 12px; font-weight: bold; color: #ea6f15;
        }
        QGroupBox::title { subcontrol-origin: margin; left: 16px; padding: 0 8px; background-color: #ffffff; }
        QLineEdit, QTextEdit, QSpinBox, QDoubleSpinBox, QComboBox, QDateTimeEdit {
            background-color: #ffffff; border: 1px solid #c0c0c0; border-radius: 4px;
            padding: 5px 10px; color: #333333; font-size: 13px; min-height: 18px;
        }
        QLineEdit:focus, QTextEdit:focus, QComboBox:focus, QDateTimeEdit:focus, QDoubleSpinBox:focus {
            border: 2px solid #ea6f15; background-color: #fffaf5;
        }
        QComboBox::drop-down { border: none; width: 30px; }
        QComboBox QAbstractItemView { background-color: #ffffff; color: #333333; selection-background-color: #ea6f15; selection-color: #ffffff; }
        QDateTimeEdit::drop-down { border: none; width: 30px; }
        QTableWidget { background-color: #ffffff; border: 1px solid #d0d0d0; border-radius: 6px; color: #333333; }
        QHeaderView::section { background-color: #f8f8f8; color: #ea6f15; padding: 8px; border: none; border-bottom: 2px solid #ea6f15; }
        QPushButton {
            background-color: #ea6f15; color: #ffffff; border: none; border-radius: 6px; 
            padding: 12px 24px; font-size: 13px; font-weight: bold;
        }
        QPushButton:hover { background-color: #f58025; }
    )");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QTabWidget *tabs = new QTabWidget();

    // Tab 1: Información General
    QWidget *infoTab = new QWidget();
    QVBoxLayout *infoLayout = new QVBoxLayout(infoTab);

    // Encabezado
    QGroupBox *headerGroup = new QGroupBox("Información de la Orden");
    QFormLayout *headerLayout = new QFormLayout(headerGroup);

    numeroEdit = new QLineEdit();
    numeroEdit->setReadOnly(true);
    numeroEdit->setStyleSheet("background-color: #f0f0f0;");
    headerLayout->addRow("N° OT:", numeroEdit);

    clienteCombo = new QComboBox();
    connect(clienteCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &OrdenTrabajoDialog::clienteSeleccionado);
    headerLayout->addRow("Cliente:", clienteCombo);

    vehiculoCombo = new QComboBox();
    headerLayout->addRow("Vehículo:", vehiculoCombo);

    estadoCombo = new QComboBox();
    estadoCombo->addItems({"Pendiente", "En Proceso", "Esperando Repuestos", 
                           "Completada", "Entregada", "Cancelada"});
    headerLayout->addRow("Estado:", estadoCombo);

    infoLayout->addWidget(headerGroup);

    // Fechas
    QGroupBox *fechasGroup = new QGroupBox("Fechas");
    QHBoxLayout *fechasLayout = new QHBoxLayout(fechasGroup);

    QFormLayout *fechaIngresoLayout = new QFormLayout();
    fechaIngresoEdit = new QDateTimeEdit();
    fechaIngresoEdit->setCalendarPopup(true);
    fechaIngresoLayout->addRow("Ingreso:", fechaIngresoEdit);
    fechasLayout->addLayout(fechaIngresoLayout);

    QFormLayout *fechaEstimadaLayout = new QFormLayout();
    fechaEstimadaEdit = new QDateTimeEdit();
    fechaEstimadaEdit->setCalendarPopup(true);
    fechaEstimadaLayout->addRow("Entrega Est.:", fechaEstimadaEdit);
    fechasLayout->addLayout(fechaEstimadaLayout);

    infoLayout->addWidget(fechasGroup);

    // Problema
    QGroupBox *problemaGroup = new QGroupBox("Descripción del Problema");
    QVBoxLayout *problemaLayout = new QVBoxLayout(problemaGroup);
    descripcionEdit = new QTextEdit();
    descripcionEdit->setMaximumHeight(80);
    descripcionEdit->setPlaceholderText("Describa el problema reportado por el cliente...");
    problemaLayout->addWidget(descripcionEdit);
    infoLayout->addWidget(problemaGroup);

    tabs->addTab(infoTab, "Información");

    // Tab 2: Diagnóstico y Trabajo
    QWidget *trabajoTab = new QWidget();
    QVBoxLayout *trabajoLayout = new QVBoxLayout(trabajoTab);

    QGroupBox *diagGroup = new QGroupBox("Diagnóstico");
    QVBoxLayout *diagLayout = new QVBoxLayout(diagGroup);
    diagnosticoEdit = new QTextEdit();
    diagnosticoEdit->setMaximumHeight(100);
    diagnosticoEdit->setPlaceholderText("Diagnóstico técnico del problema...");
    diagLayout->addWidget(diagnosticoEdit);
    trabajoLayout->addWidget(diagGroup);

    QGroupBox *trabajoRealGroup = new QGroupBox("Trabajo Realizado");
    QVBoxLayout *trabajoRealLayout = new QVBoxLayout(trabajoRealGroup);
    trabajoEdit = new QTextEdit();
    trabajoEdit->setPlaceholderText("Descripción del trabajo realizado...");
    trabajoRealLayout->addWidget(trabajoEdit);
    trabajoLayout->addWidget(trabajoRealGroup);

    QGroupBox *obsGroup = new QGroupBox("Observaciones");
    QVBoxLayout *obsLayout = new QVBoxLayout(obsGroup);
    observacionesEdit = new QTextEdit();
    observacionesEdit->setMaximumHeight(60);
    obsLayout->addWidget(observacionesEdit);
    trabajoLayout->addWidget(obsGroup);

    tabs->addTab(trabajoTab, "Trabajo");

    // Tab 3: Costos
    QWidget *costosTab = new QWidget();
    QVBoxLayout *costosLayout = new QVBoxLayout(costosTab);

    QGroupBox *costoGroup = new QGroupBox("Costos");
    QFormLayout *costoFormLayout = new QFormLayout(costoGroup);

    costoManoObraSpin = new QDoubleSpinBox();
    costoManoObraSpin->setPrefix("$ ");
    costoManoObraSpin->setMaximum(99999999);
    costoManoObraSpin->setDecimals(0);
    connect(costoManoObraSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &OrdenTrabajoDialog::actualizarTotal);
    costoFormLayout->addRow("Mano de Obra:", costoManoObraSpin);

    descuentoSpin = new QDoubleSpinBox();
    descuentoSpin->setSuffix(" %");
    descuentoSpin->setMaximum(100);
    connect(descuentoSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &OrdenTrabajoDialog::actualizarTotal);
    costoFormLayout->addRow("Descuento:", descuentoSpin);

    totalLabel = new QLabel("$ 0");
    totalLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2ecc71;");
    costoFormLayout->addRow("TOTAL:", totalLabel);

    costosLayout->addWidget(costoGroup);

    // Tabla de repuestos
    QGroupBox *repuestosGroup = new QGroupBox("Repuestos Utilizados");
    QVBoxLayout *repLayout = new QVBoxLayout(repuestosGroup);
    
    repuestosTable = new QTableWidget(0, 4);
    repuestosTable->setHorizontalHeaderLabels({"Repuesto", "Cantidad", "Precio", "Subtotal"});
    repuestosTable->horizontalHeader()->setStretchLastSection(true);
    repuestosTable->setMaximumHeight(150);
    repLayout->addWidget(repuestosTable);

    QPushButton *agregarRepBtn = new QPushButton("+ Agregar Repuesto");
    connect(agregarRepBtn, &QPushButton::clicked, this, &OrdenTrabajoDialog::agregarRepuesto);
    repLayout->addWidget(agregarRepBtn);

    costosLayout->addWidget(repuestosGroup);
    costosLayout->addStretch();

    tabs->addTab(costosTab, "Costos");

    mainLayout->addWidget(tabs);

    // Botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *cancelButton = new QPushButton("Cancelar");
    QPushButton *acceptButton = new QPushButton(modoEdicion ? "Guardar Cambios" : "Crear Orden");
    acceptButton->setDefault(true);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(acceptButton, &QPushButton::clicked, this, &OrdenTrabajoDialog::aceptar);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(acceptButton);
    mainLayout->addLayout(buttonLayout);

    cargarClientes();
}

void OrdenTrabajoDialog::cargarClientes() {
    DatabaseManager *db = DatabaseManager::getInstance();
    clientes = db->obtenerTodosClientes();

    clienteCombo->clear();
    clienteCombo->addItem("-- Seleccione Cliente --", 0);
    for (const Cliente &c : clientes) {
        clienteCombo->addItem(c.getNombre() + " " + c.getApellido() + " (" + c.getRut() + ")", c.getId());
    }
}

void OrdenTrabajoDialog::clienteSeleccionado(int index) {
    vehiculoCombo->clear();
    if (index <= 0) return;

    int clienteId = clienteCombo->currentData().toInt();
    cargarVehiculos(clienteId);
}

void OrdenTrabajoDialog::cargarVehiculos(int clienteId) {
    DatabaseManager *db = DatabaseManager::getInstance();
    auto vehiculos = db->obtenerVehiculosCliente(clienteId);

    vehiculoCombo->addItem("-- Seleccione Vehículo --", 0);
    for (const auto &v : vehiculos) {
        vehiculoCombo->addItem(v->getPatente() + " - " + v->getModelo(), v->getId());
    }
}

void OrdenTrabajoDialog::cargarDatos() {
    numeroEdit->setText(ordenTrabajo.getNumero());
    
    // Buscar y seleccionar cliente
    for (int i = 0; i < clienteCombo->count(); i++) {
        if (clienteCombo->itemData(i).toInt() == ordenTrabajo.getClienteId()) {
            clienteCombo->setCurrentIndex(i);
            break;
        }
    }
    
    // Cargar vehículos y seleccionar
    cargarVehiculos(ordenTrabajo.getClienteId());
    for (int i = 0; i < vehiculoCombo->count(); i++) {
        if (vehiculoCombo->itemData(i).toInt() == ordenTrabajo.getVehiculoId()) {
            vehiculoCombo->setCurrentIndex(i);
            break;
        }
    }

    estadoCombo->setCurrentIndex(static_cast<int>(ordenTrabajo.getEstado()));
    fechaIngresoEdit->setDateTime(ordenTrabajo.getFechaIngreso());
    fechaEstimadaEdit->setDateTime(ordenTrabajo.getFechaEstimadaEntrega());
    descripcionEdit->setPlainText(ordenTrabajo.getDescripcionProblema());
    diagnosticoEdit->setPlainText(ordenTrabajo.getDiagnostico());
    trabajoEdit->setPlainText(ordenTrabajo.getTrabajoRealizado());
    costoManoObraSpin->setValue(ordenTrabajo.getCostoManoObra());
    descuentoSpin->setValue(ordenTrabajo.getDescuento());
    observacionesEdit->setPlainText(ordenTrabajo.getObservaciones());
    
    actualizarTotal();
}

void OrdenTrabajoDialog::actualizarTotal() {
    double manoObra = costoManoObraSpin->value();
    double descuento = descuentoSpin->value();
    double total = manoObra - (manoObra * descuento / 100);
    totalLabel->setText(QString("$ %1").arg(total, 0, 'f', 0));
}

OrdenTrabajo OrdenTrabajoDialog::getOrdenTrabajo() const {
    return ordenTrabajo;
}

void OrdenTrabajoDialog::aceptar() {
    if (clienteCombo->currentData().toInt() == 0) {
        QMessageBox::warning(this, "Error", "Debe seleccionar un cliente.");
        return;
    }
    if (vehiculoCombo->currentData().toInt() == 0) {
        QMessageBox::warning(this, "Error", "Debe seleccionar un vehículo.");
        return;
    }
    if (descripcionEdit->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe ingresar una descripción del problema.");
        return;
    }

    ordenTrabajo.setNumero(numeroEdit->text());
    ordenTrabajo.setClienteId(clienteCombo->currentData().toInt());
    ordenTrabajo.setVehiculoId(vehiculoCombo->currentData().toInt());
    ordenTrabajo.setEstadoFromInt(estadoCombo->currentIndex());
    ordenTrabajo.setFechaIngreso(fechaIngresoEdit->dateTime());
    ordenTrabajo.setFechaEstimadaEntrega(fechaEstimadaEdit->dateTime());
    ordenTrabajo.setDescripcionProblema(descripcionEdit->toPlainText().trimmed());
    ordenTrabajo.setDiagnostico(diagnosticoEdit->toPlainText().trimmed());
    ordenTrabajo.setTrabajoRealizado(trabajoEdit->toPlainText().trimmed());
    ordenTrabajo.setCostoManoObra(costoManoObraSpin->value());
    ordenTrabajo.setDescuento(descuentoSpin->value());
    ordenTrabajo.setObservaciones(observacionesEdit->toPlainText().trimmed());

    accept();
}

void OrdenTrabajoDialog::agregarRepuesto() {
    QMessageBox::information(this, "Info", "Función de agregar repuesto próximamente disponible.\nPor ahora puede agregar el costo en Mano de Obra.");
}

