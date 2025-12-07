#include "repuestodialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

RepuestoDialog::RepuestoDialog(QWidget *parent)
    : QDialog(parent), modoEdicion(false) {
    setupUI();
    setWindowTitle("Nuevo Repuesto");
}

RepuestoDialog::RepuestoDialog(const Repuesto &repuesto, QWidget *parent)
    : QDialog(parent), repuesto(repuesto), modoEdicion(true) {
    setupUI();
    setWindowTitle("Editar Repuesto");
    cargarDatos();
}

void RepuestoDialog::setupUI() {
    setMinimumWidth(500);
    setStyleSheet(R"(
        QDialog { background-color: #f5f5f5; }
        QLabel { color: #333333; font-size: 13px; font-weight: bold; }
        QGroupBox { 
            background-color: #ffffff; 
            border: 1px solid #d0d0d0; 
            border-radius: 6px; 
            margin-top: 16px; 
            padding: 16px 12px 12px 12px;
            font-weight: bold;
            color: #ea6f15;
        }
        QGroupBox::title { subcontrol-origin: margin; left: 16px; padding: 0 8px; background-color: #ffffff; }
        QLineEdit, QTextEdit, QSpinBox, QDoubleSpinBox, QComboBox {
            background-color: #ffffff;
            border: 1px solid #c0c0c0;
            border-radius: 4px;
            padding: 5px 10px;
            color: #333333;
            font-size: 13px;
            min-height: 18px;
        }
        QLineEdit:focus, QTextEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus {
            border: 2px solid #ea6f15;
            background-color: #fffaf5;
        }
        QComboBox::drop-down { border: none; width: 30px; }
        QComboBox::down-arrow { image: none; border-left: 5px solid transparent; border-right: 5px solid transparent; border-top: 6px solid #ea6f15; }
        QComboBox QAbstractItemView { background-color: #ffffff; color: #333333; selection-background-color: #ea6f15; selection-color: #ffffff; }
        QPushButton {
            background-color: #ea6f15; color: #ffffff; border: none; border-radius: 6px; 
            padding: 12px 24px; font-size: 13px; font-weight: bold;
        }
        QPushButton:hover { background-color: #f58025; }
    )");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Información básica
    QGroupBox *infoGroup = new QGroupBox("Información del Repuesto");
    QFormLayout *infoLayout = new QFormLayout(infoGroup);

    codigoEdit = new QLineEdit();
    codigoEdit->setPlaceholderText("Ej: REP-001");
    infoLayout->addRow("Código:", codigoEdit);

    nombreEdit = new QLineEdit();
    nombreEdit->setPlaceholderText("Nombre del repuesto");
    infoLayout->addRow("Nombre:", nombreEdit);

    descripcionEdit = new QTextEdit();
    descripcionEdit->setMaximumHeight(60);
    descripcionEdit->setPlaceholderText("Descripción opcional...");
    infoLayout->addRow("Descripción:", descripcionEdit);

    categoriaCombo = new QComboBox();
    categoriaCombo->addItems({"Motor", "Frenos", "Suspensión", "Transmisión", 
                              "Eléctrico", "Carrocería", "Filtros", "Aceites", "Otros"});
    infoLayout->addRow("Categoría:", categoriaCombo);

    mainLayout->addWidget(infoGroup);

    // Precios
    QGroupBox *preciosGroup = new QGroupBox("Precios");
    QFormLayout *preciosLayout = new QFormLayout(preciosGroup);

    precioCompraSpin = new QDoubleSpinBox();
    precioCompraSpin->setPrefix("$ ");
    precioCompraSpin->setMaximum(99999999);
    precioCompraSpin->setDecimals(0);
    connect(precioCompraSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &RepuestoDialog::calcularMargen);
    preciosLayout->addRow("Precio Compra:", precioCompraSpin);

    precioVentaSpin = new QDoubleSpinBox();
    precioVentaSpin->setPrefix("$ ");
    precioVentaSpin->setMaximum(99999999);
    precioVentaSpin->setDecimals(0);
    connect(precioVentaSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &RepuestoDialog::calcularMargen);
    preciosLayout->addRow("Precio Venta:", precioVentaSpin);

    mainLayout->addWidget(preciosGroup);

    // Stock
    QGroupBox *stockGroup = new QGroupBox("Inventario");
    QFormLayout *stockLayout = new QFormLayout(stockGroup);

    stockActualSpin = new QSpinBox();
    stockActualSpin->setMaximum(99999);
    stockLayout->addRow("Stock Actual:", stockActualSpin);

    stockMinimoSpin = new QSpinBox();
    stockMinimoSpin->setMaximum(9999);
    stockMinimoSpin->setValue(5);
    stockLayout->addRow("Stock Mínimo:", stockMinimoSpin);

    mainLayout->addWidget(stockGroup);

    // Botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *cancelButton = new QPushButton("Cancelar");
    QPushButton *acceptButton = new QPushButton(modoEdicion ? "Guardar" : "Crear");
    acceptButton->setDefault(true);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(acceptButton, &QPushButton::clicked, this, &RepuestoDialog::aceptar);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(acceptButton);
    mainLayout->addLayout(buttonLayout);
}

void RepuestoDialog::cargarDatos() {
    codigoEdit->setText(repuesto.getCodigo());
    nombreEdit->setText(repuesto.getNombre());
    descripcionEdit->setPlainText(repuesto.getDescripcion());
    
    int index = categoriaCombo->findText(repuesto.getCategoria());
    if (index >= 0) categoriaCombo->setCurrentIndex(index);
    
    precioCompraSpin->setValue(repuesto.getPrecioCompra());
    precioVentaSpin->setValue(repuesto.getPrecioVenta());
    stockActualSpin->setValue(repuesto.getStockActual());
    stockMinimoSpin->setValue(repuesto.getStockMinimo());
}

Repuesto RepuestoDialog::getRepuesto() const {
    return repuesto;
}

void RepuestoDialog::aceptar() {
    if (codigoEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe ingresar un código para el repuesto.");
        codigoEdit->setFocus();
        return;
    }
    if (nombreEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe ingresar un nombre para el repuesto.");
        nombreEdit->setFocus();
        return;
    }

    repuesto.setCodigo(codigoEdit->text().trimmed());
    repuesto.setNombre(nombreEdit->text().trimmed());
    repuesto.setDescripcion(descripcionEdit->toPlainText().trimmed());
    repuesto.setCategoria(categoriaCombo->currentText());
    repuesto.setPrecioCompra(precioCompraSpin->value());
    repuesto.setPrecioVenta(precioVentaSpin->value());
    repuesto.setStockActual(stockActualSpin->value());
    repuesto.setStockMinimo(stockMinimoSpin->value());

    accept();
}

void RepuestoDialog::calcularMargen() {
    // El margen se calcula automáticamente en el modelo
}

