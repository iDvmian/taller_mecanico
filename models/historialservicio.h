#ifndef HISTORIALSERVICIO_H
#define HISTORIALSERVICIO_H

#include <QString>
#include <QDateTime>
#include <QTextStream>

// ==========================================
// CLASE HISTORIAL DE SERVICIO
// Registro de todos los trabajos realizados
// ==========================================
class HistorialServicio {
public:
    enum TipoServicio {
        MANTENCION_PREVENTIVA,
        REPARACION,
        CAMBIO_ACEITE,
        CAMBIO_FRENOS,
        CAMBIO_NEUMATICOS,
        REVISION_GENERAL,
        AFINAMIENTO,
        DIAGNOSTICO,
        ELECTRICIDAD,
        AIRE_ACONDICIONADO,
        SUSPENSION,
        TRANSMISION,
        OTRO
    };

private:
    int id;
    int vehiculoId;
    int clienteId;
    int ordenTrabajoId;
    TipoServicio tipoServicio;
    QString descripcion;
    QString trabajoRealizado;
    int kilometraje;
    QDateTime fecha;
    double costoTotal;
    QString repuestosUtilizados;  // Resumen de repuestos
    QString observaciones;
    int proximoServicioKm;        // Kilómetros para próximo servicio
    QDateTime proximoServicioFecha;
    QString tecnicoResponsable;

public:
    HistorialServicio();
    HistorialServicio(int vehiculoId, int clienteId, TipoServicio tipo,
                      const QString &descripcion, int kilometraje);

    // Getters
    int getId() const;
    int getVehiculoId() const;
    int getClienteId() const;
    int getOrdenTrabajoId() const;
    TipoServicio getTipoServicio() const;
    QString getTipoServicioTexto() const;
    QString getDescripcion() const;
    QString getTrabajoRealizado() const;
    int getKilometraje() const;
    QDateTime getFecha() const;
    double getCostoTotal() const;
    QString getRepuestosUtilizados() const;
    QString getObservaciones() const;
    int getProximoServicioKm() const;
    QDateTime getProximoServicioFecha() const;
    QString getTecnicoResponsable() const;

    // Setters
    void setId(int id);
    void setVehiculoId(int vehiculoId);
    void setClienteId(int clienteId);
    void setOrdenTrabajoId(int otId);
    void setTipoServicio(TipoServicio tipo);
    void setTipoServicioFromInt(int tipo);
    void setDescripcion(const QString &descripcion);
    void setTrabajoRealizado(const QString &trabajo);
    void setKilometraje(int km);
    void setFecha(const QDateTime &fecha);
    void setCostoTotal(double costo);
    void setRepuestosUtilizados(const QString &repuestos);
    void setObservaciones(const QString &obs);
    void setProximoServicioKm(int km);
    void setProximoServicioFecha(const QDateTime &fecha);
    void setTecnicoResponsable(const QString &tecnico);

    // Utilidades
    bool requiereProximoServicio() const;
    int kmParaProximoServicio(int kmActual) const;
    int diasParaProximoServicio() const;

    static QString tipoServicioToString(TipoServicio tipo);

    // Sobrecarga de operadores
    bool operator==(const HistorialServicio &otro) const;
    bool operator<(const HistorialServicio &otro) const;  // Ordenar por fecha
    friend QTextStream &operator<<(QTextStream &out, const HistorialServicio &h);
};

#endif // HISTORIALSERVICIO_H




