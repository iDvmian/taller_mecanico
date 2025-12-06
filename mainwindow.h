#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QCalendarWidget>
#include <QListWidget>
#include <QLabel>
#include <QMessageBox>
#include <QTextCharFormat>
#include "database/databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Clientes
    void onAgregarCliente();
    void onEditarCliente();
    void onEliminarCliente();
    void onClienteSeleccionado();
    void onVerHistorialCliente();

    // Vehículos
    void onAgregarAuto();
    void onAgregarMoto();
    void onAgregarHibrido();
    void onEliminarVehiculo();
    void onVerHistorialVehiculo();

    // Órdenes de Trabajo
    void onNuevaOrden();
    void onEditarOrden();
    void onCambiarEstadoOrden();
    void actualizarTablaOrdenes();

    // Inventario
    void onNuevoRepuesto();
    void onEditarRepuesto();
    void onEliminarRepuesto();
    void onAjustarStock();
    void actualizarTablaInventario();

    // Agenda
    void onNuevaCita();
    void onEditarCita();
    void onEliminarCita();
    void onFechaSeleccionada(const QDate &date);
    void actualizarAgenda();
    void marcarDiasConCitas();

    // Facturación
    void onNuevaFactura();
    void onNuevoPresupuesto();
    void onRegistrarPago();
    void onVerDetalleFactura();
    void onAnularFactura();
    void onConvertirPresupuestoAFactura();
    void actualizarTablaFacturas();

    // General
    void actualizarTablaClientes();
    void actualizarTablaVehiculos();
    void actualizarDashboard();

private:
    Ui::MainWindow *ui;
    DatabaseManager *db;

    // Widgets adicionales para las nuevas pestañas
    QTableWidget *ordenesTable;
    QTableWidget *inventarioTable;
    QTableWidget *facturasTable;
    QCalendarWidget *calendario;
    QListWidget *citasDelDia;
    
    // Labels del dashboard
    QLabel *lblOrdenesActivas;
    QLabel *lblCitasHoy;
    QLabel *lblStockCritico;

    void setupUI();
    void setupConnections();
    void setupNuevasPestanas();
    void setupDashboard();
    
    int getSelectedClienteId();
    int getSelectedVehiculoId();
    int getSelectedOrdenId();
    int getSelectedRepuestoId();
    int getSelectedCitaId();
};

#endif // MAINWINDOW_H
