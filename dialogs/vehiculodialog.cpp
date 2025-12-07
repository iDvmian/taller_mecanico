#include "vehiculodialog.h"
#include "ui_vehiculodialog.h"
#include <QMessageBox>

VehiculoDialog::VehiculoDialog(QWidget *parent, TipoVehiculo tipo)
    : QDialog(parent)
    , ui(new Ui::VehiculoDialog)
    , tipoVehiculo(tipo)
{
    ui->setupUi(this);
    setupUI();

    connect(ui->btnAceptar, &QPushButton::clicked, this, &VehiculoDialog::onAceptar);
    connect(ui->btnCancelar, &QPushButton::clicked, this, &QDialog::reject);
}

VehiculoDialog::~VehiculoDialog() {
    delete ui;
}

void VehiculoDialog::setupUI() {
    setFixedSize(450, 450);

    // Configurar campos según tipo de vehículo
    switch (tipoVehiculo) {
        case TIPO_AUTO:
            setWindowTitle("Agregar Auto");
            ui->labelEspecifico->setText("Puertas:");
            ui->spinEspecifico->setMinimum(2);
            ui->spinEspecifico->setMaximum(5);
            ui->spinEspecifico->setValue(4);
            ui->checkCajon->setVisible(false);
            ui->labelBateria->setVisible(false);
            ui->spinBateria->setVisible(false);
            break;

        case TIPO_MOTO:
            setWindowTitle("Agregar Moto");
            ui->labelEspecifico->setVisible(false);
            ui->spinEspecifico->setVisible(false);
            ui->checkCajon->setVisible(true);
            ui->checkCajon->setText("¿Tiene cajón?");
            ui->labelBateria->setVisible(false);
            ui->spinBateria->setVisible(false);
            break;

        case TIPO_HIBRIDO:
            setWindowTitle("Agregar Auto Híbrido");
            ui->labelEspecifico->setText("Puertas:");
            ui->spinEspecifico->setMinimum(2);
            ui->spinEspecifico->setMaximum(5);
            ui->spinEspecifico->setValue(4);
            ui->checkCajon->setVisible(false);
            ui->labelBateria->setVisible(true);
            ui->spinBateria->setVisible(true);
            ui->spinBateria->setMinimum(0);
            ui->spinBateria->setMaximum(100);
            ui->spinBateria->setValue(100);
            ui->spinBateria->setSuffix("%");
            // Ocultar cilindrada para vehículos eléctricos
            ui->labelCC->setVisible(false);
            ui->spinCC->setVisible(false);
            ui->spinCC->setValue(0);
            break;
    }
}

bool VehiculoDialog::validarCampos() {
    if (ui->editPatente->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "La patente es obligatoria.");
        return false;
    }
    if (ui->editModelo->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El modelo es obligatorio.");
        return false;
    }
    if (ui->editAnio->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El año es obligatorio.");
        return false;
    }
    if (ui->editSerieMotor->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "La serie del motor es obligatoria.");
        return false;
    }
    return true;
}

void VehiculoDialog::onAceptar() {
    if (validarCampos()) {
        accept();
    }
}

Auto* VehiculoDialog::getAuto() const {
    return new Auto(
        ui->editPatente->text().trimmed(),
        ui->editModelo->text().trimmed(),
        ui->editAnio->text().trimmed(),
        ui->editSerieMotor->text().trimmed(),
        ui->spinCC->value(),
        ui->spinEspecifico->value()
    );
}

Moto* VehiculoDialog::getMoto() const {
    return new Moto(
        ui->editPatente->text().trimmed(),
        ui->editModelo->text().trimmed(),
        ui->editAnio->text().trimmed(),
        ui->editSerieMotor->text().trimmed(),
        ui->spinCC->value(),
        ui->checkCajon->isChecked()
    );
}

AutoHibrido* VehiculoDialog::getHibrido() const {
    return new AutoHibrido(
        ui->editPatente->text().trimmed(),
        ui->editModelo->text().trimmed(),
        ui->editAnio->text().trimmed(),
        ui->editSerieMotor->text().trimmed(),
        0,  // Los vehículos eléctricos/híbridos no tienen cilindrada
        ui->spinEspecifico->value(),
        ui->spinBateria->value()
    );
}




