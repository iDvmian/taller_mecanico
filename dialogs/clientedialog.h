#ifndef CLIENTEDIALOG_H
#define CLIENTEDIALOG_H

#include <QDialog>
#include "../models/cliente.h"

namespace Ui {
class ClienteDialog;
}

class ClienteDialog : public QDialog {
    Q_OBJECT

public:
    explicit ClienteDialog(QWidget *parent = nullptr, Cliente *cliente = nullptr);
    ~ClienteDialog();

    Cliente getCliente() const;

private slots:
    void onAceptar();

private:
    Ui::ClienteDialog *ui;
    bool editMode;

    void setupUI();
    bool validarCampos();
};

#endif // CLIENTEDIALOG_H






