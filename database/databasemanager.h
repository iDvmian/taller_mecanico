#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QVector>
#include <QDate>
#include <memory>
#include <stdexcept>

#include "../models/cliente.h"
#include "../models/vehiculo.h"
#include "../models/auto.h"
#include "../models/moto.h"
#include "../models/autohibrido.h"
#include "../models/repuesto.h"
#include "../models/ordentrabajo.h"
#include "../models/documento.h"
#include "../models/citaagenda.h"
#include "../models/historialservicio.h"

// ==========================================
// EXCEPCIONES PERSONALIZADAS
// ==========================================
class ErrorBaseDatos : public std::runtime_error {
public:
    ErrorBaseDatos(const std::string &msg) : std::runtime_error("Error BD: " + msg) {}
};

class DatoInvalido : public std::invalid_argument {
public:
    DatoInvalido(const std::string &msg) : std::invalid_argument("Dato Inválido: " + msg) {}
};

class VehiculoNoEncontrado : public std::runtime_error {
public:
    VehiculoNoEncontrado() : std::runtime_error("El vehículo solicitado no existe en el sistema.") {}
};

// ==========================================
// CLASE DATABASE MANAGER - Gestión de SQLite
// ==========================================
class DatabaseManager {
private:
    QSqlDatabase db;
    static DatabaseManager* instance;

    QString host;
    int port;
    QString databaseName;
    QString username;
    QString password;

    DatabaseManager();
    void createTables();

public:
    ~DatabaseManager();

    // Singleton pattern
    static DatabaseManager* getInstance();

    // Conexión
    bool connect(const QString &host = "",
                 int port = 0,
                 const QString &dbName = "taller_mecanico.db",
                 const QString &user = "",
                 const QString &pass = "");
    
    void disconnect();
    bool isConnected() const;

    // CRUD Clientes
    bool insertarCliente(Cliente &cliente);
    bool actualizarCliente(const Cliente &cliente);
    bool eliminarCliente(int clienteId);
    Cliente obtenerCliente(int clienteId);
    Cliente obtenerClientePorRut(const QString &rut);
    QVector<Cliente> obtenerTodosClientes();
    bool existeClienteRut(const QString &rut);

    // CRUD Vehículos
    bool insertarVehiculo(Vehiculo *vehiculo, int clienteId);
    bool eliminarVehiculo(int vehiculoId);
    QVector<std::shared_ptr<Vehiculo>> obtenerVehiculosCliente(int clienteId);
    QVector<std::shared_ptr<Vehiculo>> obtenerTodosVehiculos();

    // CRUD Repuestos (Inventario)
    bool insertarRepuesto(Repuesto &repuesto);
    bool actualizarRepuesto(const Repuesto &repuesto);
    bool eliminarRepuesto(int repuestoId);
    Repuesto obtenerRepuesto(int repuestoId);
    QVector<Repuesto> obtenerTodosRepuestos();
    QVector<Repuesto> obtenerRepuestosStockCritico();
    bool actualizarStock(int repuestoId, int cantidad, bool esIngreso);

    // CRUD Órdenes de Trabajo
    bool insertarOrdenTrabajo(OrdenTrabajo &ot);
    bool actualizarOrdenTrabajo(const OrdenTrabajo &ot);
    bool eliminarOrdenTrabajo(int otId);
    OrdenTrabajo obtenerOrdenTrabajo(int otId);
    QVector<OrdenTrabajo> obtenerOrdenesCliente(int clienteId);
    QVector<OrdenTrabajo> obtenerOrdenesVehiculo(int vehiculoId);
    QVector<OrdenTrabajo> obtenerOrdenesPorEstado(int estado);
    QVector<OrdenTrabajo> obtenerTodasOrdenes();
    QString generarNumeroOT();
    bool agregarRepuestoAOrden(int otId, int repuestoId, int cantidad, double precio);

    // CRUD Facturas
    bool insertarFactura(Factura &factura);
    bool actualizarFactura(const Factura &factura);
    Factura obtenerFactura(int facturaId);
    QVector<Factura> obtenerFacturasCliente(int clienteId);
    QVector<Factura> obtenerFacturasPendientes();
    QVector<Factura> obtenerTodasFacturas();
    QString generarNumeroFactura();

    // CRUD Presupuestos
    bool insertarPresupuesto(Presupuesto &presupuesto);
    bool actualizarPresupuesto(const Presupuesto &presupuesto);
    Presupuesto obtenerPresupuesto(int presupuestoId);
    QVector<Presupuesto> obtenerPresupuestosCliente(int clienteId);
    QVector<Presupuesto> obtenerTodosPresupuestos();
    QString generarNumeroPresupuesto();

    // CRUD Citas/Agenda
    bool insertarCita(CitaAgenda &cita);
    bool actualizarCita(const CitaAgenda &cita);
    bool eliminarCita(int citaId);
    CitaAgenda obtenerCita(int citaId);
    QVector<CitaAgenda> obtenerCitasPorFecha(const QDate &fecha);
    QVector<CitaAgenda> obtenerCitasCliente(int clienteId);
    QVector<CitaAgenda> obtenerCitasHoy();
    QVector<CitaAgenda> obtenerCitasSemana();
    QVector<CitaAgenda> obtenerTodasCitas();

    // CRUD Historial de Servicios
    bool insertarHistorial(HistorialServicio &historial);
    QVector<HistorialServicio> obtenerHistorialVehiculo(int vehiculoId);
    QVector<HistorialServicio> obtenerHistorialCliente(int clienteId);
    QVector<HistorialServicio> obtenerTodoHistorial();

    // Utilidades
    QString getLastError() const;
};

#endif // DATABASEMANAGER_H
