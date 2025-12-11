#ifndef VEHICULODIALOG_H
#define VEHICULODIALOG_H

#include <QDialog>
#include "../clases/auto.h"
#include "../clases/moto.h"
#include "../clases/autohibrido.h"

namespace Ui {
class VehiculoDialog;
}

class VehiculoDialog : public QDialog {
    Q_OBJECT

public:
    enum TipoVehiculo {
        TIPO_AUTO,
        TIPO_MOTO,
        TIPO_HIBRIDO
    };

    explicit VehiculoDialog(QWidget *parent = nullptr, TipoVehiculo tipo = TIPO_AUTO);
    ~VehiculoDialog();

    Auto* getAuto() const;
    Moto* getMoto() const;
    AutoHibrido* getHibrido() const;

private slots:
    void onAceptar();

private:
    Ui::VehiculoDialog *ui;
    TipoVehiculo tipoVehiculo;

    void setupUI();
    bool validarCampos();
};

#endif // VEHICULODIALOG_H







