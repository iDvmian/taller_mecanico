#include "citadialog.h"
#include "../database/databasemanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QMessageBox>

CitaDialog::CitaDialog(QWidget *parent)
    : QDialog(parent), modoEdicion(false) {
    setupUI();
    setWindowTitle("Nueva Cita");
    fechaHoraEdit->setDateTime(QDateTime::currentDateTime().addSecs(3600));
}

CitaDialog::CitaDialog(const CitaAgenda &cita, QWidget *parent)
    : QDialog(parent), cita(cita), modoEdicion(true) {
    setupUI();
    setWindowTitle("Editar Cita");
    cargarDatos();
}

CitaDialog::CitaDialog(const QDateTime &fechaHora, QWidget *parent)
    : QDialog(parent), modoEdicion(false) {
    setupUI();
    setWindowTitle("Nueva Cita");
    fechaHoraEdit->setDateTime(fechaHora);
}

void CitaDialog::setupUI() {
    setMinimumWidth(500);
    setStyleSheet(R"(
        QDialog { background-color: #f5f5f5; }
        QLabel { color: #333333; font-size: 13px; font-weight: bold; }
        QGroupBox { 
            background-color: #ffffff; border: 1px solid #d0d0d0; border-radius: 6px; 
            margin-top: 16px; padding: 16px 12px 12px 12px; font-weight: bold; color: #ea6f15;
        }
        QGroupBox::title { subcontrol-origin: margin; left: 16px; padding: 0 8px; background-color: #ffffff; }
        QLineEdit, QTextEdit, QSpinBox, QComboBox, QDateTimeEdit {
            background-color: #ffffff; border: 1px solid #c0c0c0; border-radius: 4px;
            padding: 5px 10px; color: #333333; font-size: 13px; min-height: 18px;
        }
        QLineEdit:focus, QTextEdit:focus, QComboBox:focus, QDateTimeEdit:focus, QSpinBox:focus {
            border: 2px solid #ea6f15; background-color: #fffaf5;
        }
        QComboBox::drop-down { border: none; width: 30px; }
        QComboBox QAbstractItemView { background-color: #ffffff; color: #333333; selection-background-color: #ea6f15; selection-color: #ffffff; }
        QDateTimeEdit::drop-down { border: none; width: 30px; }
        QPushButton {
            background-color: #ea6f15; color: #ffffff; border: none; border-radius: 6px; 
            padding: 12px 24px; font-size: 13px; font-weight: bold;
        }
        QPushButton:hover { background-color: #f58025; }
    )");
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Información de la cita
    QGroupBox *infoGroup = new QGroupBox("Información de la Cita");
    QFormLayout *infoLayout = new QFormLayout(infoGroup);

    tituloEdit = new QLineEdit();
    tituloEdit->setPlaceholderText("Ej: Cambio de aceite, Revisión general...");
    infoLayout->addRow("Título:", tituloEdit);

    clienteCombo = new QComboBox();
    connect(clienteCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CitaDialog::clienteSeleccionado);
    infoLayout->addRow("Cliente:", clienteCombo);

    vehiculoCombo = new QComboBox();
    infoLayout->addRow("Vehículo:", vehiculoCombo);

    tipoCombo = new QComboBox();
    tipoCombo->addItems({"Revisión", "Mantención", "Reparación", 
                         "Diagnóstico", "Entrega", "Otro"});
    infoLayout->addRow("Tipo:", tipoCombo);

    // Fecha y hora (dentro del mismo grupo de información)
    fechaHoraEdit = new QDateTimeEdit();
    fechaHoraEdit->setCalendarPopup(true);
    fechaHoraEdit->setDisplayFormat("dd/MM/yyyy hh:mm");
    infoLayout->addRow("Fecha y Hora:", fechaHoraEdit);

    duracionSpin = new QSpinBox();
    duracionSpin->setRange(15, 480);
    duracionSpin->setValue(60);
    duracionSpin->setSuffix(" min");
    duracionSpin->setSingleStep(15);
    infoLayout->addRow("Duración:", duracionSpin);

    estadoCombo = new QComboBox();
    estadoCombo->addItems({"Programada", "Confirmada", "En Curso", 
                           "Completada", "No Asistió", "Cancelada", "Reprogramada"});
    infoLayout->addRow("Estado:", estadoCombo);

    mainLayout->addWidget(infoGroup);

    // Descripción
    QGroupBox *descGroup = new QGroupBox("Descripción");
    QVBoxLayout *descLayout = new QVBoxLayout(descGroup);
    descripcionEdit = new QTextEdit();
    descripcionEdit->setMaximumHeight(60);
    descripcionEdit->setPlaceholderText("Descripción del trabajo a realizar...");
    descLayout->addWidget(descripcionEdit);
    mainLayout->addWidget(descGroup);

    // Notas
    QGroupBox *notasGroup = new QGroupBox("Notas");
    QVBoxLayout *notasLayout = new QVBoxLayout(notasGroup);
    notasEdit = new QTextEdit();
    notasEdit->setMaximumHeight(50);
    notasEdit->setPlaceholderText("Notas adicionales...");
    notasLayout->addWidget(notasEdit);
    mainLayout->addWidget(notasGroup);

    // Botones
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *cancelButton = new QPushButton("Cancelar");
    QPushButton *acceptButton = new QPushButton(modoEdicion ? "Guardar Cambios" : "Programar Cita");
    acceptButton->setDefault(true);

    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(acceptButton, &QPushButton::clicked, this, &CitaDialog::aceptar);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    buttonLayout->addWidget(acceptButton);
    mainLayout->addLayout(buttonLayout);

    cargarClientes();
}

void CitaDialog::cargarClientes() {
    DatabaseManager *db = DatabaseManager::getInstance();
    clientes = db->obtenerTodosClientes();

    clienteCombo->clear();
    clienteCombo->addItem("-- Seleccione Cliente --", 0);
    for (const Cliente &c : clientes) {
        clienteCombo->addItem(c.getNombre() + " " + c.getApellido(), c.getId());
    }
}

void CitaDialog::clienteSeleccionado(int index) {
    vehiculoCombo->clear();
    if (index <= 0) return;

    int clienteId = clienteCombo->currentData().toInt();
    cargarVehiculos(clienteId);
}

void CitaDialog::cargarVehiculos(int clienteId) {
    DatabaseManager *db = DatabaseManager::getInstance();
    auto vehiculos = db->obtenerVehiculosCliente(clienteId);

    vehiculoCombo->addItem("-- Seleccione Vehículo --", 0);
    for (const auto &v : vehiculos) {
        vehiculoCombo->addItem(v->getPatente() + " - " + v->getModelo(), v->getId());
    }
}

void CitaDialog::cargarDatos() {
    tituloEdit->setText(cita.getTitulo());
    
    for (int i = 0; i < clienteCombo->count(); i++) {
        if (clienteCombo->itemData(i).toInt() == cita.getClienteId()) {
            clienteCombo->setCurrentIndex(i);
            break;
        }
    }
    
    cargarVehiculos(cita.getClienteId());
    for (int i = 0; i < vehiculoCombo->count(); i++) {
        if (vehiculoCombo->itemData(i).toInt() == cita.getVehiculoId()) {
            vehiculoCombo->setCurrentIndex(i);
            break;
        }
    }

    tipoCombo->setCurrentIndex(static_cast<int>(cita.getTipo()));
    estadoCombo->setCurrentIndex(static_cast<int>(cita.getEstado()));
    fechaHoraEdit->setDateTime(cita.getFechaHoraInicio());
    duracionSpin->setValue(cita.getDuracionEstimadaMin());
    descripcionEdit->setPlainText(cita.getDescripcion());
    notasEdit->setPlainText(cita.getNotas());
}

CitaAgenda CitaDialog::getCita() const {
    return cita;
}

void CitaDialog::aceptar() {
    if (tituloEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe ingresar un título para la cita.");
        tituloEdit->setFocus();
        return;
    }
    if (clienteCombo->currentData().toInt() == 0) {
        QMessageBox::warning(this, "Error", "Debe seleccionar un cliente.");
        return;
    }

    cita.setTitulo(tituloEdit->text().trimmed());
    cita.setClienteId(clienteCombo->currentData().toInt());
    cita.setVehiculoId(vehiculoCombo->currentData().toInt());
    cita.setTipoFromInt(tipoCombo->currentIndex());
    cita.setEstadoFromInt(estadoCombo->currentIndex());
    cita.setFechaHoraInicio(fechaHoraEdit->dateTime());
    cita.setDuracionEstimadaMin(duracionSpin->value());
    cita.setDescripcion(descripcionEdit->toPlainText().trimmed());
    cita.setNotas(notasEdit->toPlainText().trimmed());

    accept();
}

