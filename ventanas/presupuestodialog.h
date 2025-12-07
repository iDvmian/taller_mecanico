#ifndef PRESUPUESTODIALOG_H
#define PRESUPUESTODIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDateTimeEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "../models/documento.h"
#include "../database/databasemanager.h"

class PresupuestoDialog : public QDialog {
    Q_OBJECT

public:
    explicit PresupuestoDialog(QWidget *parent = nullptr);
    explicit PresupuestoDialog(const Presupuesto &presupuesto, QWidget *parent = nullptr);
    
    Presupuesto getPresupuesto() const;

private slots:
    void onAgregarItem();
    void onQuitarItem();
    void onClienteChanged(int index);
    void onDiasValidezChanged(int dias);
    void recalcular();
    void onAceptar();

private:
    void setupUI();
    void cargarClientes();
    void cargarDatosPresupuesto(const Presupuesto &presupuesto);
    
    // Widgets
    QLineEdit *txtNumero;
    QComboBox *cmbCliente;
    QDateTimeEdit *dteFecha;
    QSpinBox *spnDiasValidez;
    QDateTimeEdit *dteFechaVencimiento;
    
    // Items
    QTableWidget *tablaItems;
    QLineEdit *txtItemDescripcion;
    QSpinBox *spnItemCantidad;
    QDoubleSpinBox *spnItemPrecio;
    QPushButton *btnAgregarItem;
    QPushButton *btnQuitarItem;
    
    // Totales
    QDoubleSpinBox *spnDescuento;
    QDoubleSpinBox *spnImpuesto;
    QLabel *lblSubtotal;
    QLabel *lblTotal;
    
    QTextEdit *txtObservaciones;
    
    DatabaseManager *db;
    Presupuesto presupuestoActual;
    bool modoEdicion;
};

#endif // PRESUPUESTODIALOG_H

