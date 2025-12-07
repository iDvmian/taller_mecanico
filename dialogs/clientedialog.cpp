#include "clientedialog.h"
#include "ui_clientedialog.h"
#include <QMessageBox>

ClienteDialog::ClienteDialog(QWidget *parent, Cliente *cliente)
    : QDialog(parent)
    , ui(new Ui::ClienteDialog)
    , editMode(cliente != nullptr)
{
    ui->setupUi(this);
    setupUI();

    if (editMode && cliente) {
        ui->editRut->setText(cliente->getRut());
        ui->editRut->setEnabled(false); // No permitir cambiar RUT en edición
        ui->editNombre->setText(cliente->getNombre());
        ui->editApellido->setText(cliente->getApellido());
        ui->editTelefono->setText(cliente->getTelefono());
        ui->editDireccion->setText(cliente->getDireccion());
    }

    connect(ui->btnAceptar, &QPushButton::clicked, this, &ClienteDialog::onAceptar);
    connect(ui->btnCancelar, &QPushButton::clicked, this, &QDialog::reject);
}

ClienteDialog::~ClienteDialog() {
    delete ui;
}

void ClienteDialog::setupUI() {
    setWindowTitle(editMode ? "Editar Cliente" : "Agregar Cliente");
    setFixedSize(450, 350);
}

bool ClienteDialog::validarCampos() {
    if (ui->editRut->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El RUT es obligatorio.");
        return false;
    }
    if (ui->editRut->text().trimmed().length() < 8) {
        QMessageBox::warning(this, "Error", "El RUT debe tener al menos 8 caracteres.");
        return false;
    }
    if (ui->editNombre->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El nombre es obligatorio.");
        return false;
    }
    if (ui->editApellido->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Error", "El apellido es obligatorio.");
        return false;
    }
    return true;
}

void ClienteDialog::onAceptar() {
    if (validarCampos()) {
        accept();
    }
}

Cliente ClienteDialog::getCliente() const {
    return Cliente(
        ui->editRut->text().trimmed(),
        ui->editNombre->text().trimmed(),
        ui->editApellido->text().trimmed(),
        ui->editTelefono->text().trimmed(),
        ui->editDireccion->text().trimmed()
    );
}







