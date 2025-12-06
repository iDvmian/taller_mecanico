#include "historialservicio.h"

HistorialServicio::HistorialServicio()
    : id(0), vehiculoId(0), clienteId(0), ordenTrabajoId(0),
      tipoServicio(OTRO), kilometraje(0), costoTotal(0), proximoServicioKm(0) {
    fecha = QDateTime::currentDateTime();
}

HistorialServicio::HistorialServicio(int vehiculoId, int clienteId, TipoServicio tipo,
                                     const QString &descripcion, int kilometraje)
    : id(0), vehiculoId(vehiculoId), clienteId(clienteId), ordenTrabajoId(0),
      tipoServicio(tipo), descripcion(descripcion), kilometraje(kilometraje),
      costoTotal(0), proximoServicioKm(0) {
    fecha = QDateTime::currentDateTime();
}

// Getters
int HistorialServicio::getId() const { return id; }
int HistorialServicio::getVehiculoId() const { return vehiculoId; }
int HistorialServicio::getClienteId() const { return clienteId; }
int HistorialServicio::getOrdenTrabajoId() const { return ordenTrabajoId; }
HistorialServicio::TipoServicio HistorialServicio::getTipoServicio() const { return tipoServicio; }
QString HistorialServicio::getTipoServicioTexto() const { return tipoServicioToString(tipoServicio); }
QString HistorialServicio::getDescripcion() const { return descripcion; }
QString HistorialServicio::getTrabajoRealizado() const { return trabajoRealizado; }
int HistorialServicio::getKilometraje() const { return kilometraje; }
QDateTime HistorialServicio::getFecha() const { return fecha; }
double HistorialServicio::getCostoTotal() const { return costoTotal; }
QString HistorialServicio::getRepuestosUtilizados() const { return repuestosUtilizados; }
QString HistorialServicio::getObservaciones() const { return observaciones; }
int HistorialServicio::getProximoServicioKm() const { return proximoServicioKm; }
QDateTime HistorialServicio::getProximoServicioFecha() const { return proximoServicioFecha; }
QString HistorialServicio::getTecnicoResponsable() const { return tecnicoResponsable; }

// Setters
void HistorialServicio::setId(int id) { this->id = id; }
void HistorialServicio::setVehiculoId(int vehiculoId) { this->vehiculoId = vehiculoId; }
void HistorialServicio::setClienteId(int clienteId) { this->clienteId = clienteId; }
void HistorialServicio::setOrdenTrabajoId(int otId) { this->ordenTrabajoId = otId; }
void HistorialServicio::setTipoServicio(TipoServicio tipo) { this->tipoServicio = tipo; }

void HistorialServicio::setTipoServicioFromInt(int tipo) {
    this->tipoServicio = static_cast<TipoServicio>(tipo);
}

void HistorialServicio::setDescripcion(const QString &descripcion) { this->descripcion = descripcion; }
void HistorialServicio::setTrabajoRealizado(const QString &trabajo) { this->trabajoRealizado = trabajo; }
void HistorialServicio::setKilometraje(int km) { this->kilometraje = km; }
void HistorialServicio::setFecha(const QDateTime &fecha) { this->fecha = fecha; }
void HistorialServicio::setCostoTotal(double costo) { this->costoTotal = costo; }
void HistorialServicio::setRepuestosUtilizados(const QString &repuestos) { this->repuestosUtilizados = repuestos; }
void HistorialServicio::setObservaciones(const QString &obs) { this->observaciones = obs; }
void HistorialServicio::setProximoServicioKm(int km) { this->proximoServicioKm = km; }
void HistorialServicio::setProximoServicioFecha(const QDateTime &fecha) { this->proximoServicioFecha = fecha; }
void HistorialServicio::setTecnicoResponsable(const QString &tecnico) { this->tecnicoResponsable = tecnico; }

// Utilidades
bool HistorialServicio::requiereProximoServicio() const {
    return proximoServicioKm > 0 || proximoServicioFecha.isValid();
}

int HistorialServicio::kmParaProximoServicio(int kmActual) const {
    if (proximoServicioKm <= 0) return -1;
    return proximoServicioKm - kmActual;
}

int HistorialServicio::diasParaProximoServicio() const {
    if (!proximoServicioFecha.isValid()) return -1;
    return QDateTime::currentDateTime().daysTo(proximoServicioFecha);
}

QString HistorialServicio::tipoServicioToString(TipoServicio tipo) {
    switch (tipo) {
        case MANTENCION_PREVENTIVA: return "Mantención Preventiva";
        case REPARACION: return "Reparación";
        case CAMBIO_ACEITE: return "Cambio de Aceite";
        case CAMBIO_FRENOS: return "Cambio de Frenos";
        case CAMBIO_NEUMATICOS: return "Cambio de Neumáticos";
        case REVISION_GENERAL: return "Revisión General";
        case AFINAMIENTO: return "Afinamiento";
        case DIAGNOSTICO: return "Diagnóstico";
        case ELECTRICIDAD: return "Sistema Eléctrico";
        case AIRE_ACONDICIONADO: return "Aire Acondicionado";
        case SUSPENSION: return "Suspensión";
        case TRANSMISION: return "Transmisión";
        case OTRO: return "Otro";
        default: return "Desconocido";
    }
}

// Sobrecarga de operadores
bool HistorialServicio::operator==(const HistorialServicio &otro) const {
    return id == otro.id;
}

bool HistorialServicio::operator<(const HistorialServicio &otro) const {
    return fecha > otro.fecha;  // Más reciente primero
}

QTextStream &operator<<(QTextStream &out, const HistorialServicio &h) {
    out << h.fecha.toString("dd/MM/yyyy") << " - " << h.getTipoServicioTexto()
        << " - " << h.kilometraje << " km - $" << h.costoTotal;
    return out;
}



