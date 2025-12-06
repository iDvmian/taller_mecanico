#include "presupuestodialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QMessageBox>

PresupuestoDialog::PresupuestoDialog(QWidget *parent)
    : QDialog(parent), db(DatabaseManager::getInstance()), modoEdicion(false) {
    
    setWindowTitle("Nuevo Presupuesto");
    setupUI();
    cargarClientes();
    
    // Generar número de presupuesto automático
    auto presupuestos = db->obtenerTodosPresupuestos();
    txtNumero->setText(QString("P-%1").arg(presupuestos.size() + 1, 6, 10, QChar('0')));
}

PresupuestoDialog::PresupuestoDialog(const Presupuesto &presupuesto, QWidget *parent)
    : QDialog(parent), db(DatabaseManager::getInstance()), 
      presupuestoActual(presupuesto), modoEdicion(true) {
    
    setWindowTitle("Editar Presupuesto");
    setupUI();
    cargarClientes();
    cargarDatosPresupuesto(presupuesto);
}

void PresupuestoDialog::setupUI() {
    auto *mainLayout = new QVBoxLayout(this);
    
    // Grupo de información básica
    auto *infoGroup = new QGroupBox("Información del Presupuesto");
    auto *infoLayout = new QFormLayout(infoGroup);
    
    txtNumero = new QLineEdit();
    txtNumero->setPlaceholderText("P-000001");
    
    cmbCliente = new QComboBox();
    cmbCliente->setMinimumWidth(300);
    
    dteFecha = new QDateTimeEdit(QDateTime::currentDateTime());
    dteFecha->setCalendarPopup(true);
    
    spnDiasValidez = new QSpinBox();
    spnDiasValidez->setRange(1, 365);
    spnDiasValidez->setValue(15);
    spnDiasValidez->setSuffix(" días");
    
    dteFechaVencimiento = new QDateTimeEdit(QDateTime::currentDateTime().addDays(15));
    dteFechaVencimiento->setCalendarPopup(true);
    dteFechaVencimiento->setEnabled(false);
    
    infoLayout->addRow("Número:", txtNumero);
    infoLayout->addRow("Cliente:", cmbCliente);
    infoLayout->addRow("Fecha:", dteFecha);
    infoLayout->addRow("Días de Validez:", spnDiasValidez);
    infoLayout->addRow("Vence el:", dteFechaVencimiento);
    
    mainLayout->addWidget(infoGroup);
    
    // Grupo de items
    auto *itemsGroup = new QGroupBox("Items del Presupuesto");
    auto *itemsLayout = new QVBoxLayout(itemsGroup);
    
    // Tabla de items
    tablaItems = new QTableWidget(0, 4);
    tablaItems->setHorizontalHeaderLabels({"Descripción", "Cantidad", "Precio Unit.", "Subtotal"});
    tablaItems->horizontalHeader()->setStretchLastSection(true);
    tablaItems->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tablaItems->setMinimumHeight(200);
    
    itemsLayout->addWidget(tablaItems);
    
    // Controles para agregar items
    auto *addItemLayout = new QHBoxLayout();
    
    txtItemDescripcion = new QLineEdit();
    txtItemDescripcion->setPlaceholderText("Descripción del item");
    
    spnItemCantidad = new QSpinBox();
    spnItemCantidad->setRange(1, 1000);
    spnItemCantidad->setValue(1);
    spnItemCantidad->setPrefix("Cant: ");
    
    spnItemPrecio = new QDoubleSpinBox();
    spnItemPrecio->setRange(0, 9999999);
    spnItemPrecio->setPrefix("$ ");
    spnItemPrecio->setDecimals(0);
    
    btnAgregarItem = new QPushButton("Agregar Item");
    btnQuitarItem = new QPushButton("Quitar Item");
    
    addItemLayout->addWidget(new QLabel("Item:"));
    addItemLayout->addWidget(txtItemDescripcion, 2);
    addItemLayout->addWidget(spnItemCantidad);
    addItemLayout->addWidget(spnItemPrecio);
    addItemLayout->addWidget(btnAgregarItem);
    addItemLayout->addWidget(btnQuitarItem);
    
    itemsLayout->addLayout(addItemLayout);
    mainLayout->addWidget(itemsGroup);
    
    // Grupo de totales
    auto *totalesGroup = new QGroupBox("Totales");
    auto *totalesLayout = new QFormLayout(totalesGroup);
    
    spnDescuento = new QDoubleSpinBox();
    spnDescuento->setRange(0, 100);
    spnDescuento->setSuffix(" %");
    
    spnImpuesto = new QDoubleSpinBox();
    spnImpuesto->setRange(0, 100);
    spnImpuesto->setValue(19);  // IVA por defecto
    spnImpuesto->setSuffix(" %");
    
    lblSubtotal = new QLabel("$ 0");
    lblSubtotal->setStyleSheet("font-weight: bold;");
    
    lblTotal = new QLabel("$ 0");
    lblTotal->setStyleSheet("font-size: 16pt; font-weight: bold; color: #ea6f15;");
    
    totalesLayout->addRow("Descuento:", spnDescuento);
    totalesLayout->addRow("Impuesto (IVA):", spnImpuesto);
    totalesLayout->addRow("Subtotal:", lblSubtotal);
    totalesLayout->addRow("TOTAL:", lblTotal);
    
    mainLayout->addWidget(totalesGroup);
    
    // Observaciones
    auto *obsGroup = new QGroupBox("Observaciones");
    auto *obsLayout = new QVBoxLayout(obsGroup);
    txtObservaciones = new QTextEdit();
    txtObservaciones->setMaximumHeight(80);
    obsLayout->addWidget(txtObservaciones);
    mainLayout->addWidget(obsGroup);
    
    // Botones
    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel);
    mainLayout->addWidget(buttonBox);
    
    // Conexiones
    connect(btnAgregarItem, &QPushButton::clicked, this, &PresupuestoDialog::onAgregarItem);
    connect(btnQuitarItem, &QPushButton::clicked, this, &PresupuestoDialog::onQuitarItem);
    connect(cmbCliente, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PresupuestoDialog::onClienteChanged);
    connect(spnDiasValidez, QOverload<int>::of(&QSpinBox::valueChanged), this, &PresupuestoDialog::onDiasValidezChanged);
    connect(spnDescuento, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PresupuestoDialog::recalcular);
    connect(spnImpuesto, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &PresupuestoDialog::recalcular);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &PresupuestoDialog::onAceptar);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    setMinimumSize(900, 700);
}

void PresupuestoDialog::cargarClientes() {
    cmbCliente->clear();
    auto clientes = db->obtenerTodosClientes();
    for (const auto &cliente : clientes) {
        cmbCliente->addItem(QString("%1 - %2").arg(cliente.getRut(), cliente.getNombre()), 
                           cliente.getId());
    }
}

void PresupuestoDialog::cargarDatosPresupuesto(const Presupuesto &presupuesto) {
    txtNumero->setText(presupuesto.getNumero());
    
    // Seleccionar cliente
    for (int i = 0; i < cmbCliente->count(); i++) {
        if (cmbCliente->itemData(i).toInt() == presupuesto.getClienteId()) {
            cmbCliente->setCurrentIndex(i);
            break;
        }
    }
    
    dteFecha->setDateTime(presupuesto.getFecha());
    spnDiasValidez->setValue(presupuesto.getDiasValidez());
    dteFechaVencimiento->setDateTime(presupuesto.getFechaVencimiento());
    
    // Cargar items
    for (const auto &item : presupuesto.getItems()) {
        int row = tablaItems->rowCount();
        tablaItems->insertRow(row);
        
        tablaItems->setItem(row, 0, new QTableWidgetItem(item.descripcion));
        tablaItems->setItem(row, 1, new QTableWidgetItem(QString::number(item.cantidad)));
        tablaItems->setItem(row, 2, new QTableWidgetItem(QString("$ %1").arg(item.precioUnitario, 0, 'f', 0)));
        tablaItems->setItem(row, 3, new QTableWidgetItem(QString("$ %1").arg(item.subtotal, 0, 'f', 0)));
    }
    
    spnDescuento->setValue(presupuesto.getDescuento());
    spnImpuesto->setValue(presupuesto.getImpuesto());
    txtObservaciones->setPlainText(presupuesto.getObservaciones());
    
    recalcular();
}

void PresupuestoDialog::onAgregarItem() {
    QString descripcion = txtItemDescripcion->text().trimmed();
    if (descripcion.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese una descripción para el item.");
        return;
    }
    
    int cantidad = spnItemCantidad->value();
    double precio = spnItemPrecio->value();
    double subtotal = cantidad * precio;
    
    int row = tablaItems->rowCount();
    tablaItems->insertRow(row);
    
    tablaItems->setItem(row, 0, new QTableWidgetItem(descripcion));
    tablaItems->setItem(row, 1, new QTableWidgetItem(QString::number(cantidad)));
    tablaItems->setItem(row, 2, new QTableWidgetItem(QString("$ %1").arg(precio, 0, 'f', 0)));
    tablaItems->setItem(row, 3, new QTableWidgetItem(QString("$ %1").arg(subtotal, 0, 'f', 0)));
    
    // Limpiar campos
    txtItemDescripcion->clear();
    spnItemCantidad->setValue(1);
    spnItemPrecio->setValue(0);
    
    recalcular();
}

void PresupuestoDialog::onQuitarItem() {
    int row = tablaItems->currentRow();
    if (row >= 0) {
        tablaItems->removeRow(row);
        recalcular();
    }
}

void PresupuestoDialog::onClienteChanged(int index) {
    Q_UNUSED(index);
}

void PresupuestoDialog::onDiasValidezChanged(int dias) {
    dteFechaVencimiento->setDateTime(dteFecha->dateTime().addDays(dias));
}

void PresupuestoDialog::recalcular() {
    double subtotal = 0;
    
    for (int i = 0; i < tablaItems->rowCount(); i++) {
        QString valorStr = tablaItems->item(i, 3)->text();
        valorStr.remove("$ ").remove(",");
        subtotal += valorStr.toDouble();
    }
    
    double descuento = spnDescuento->value();
    double impuesto = spnImpuesto->value();
    
    double base = subtotal - (subtotal * descuento / 100);
    double total = base + (base * impuesto / 100);
    
    lblSubtotal->setText(QString("$ %L1").arg(subtotal, 0, 'f', 0));
    lblTotal->setText(QString("$ %L1").arg(total, 0, 'f', 0));
}

void PresupuestoDialog::onAceptar() {
    // Validaciones
    if (txtNumero->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese un número de presupuesto.");
        return;
    }
    
    if (cmbCliente->currentIndex() < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente.");
        return;
    }
    
    if (tablaItems->rowCount() == 0) {
        QMessageBox::warning(this, "Advertencia", "Agregue al menos un item al presupuesto.");
        return;
    }
    
    accept();
}

Presupuesto PresupuestoDialog::getPresupuesto() const {
    Presupuesto presupuesto;
    
    if (modoEdicion) {
        presupuesto = presupuestoActual;
    }
    
    presupuesto.setNumero(txtNumero->text().trimmed());
    presupuesto.setClienteId(cmbCliente->currentData().toInt());
    presupuesto.setFecha(dteFecha->dateTime());
    presupuesto.setDiasValidez(spnDiasValidez->value());
    presupuesto.setFechaVencimiento(dteFechaVencimiento->dateTime());
    presupuesto.setDescuento(spnDescuento->value());
    presupuesto.setImpuesto(spnImpuesto->value());
    presupuesto.setObservaciones(txtObservaciones->toPlainText());
    
    // Agregar items
    presupuesto.limpiarItems();
    for (int i = 0; i < tablaItems->rowCount(); i++) {
        ItemDocumento item;
        item.descripcion = tablaItems->item(i, 0)->text();
        item.cantidad = tablaItems->item(i, 1)->text().toInt();
        
        QString precioStr = tablaItems->item(i, 2)->text();
        precioStr.remove("$ ").remove(",");
        item.precioUnitario = precioStr.toDouble();
        
        QString subtotalStr = tablaItems->item(i, 3)->text();
        subtotalStr.remove("$ ").remove(",");
        item.subtotal = subtotalStr.toDouble();
        
        presupuesto.agregarItem(item);
    }
    
    return presupuesto;
}


