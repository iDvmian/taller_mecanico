#ifndef FACTURADIALOG_H
#define FACTURADIALOG_H

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

class FacturaDialog : public QDialog {
    Q_OBJECT

public:
    explicit FacturaDialog(QWidget *parent = nullptr);
    explicit FacturaDialog(const Factura &factura, QWidget *parent = nullptr);
    
    Factura getFactura() const;

private slots:
    void onAgregarItem();
    void onQuitarItem();
    void onClienteChanged(int index);
    void onOrdenChanged(int index);
    void recalcular();
    void onAceptar();

private:
    void setupUI();
    void cargarClientes();
    void cargarOrdenes();
    void cargarDatosFactura(const Factura &factura);
    
    // Widgets
    QLineEdit *txtNumero;
    QComboBox *cmbCliente;
    QComboBox *cmbOrden;
    QDateTimeEdit *dteFecha;
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
    Factura facturaActual;
    bool modoEdicion;
};

#endif // FACTURADIALOG_H

