#ifndef CITAAGENDA_H
#define CITAAGENDA_H

#include <QString>
#include <QDateTime>
#include <QTextStream>

// ==========================================
// CLASE CITA AGENDA - Calendario de trabajos
// ==========================================
class CitaAgenda {
public:
    enum TipoCita {
        REVISION,
        MANTENCION,
        REPARACION,
        DIAGNOSTICO,
        ENTREGA,
        OTRO
    };

    enum EstadoCita {
        PROGRAMADA,
        CONFIRMADA,
        EN_CURSO,
        COMPLETADA,
        NO_ASISTIO,
        CANCELADA,
        REPROGRAMADA
    };

private:
    int id;
    int clienteId;
    int vehiculoId;
    int ordenTrabajoId;       // 0 si aún no tiene OT
    QString titulo;
    QString descripcion;
    TipoCita tipo;
    EstadoCita estado;
    QDateTime fechaHoraInicio;
    QDateTime fechaHoraFin;
    int duracionEstimadaMin;
    QString colorCalendario;  // Para mostrar en UI
    bool recordatorioEnviado;
    QString notas;

public:
    CitaAgenda();
    CitaAgenda(int clienteId, int vehiculoId, const QString &titulo,
               TipoCita tipo, const QDateTime &inicio, int duracionMin);

    // Getters
    int getId() const;
    int getClienteId() const;
    int getVehiculoId() const;
    int getOrdenTrabajoId() const;
    QString getTitulo() const;
    QString getDescripcion() const;
    TipoCita getTipo() const;
    QString getTipoTexto() const;
    EstadoCita getEstado() const;
    QString getEstadoTexto() const;
    QDateTime getFechaHoraInicio() const;
    QDateTime getFechaHoraFin() const;
    int getDuracionEstimadaMin() const;
    QString getColorCalendario() const;
    bool getRecordatorioEnviado() const;
    QString getNotas() const;

    // Setters
    void setId(int id);
    void setClienteId(int clienteId);
    void setVehiculoId(int vehiculoId);
    void setOrdenTrabajoId(int otId);
    void setTitulo(const QString &titulo);
    void setDescripcion(const QString &descripcion);
    void setTipo(TipoCita tipo);
    void setTipoFromInt(int tipo);
    void setEstado(EstadoCita estado);
    void setEstadoFromInt(int estado);
    void setFechaHoraInicio(const QDateTime &fecha);
    void setFechaHoraFin(const QDateTime &fecha);
    void setDuracionEstimadaMin(int minutos);
    void setColorCalendario(const QString &color);
    void setRecordatorioEnviado(bool enviado);
    void setNotas(const QString &notas);

    // Operaciones
    bool confirmar();
    bool iniciar();
    bool completar();
    bool marcarNoAsistio();
    bool cancelar();
    bool reprogramar(const QDateTime &nuevaFecha);

    // Utilidades
    bool esHoy() const;
    bool esFutura() const;
    bool estaPasada() const;
    bool seSuperpone(const CitaAgenda &otra) const;
    int minutosHastaInicio() const;

    // Colores según tipo
    static QString colorPorTipo(TipoCita tipo);
    static QString tipoToString(TipoCita tipo);
    static QString estadoToString(EstadoCita estado);

    // Sobrecarga de operadores
    bool operator==(const CitaAgenda &otra) const;
    bool operator<(const CitaAgenda &otra) const;
    friend QTextStream &operator<<(QTextStream &out, const CitaAgenda &c);
};

#endif // CITAAGENDA_H



