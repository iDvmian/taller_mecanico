#ifndef ORDENTRABAJODIALOG_H
#define ORDENTRABAJODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>

#include "../clases/ordentrabajo.h"
#include "../clases/cliente.h"
#include "../clases/vehiculo.h"
#include "../clases/repuesto.h"

class OrdenTrabajoDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit *numeroEdit;
    QComboBox *clienteCombo;
    QComboBox *vehiculoCombo;
    QComboBox *estadoCombo;
    QTextEdit *descripcionEdit;
    QTextEdit *diagnosticoEdit;
    QTextEdit *trabajoEdit;
    QDateTimeEdit *fechaIngresoEdit;
    QDateTimeEdit *fechaEstimadaEdit;
    QDoubleSpinBox *costoManoObraSpin;
    QDoubleSpinBox *descuentoSpin;
    QTextEdit *observacionesEdit;
    QLabel *totalLabel;
    QLabel *costoRepuestosLabel;
    QTableWidget *repuestosTable;
    
    OrdenTrabajo ordenTrabajo;
    QVector<Cliente> clientes;
    QVector<RepuestoUsado> repuestosAgregados;
    bool modoEdicion;

    void setupUI();
    void cargarClientes();
    void cargarVehiculos(int clienteId);
    void cargarDatos();
    void cargarRepuestosTabla();
    void actualizarTotal();
    double calcularTotalRepuestos() const;

public:
    explicit OrdenTrabajoDialog(QWidget *parent = nullptr);
    OrdenTrabajoDialog(const OrdenTrabajo &ot, QWidget *parent = nullptr);

    OrdenTrabajo getOrdenTrabajo() const;

private slots:
    void clienteSeleccionado(int index);
    void aceptar();
    void agregarRepuesto();
    void quitarRepuesto();
};

#endif // ORDENTRABAJODIALOG_H




