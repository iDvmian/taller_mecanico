#include "ordentrabajodialog.h"
#include "../database/databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QTabWidget>
#include <QSpinBox>

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

    costoRepuestosLabel = new QLabel("$ 0");
    costoRepuestosLabel->setStyleSheet("font-size: 13px; color: #555555;");
    costoFormLayout->addRow("Repuestos:", costoRepuestosLabel);

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
    
    repuestosTable = new QTableWidget(0, 5);
    repuestosTable->setHorizontalHeaderLabels({"Repuesto", "Cantidad", "Precio Unit.", "Subtotal", ""});
    repuestosTable->horizontalHeader()->setStretchLastSection(false);
    repuestosTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    repuestosTable->setColumnWidth(1, 80);
    repuestosTable->setColumnWidth(2, 100);
    repuestosTable->setColumnWidth(3, 100);
    repuestosTable->setColumnWidth(4, 80);
    repuestosTable->setMaximumHeight(150);
    repLayout->addWidget(repuestosTable);

    QHBoxLayout *btnRepLayout = new QHBoxLayout();
    QPushButton *agregarRepBtn = new QPushButton("+ Agregar Repuesto");
    connect(agregarRepBtn, &QPushButton::clicked, this, &OrdenTrabajoDialog::agregarRepuesto);
    btnRepLayout->addWidget(agregarRepBtn);
    btnRepLayout->addStretch();
    repLayout->addLayout(btnRepLayout);

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
    
    // Cargar repuestos
    repuestosAgregados = ordenTrabajo.getRepuestosUsados();
    cargarRepuestosTabla();
    
    actualizarTotal();
}

void OrdenTrabajoDialog::cargarRepuestosTabla() {
    repuestosTable->setRowCount(0);
    
    for (int i = 0; i < repuestosAgregados.size(); ++i) {
        const RepuestoUsado &rep = repuestosAgregados[i];
        int row = repuestosTable->rowCount();
        repuestosTable->insertRow(row);
        
        repuestosTable->setItem(row, 0, new QTableWidgetItem(rep.nombre));
        repuestosTable->setItem(row, 1, new QTableWidgetItem(QString::number(rep.cantidad)));
        repuestosTable->setItem(row, 2, new QTableWidgetItem(QString("$ %1").arg(rep.precioUnitario, 0, 'f', 0)));
        repuestosTable->setItem(row, 3, new QTableWidgetItem(QString("$ %1").arg(rep.subtotal, 0, 'f', 0)));
        
        // Botón quitar
        QPushButton *btnQuitar = new QPushButton("✕");
        btnQuitar->setStyleSheet("background-color: #e74c3c; font-weight: bold; padding: 4px;");
        btnQuitar->setMaximumWidth(60);
        btnQuitar->setProperty("row", i);
        connect(btnQuitar, &QPushButton::clicked, this, &OrdenTrabajoDialog::quitarRepuesto);
        repuestosTable->setCellWidget(row, 4, btnQuitar);
    }
}

double OrdenTrabajoDialog::calcularTotalRepuestos() const {
    double total = 0;
    for (const RepuestoUsado &rep : repuestosAgregados) {
        total += rep.subtotal;
    }
    return total;
}

void OrdenTrabajoDialog::actualizarTotal() {
    double manoObra = costoManoObraSpin->value();
    double repuestos = calcularTotalRepuestos();
    double subtotal = manoObra + repuestos;
    double descuento = descuentoSpin->value();
    double total = subtotal - (subtotal * descuento / 100);
    
    costoRepuestosLabel->setText(QString("$ %1").arg(repuestos, 0, 'f', 0));
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
    ordenTrabajo.setRepuestosUsados(repuestosAgregados);

    accept();
}

void OrdenTrabajoDialog::agregarRepuesto() {
    DatabaseManager *db = DatabaseManager::getInstance();
    QVector<Repuesto> repuestos = db->obtenerTodosRepuestos();
    
    if (repuestos.isEmpty()) {
        QMessageBox::warning(this, "Sin repuestos", "No hay repuestos registrados en el inventario.");
        return;
    }
    
    // Crear diálogo personalizado
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Agregar Repuesto");
    dialog->setMinimumWidth(500);
    dialog->setStyleSheet(styleSheet());
    
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    
    QGroupBox *group = new QGroupBox("Seleccionar Repuesto");
    QFormLayout *formLayout = new QFormLayout(group);
    
    // ComboBox de repuestos
    QComboBox *repuestoCombo = new QComboBox();
    for (const Repuesto &r : repuestos) {
        QString texto = QString("%1 - %2 (Stock: %3) - $%4")
                           .arg(r.getCodigo())
                           .arg(r.getNombre())
                           .arg(r.getStockActual())
                           .arg(r.getPrecioVenta(), 0, 'f', 0);
        repuestoCombo->addItem(texto, r.getId());
    }
    formLayout->addRow("Repuesto:", repuestoCombo);
    
    // SpinBox cantidad
    QSpinBox *cantidadSpin = new QSpinBox();
    cantidadSpin->setMinimum(1);
    cantidadSpin->setMaximum(1000);
    cantidadSpin->setValue(1);
    formLayout->addRow("Cantidad:", cantidadSpin);
    
    // Label stock disponible
    QLabel *stockLabel = new QLabel();
    stockLabel->setStyleSheet("color: #555555; font-weight: normal;");
    
    // Actualizar stock al cambiar repuesto
    auto actualizarStock = [&]() {
        int idx = repuestoCombo->currentIndex();
        if (idx >= 0) {
            int stock = repuestos[idx].getStockActual();
            stockLabel->setText(QString("Stock disponible: %1 unidades").arg(stock));
            cantidadSpin->setMaximum(stock > 0 ? stock : 1);
            
            if (stock <= 0) {
                stockLabel->setText("⚠️ SIN STOCK");
                stockLabel->setStyleSheet("color: #e74c3c; font-weight: bold;");
            } else if (repuestos[idx].esStockCritico()) {
                stockLabel->setStyleSheet("color: #e67e22; font-weight: bold;");
            } else {
                stockLabel->setStyleSheet("color: #27ae60; font-weight: normal;");
            }
        }
    };
    
    connect(repuestoCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), actualizarStock);
    actualizarStock();
    
    formLayout->addRow("", stockLabel);
    layout->addWidget(group);
    
    // Botones
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnCancelar = new QPushButton("Cancelar");
    QPushButton *btnAgregar = new QPushButton("Agregar");
    btnAgregar->setDefault(true);
    
    connect(btnCancelar, &QPushButton::clicked, dialog, &QDialog::reject);
    connect(btnAgregar, &QPushButton::clicked, dialog, &QDialog::accept);
    
    btnLayout->addStretch();
    btnLayout->addWidget(btnCancelar);
    btnLayout->addWidget(btnAgregar);
    layout->addLayout(btnLayout);
    
    if (dialog->exec() == QDialog::Accepted) {
        int idx = repuestoCombo->currentIndex();
        if (idx < 0) return;
        
        const Repuesto &repuesto = repuestos[idx];
        int cantidad = cantidadSpin->value();
        
        // Verificar stock
        if (cantidad > repuesto.getStockActual()) {
            QMessageBox::warning(this, "Stock insuficiente", 
                               QString("No hay suficiente stock. Disponible: %1").arg(repuesto.getStockActual()));
            return;
        }
        
        // Crear RepuestoUsado
        RepuestoUsado ru;
        ru.repuestoId = repuesto.getId();
        ru.nombre = repuesto.getNombre();
        ru.cantidad = cantidad;
        ru.precioUnitario = repuesto.getPrecioVenta();
        ru.subtotal = cantidad * repuesto.getPrecioVenta();
        
        // Agregar a la lista
        repuestosAgregados.append(ru);
        
        // Actualizar tabla y total
        cargarRepuestosTabla();
        actualizarTotal();
    }
    
    delete dialog;
}

void OrdenTrabajoDialog::quitarRepuesto() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    
    int row = btn->property("row").toInt();
    
    if (row >= 0 && row < repuestosAgregados.size()) {
        QString nombre = repuestosAgregados[row].nombre;
        
        auto reply = QMessageBox::question(this, "Confirmar", 
                                          QString("¿Quitar '%1' de la orden?").arg(nombre),
                                          QMessageBox::Yes | QMessageBox::No);
        
        if (reply == QMessageBox::Yes) {
            repuestosAgregados.removeAt(row);
            cargarRepuestosTabla();
            actualizarTotal();
        }
    }
}

