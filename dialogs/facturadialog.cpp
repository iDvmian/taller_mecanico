#include "facturadialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QMessageBox>

FacturaDialog::FacturaDialog(QWidget *parent)
    : QDialog(parent), db(DatabaseManager::getInstance()), modoEdicion(false) {
    
    setWindowTitle("Nueva Factura");
    setupUI();
    cargarClientes();
    cargarOrdenes();
    
    // Generar número de factura automático
    auto facturas = db->obtenerTodasFacturas();
    txtNumero->setText(QString("F-%1").arg(facturas.size() + 1, 6, 10, QChar('0')));
}

FacturaDialog::FacturaDialog(const Factura &factura, QWidget *parent)
    : QDialog(parent), db(DatabaseManager::getInstance()), 
      facturaActual(factura), modoEdicion(true) {
    
    setWindowTitle("Editar Factura");
    setupUI();
    cargarClientes();
    cargarOrdenes();
    cargarDatosFactura(factura);
}

void FacturaDialog::setupUI() {
    auto *mainLayout = new QVBoxLayout(this);
    
    // Grupo de información básica
    auto *infoGroup = new QGroupBox("Información de la Factura");
    auto *infoLayout = new QFormLayout(infoGroup);
    
    txtNumero = new QLineEdit();
    txtNumero->setPlaceholderText("F-000001");
    
    cmbCliente = new QComboBox();
    cmbCliente->setMinimumWidth(300);
    
    cmbOrden = new QComboBox();
    cmbOrden->addItem("(Sin orden asociada)", 0);
    
    dteFecha = new QDateTimeEdit(QDateTime::currentDateTime());
    dteFecha->setCalendarPopup(true);
    
    dteFechaVencimiento = new QDateTimeEdit(QDateTime::currentDateTime().addDays(30));
    dteFechaVencimiento->setCalendarPopup(true);
    
    infoLayout->addRow("Número:", txtNumero);
    infoLayout->addRow("Cliente:", cmbCliente);
    infoLayout->addRow("Orden de Trabajo:", cmbOrden);
    infoLayout->addRow("Fecha:", dteFecha);
    infoLayout->addRow("Fecha Vencimiento:", dteFechaVencimiento);
    
    mainLayout->addWidget(infoGroup);
    
    // Grupo de items
    auto *itemsGroup = new QGroupBox("Items de la Factura");
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
    connect(btnAgregarItem, &QPushButton::clicked, this, &FacturaDialog::onAgregarItem);
    connect(btnQuitarItem, &QPushButton::clicked, this, &FacturaDialog::onQuitarItem);
    connect(cmbCliente, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FacturaDialog::onClienteChanged);
    connect(cmbOrden, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &FacturaDialog::onOrdenChanged);
    connect(spnDescuento, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &FacturaDialog::recalcular);
    connect(spnImpuesto, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &FacturaDialog::recalcular);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &FacturaDialog::onAceptar);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    
    setMinimumSize(900, 700);
}

void FacturaDialog::cargarClientes() {
    cmbCliente->clear();
    auto clientes = db->obtenerTodosClientes();
    for (const auto &cliente : clientes) {
        cmbCliente->addItem(QString("%1 - %2").arg(cliente.getRut(), cliente.getNombre()), 
                           cliente.getId());
    }
}

void FacturaDialog::cargarOrdenes() {
    cmbOrden->clear();
    cmbOrden->addItem("(Sin orden asociada)", 0);
    
    auto ordenes = db->obtenerTodasOrdenes();
    for (const auto &orden : ordenes) {
        QString texto = QString("OT-%1 - %2").arg(orden.getId()).arg(orden.getDescripcionProblema());
        cmbOrden->addItem(texto, orden.getId());
    }
}

void FacturaDialog::cargarDatosFactura(const Factura &factura) {
    txtNumero->setText(factura.getNumero());
    
    // Seleccionar cliente
    for (int i = 0; i < cmbCliente->count(); i++) {
        if (cmbCliente->itemData(i).toInt() == factura.getClienteId()) {
            cmbCliente->setCurrentIndex(i);
            break;
        }
    }
    
    // Seleccionar orden
    for (int i = 0; i < cmbOrden->count(); i++) {
        if (cmbOrden->itemData(i).toInt() == factura.getOrdenTrabajoId()) {
            cmbOrden->setCurrentIndex(i);
            break;
        }
    }
    
    dteFecha->setDateTime(factura.getFecha());
    dteFechaVencimiento->setDateTime(factura.getFechaVencimiento());
    
    // Cargar items
    for (const auto &item : factura.getItems()) {
        int row = tablaItems->rowCount();
        tablaItems->insertRow(row);
        
        tablaItems->setItem(row, 0, new QTableWidgetItem(item.descripcion));
        tablaItems->setItem(row, 1, new QTableWidgetItem(QString::number(item.cantidad)));
        tablaItems->setItem(row, 2, new QTableWidgetItem(QString("$ %1").arg(item.precioUnitario, 0, 'f', 0)));
        tablaItems->setItem(row, 3, new QTableWidgetItem(QString("$ %1").arg(item.subtotal, 0, 'f', 0)));
    }
    
    spnDescuento->setValue(factura.getDescuento());
    spnImpuesto->setValue(factura.getImpuesto());
    txtObservaciones->setPlainText(factura.getObservaciones());
    
    recalcular();
}

void FacturaDialog::onAgregarItem() {
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

void FacturaDialog::onQuitarItem() {
    int row = tablaItems->currentRow();
    if (row >= 0) {
        tablaItems->removeRow(row);
        recalcular();
    }
}

void FacturaDialog::onClienteChanged(int index) {
    Q_UNUSED(index);
}

void FacturaDialog::onOrdenChanged(int index) {
    int ordenId = cmbOrden->itemData(index).toInt();
    if (ordenId > 0) {
        // Cargar items de la orden de trabajo
        auto ordenes = db->obtenerTodasOrdenes();
        for (const auto &orden : ordenes) {
            if (orden.getId() == ordenId) {
                // Limpiar tabla
                tablaItems->setRowCount(0);
                
                // Agregar items de la orden
                for (const auto &item : orden.getRepuestosUsados()) {
                    int row = tablaItems->rowCount();
                    tablaItems->insertRow(row);
                    
                    tablaItems->setItem(row, 0, new QTableWidgetItem(item.nombre));
                    tablaItems->setItem(row, 1, new QTableWidgetItem(QString::number(item.cantidad)));
                    tablaItems->setItem(row, 2, new QTableWidgetItem(QString("$ %1").arg(item.precioUnitario, 0, 'f', 0)));
                    tablaItems->setItem(row, 3, new QTableWidgetItem(QString("$ %1").arg(item.subtotal, 0, 'f', 0)));
                }
                
                // Agregar mano de obra
                if (orden.getCostoManoObra() > 0) {
                    int row = tablaItems->rowCount();
                    tablaItems->insertRow(row);
                    
                    tablaItems->setItem(row, 0, new QTableWidgetItem("Mano de Obra"));
                    tablaItems->setItem(row, 1, new QTableWidgetItem("1"));
                    tablaItems->setItem(row, 2, new QTableWidgetItem(QString("$ %1").arg(orden.getCostoManoObra(), 0, 'f', 0)));
                    tablaItems->setItem(row, 3, new QTableWidgetItem(QString("$ %1").arg(orden.getCostoManoObra(), 0, 'f', 0)));
                }
                
                recalcular();
                break;
            }
        }
    }
}

void FacturaDialog::recalcular() {
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

void FacturaDialog::onAceptar() {
    // Validaciones
    if (txtNumero->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Ingrese un número de factura.");
        return;
    }
    
    if (cmbCliente->currentIndex() < 0) {
        QMessageBox::warning(this, "Advertencia", "Seleccione un cliente.");
        return;
    }
    
    if (tablaItems->rowCount() == 0) {
        QMessageBox::warning(this, "Advertencia", "Agregue al menos un item a la factura.");
        return;
    }
    
    accept();
}

Factura FacturaDialog::getFactura() const {
    Factura factura;
    
    if (modoEdicion) {
        factura = facturaActual;
    }
    
    factura.setNumero(txtNumero->text().trimmed());
    factura.setClienteId(cmbCliente->currentData().toInt());
    factura.setOrdenTrabajoId(cmbOrden->currentData().toInt());
    factura.setFecha(dteFecha->dateTime());
    factura.setFechaVencimiento(dteFechaVencimiento->dateTime());
    factura.setDescuento(spnDescuento->value());
    factura.setImpuesto(spnImpuesto->value());
    factura.setObservaciones(txtObservaciones->toPlainText());
    
    // Agregar items
    factura.limpiarItems();
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
        
        factura.agregarItem(item);
    }
    
    return factura;
}

