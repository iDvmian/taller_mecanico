#ifndef CITADIALOG_H
#define CITADIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QPushButton>

#include "../models/citaagenda.h"
#include "../models/cliente.h"

class CitaDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit *tituloEdit;
    QComboBox *clienteCombo;
    QComboBox *vehiculoCombo;
    QComboBox *tipoCombo;
    QComboBox *estadoCombo;
    QDateTimeEdit *fechaHoraEdit;
    QSpinBox *duracionSpin;
    QTextEdit *descripcionEdit;
    QTextEdit *notasEdit;
    
    CitaAgenda cita;
    QVector<Cliente> clientes;
    bool modoEdicion;

    void setupUI();
    void cargarClientes();
    void cargarVehiculos(int clienteId);
    void cargarDatos();

public:
    explicit CitaDialog(QWidget *parent = nullptr);
    CitaDialog(const CitaAgenda &cita, QWidget *parent = nullptr);
    CitaDialog(const QDateTime &fechaHora, QWidget *parent = nullptr);

    CitaAgenda getCita() const;

private slots:
    void clienteSeleccionado(int index);
    void aceptar();
};

#endif // CITADIALOG_H



