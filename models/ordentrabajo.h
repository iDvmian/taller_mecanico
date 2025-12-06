#ifndef ORDENTRABAJO_H
#define ORDENTRABAJO_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QTextStream>

// ==========================================
// Estructura para repuestos usados en OT
// ==========================================
struct RepuestoUsado {
    int repuestoId;
    QString nombre;
    int cantidad;
    double precioUnitario;
    double subtotal;
};

// ==========================================
// CLASE ORDEN DE TRABAJO (OT)
// ==========================================
class OrdenTrabajo {
public:
    // Estados posibles de la OT
    enum Estado {
        PENDIENTE,
        EN_PROCESO,
        ESPERANDO_REPUESTOS,
        COMPLETADA,
        ENTREGADA,
        CANCELADA
    };

private:
    int id;
    QString numero;           // Ej: OT-2025-001
    int clienteId;
    int vehiculoId;
    QString descripcionProblema;
    QString diagnostico;
    QString trabajoRealizado;
    Estado estado;
    QDateTime fechaIngreso;
    QDateTime fechaEstimadaEntrega;
    QDateTime fechaEntrega;
    double costoManoObra;
    double costoRepuestos;
    double descuento;
    QString observaciones;
    int mecanicoAsignado;     // ID del mecánico (futuro)
    
    // COMPOSICIÓN: Lista de repuestos usados
    QVector<RepuestoUsado> repuestosUsados;

public:
    OrdenTrabajo();
    OrdenTrabajo(const QString &numero, int clienteId, int vehiculoId,
                 const QString &descripcion);

    // Getters
    int getId() const;
    QString getNumero() const;
    int getClienteId() const;
    int getVehiculoId() const;
    QString getDescripcionProblema() const;
    QString getDiagnostico() const;
    QString getTrabajoRealizado() const;
    Estado getEstado() const;
    QString getEstadoTexto() const;
    QDateTime getFechaIngreso() const;
    QDateTime getFechaEstimadaEntrega() const;
    QDateTime getFechaEntrega() const;
    double getCostoManoObra() const;
    double getCostoRepuestos() const;
    double getDescuento() const;
    double getTotal() const;
    QString getObservaciones() const;
    int getMecanicoAsignado() const;
    QVector<RepuestoUsado> getRepuestosUsados() const;

    // Setters
    void setId(int id);
    void setNumero(const QString &numero);
    void setClienteId(int clienteId);
    void setVehiculoId(int vehiculoId);
    void setDescripcionProblema(const QString &descripcion);
    void setDiagnostico(const QString &diagnostico);
    void setTrabajoRealizado(const QString &trabajo);
    void setEstado(Estado estado);
    void setEstadoFromInt(int estado);
    void setFechaIngreso(const QDateTime &fecha);
    void setFechaEstimadaEntrega(const QDateTime &fecha);
    void setFechaEntrega(const QDateTime &fecha);
    void setCostoManoObra(double costo);
    void setDescuento(double descuento);
    void setObservaciones(const QString &obs);
    void setMecanicoAsignado(int mecanico);

    // Gestión de repuestos
    void agregarRepuesto(const RepuestoUsado &repuesto);
    void quitarRepuesto(int repuestoId);
    void recalcularCostoRepuestos();

    // Cambios de estado
    bool iniciarTrabajo();
    bool marcarEsperandoRepuestos();
    bool completarTrabajo();
    bool entregarVehiculo();
    bool cancelar();

    // Utilidades
    int getDiasEnTaller() const;
    bool estaAtrasada() const;
    static QString estadoToString(Estado estado);

    // Sobrecarga de operadores
    bool operator==(const OrdenTrabajo &otra) const;
    bool operator<(const OrdenTrabajo &otra) const;
    friend QTextStream &operator<<(QTextStream &out, const OrdenTrabajo &ot);
};

#endif // ORDENTRABAJO_H



