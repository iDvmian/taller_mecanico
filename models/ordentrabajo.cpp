#include "ordentrabajo.h"

OrdenTrabajo::OrdenTrabajo()
    : id(0), clienteId(0), vehiculoId(0), estado(PENDIENTE),
      costoManoObra(0), costoRepuestos(0), descuento(0), mecanicoAsignado(0) {
    fechaIngreso = QDateTime::currentDateTime();
}

OrdenTrabajo::OrdenTrabajo(const QString &numero, int clienteId, int vehiculoId,
                           const QString &descripcion)
    : id(0), numero(numero), clienteId(clienteId), vehiculoId(vehiculoId),
      descripcionProblema(descripcion), estado(PENDIENTE),
      costoManoObra(0), costoRepuestos(0), descuento(0), mecanicoAsignado(0) {
    fechaIngreso = QDateTime::currentDateTime();
}

// Getters
int OrdenTrabajo::getId() const { return id; }
QString OrdenTrabajo::getNumero() const { return numero; }
int OrdenTrabajo::getClienteId() const { return clienteId; }
int OrdenTrabajo::getVehiculoId() const { return vehiculoId; }
QString OrdenTrabajo::getDescripcionProblema() const { return descripcionProblema; }
QString OrdenTrabajo::getDiagnostico() const { return diagnostico; }
QString OrdenTrabajo::getTrabajoRealizado() const { return trabajoRealizado; }
OrdenTrabajo::Estado OrdenTrabajo::getEstado() const { return estado; }

QString OrdenTrabajo::getEstadoTexto() const {
    return estadoToString(estado);
}

QDateTime OrdenTrabajo::getFechaIngreso() const { return fechaIngreso; }
QDateTime OrdenTrabajo::getFechaEstimadaEntrega() const { return fechaEstimadaEntrega; }
QDateTime OrdenTrabajo::getFechaEntrega() const { return fechaEntrega; }
double OrdenTrabajo::getCostoManoObra() const { return costoManoObra; }
double OrdenTrabajo::getCostoRepuestos() const { return costoRepuestos; }
double OrdenTrabajo::getDescuento() const { return descuento; }

double OrdenTrabajo::getTotal() const {
    double subtotal = costoManoObra + costoRepuestos;
    return subtotal - (subtotal * descuento / 100);
}

QString OrdenTrabajo::getObservaciones() const { return observaciones; }
int OrdenTrabajo::getMecanicoAsignado() const { return mecanicoAsignado; }
QVector<RepuestoUsado> OrdenTrabajo::getRepuestosUsados() const { return repuestosUsados; }

// Setters
void OrdenTrabajo::setId(int id) { this->id = id; }
void OrdenTrabajo::setNumero(const QString &numero) { this->numero = numero; }
void OrdenTrabajo::setClienteId(int clienteId) { this->clienteId = clienteId; }
void OrdenTrabajo::setVehiculoId(int vehiculoId) { this->vehiculoId = vehiculoId; }
void OrdenTrabajo::setDescripcionProblema(const QString &descripcion) { this->descripcionProblema = descripcion; }
void OrdenTrabajo::setDiagnostico(const QString &diagnostico) { this->diagnostico = diagnostico; }
void OrdenTrabajo::setTrabajoRealizado(const QString &trabajo) { this->trabajoRealizado = trabajo; }
void OrdenTrabajo::setEstado(Estado estado) { this->estado = estado; }

void OrdenTrabajo::setEstadoFromInt(int estado) {
    this->estado = static_cast<Estado>(estado);
}

void OrdenTrabajo::setFechaIngreso(const QDateTime &fecha) { this->fechaIngreso = fecha; }
void OrdenTrabajo::setFechaEstimadaEntrega(const QDateTime &fecha) { this->fechaEstimadaEntrega = fecha; }
void OrdenTrabajo::setFechaEntrega(const QDateTime &fecha) { this->fechaEntrega = fecha; }
void OrdenTrabajo::setCostoManoObra(double costo) { this->costoManoObra = costo; }
void OrdenTrabajo::setDescuento(double descuento) { this->descuento = descuento; }
void OrdenTrabajo::setObservaciones(const QString &obs) { this->observaciones = obs; }
void OrdenTrabajo::setMecanicoAsignado(int mecanico) { this->mecanicoAsignado = mecanico; }

// Gestión de repuestos
void OrdenTrabajo::agregarRepuesto(const RepuestoUsado &repuesto) {
    repuestosUsados.append(repuesto);
    recalcularCostoRepuestos();
}

void OrdenTrabajo::quitarRepuesto(int repuestoId) {
    for (int i = 0; i < repuestosUsados.size(); ++i) {
        if (repuestosUsados[i].repuestoId == repuestoId) {
            repuestosUsados.removeAt(i);
            break;
        }
    }
    recalcularCostoRepuestos();
}

void OrdenTrabajo::setRepuestosUsados(const QVector<RepuestoUsado> &repuestos) {
    repuestosUsados = repuestos;
    recalcularCostoRepuestos();
}

void OrdenTrabajo::recalcularCostoRepuestos() {
    costoRepuestos = 0;
    for (const auto &rep : repuestosUsados) {
        costoRepuestos += rep.subtotal;
    }
}

// Cambios de estado
bool OrdenTrabajo::iniciarTrabajo() {
    if (estado == PENDIENTE) {
        estado = EN_PROCESO;
        return true;
    }
    return false;
}

bool OrdenTrabajo::marcarEsperandoRepuestos() {
    if (estado == EN_PROCESO) {
        estado = ESPERANDO_REPUESTOS;
        return true;
    }
    return false;
}

bool OrdenTrabajo::completarTrabajo() {
    if (estado == EN_PROCESO || estado == ESPERANDO_REPUESTOS) {
        estado = COMPLETADA;
        return true;
    }
    return false;
}

bool OrdenTrabajo::entregarVehiculo() {
    if (estado == COMPLETADA) {
        estado = ENTREGADA;
        fechaEntrega = QDateTime::currentDateTime();
        return true;
    }
    return false;
}

bool OrdenTrabajo::cancelar() {
    if (estado != ENTREGADA) {
        estado = CANCELADA;
        return true;
    }
    return false;
}

// Utilidades
int OrdenTrabajo::getDiasEnTaller() const {
    QDateTime fin = (estado == ENTREGADA) ? fechaEntrega : QDateTime::currentDateTime();
    return fechaIngreso.daysTo(fin);
}

bool OrdenTrabajo::estaAtrasada() const {
    if (estado == ENTREGADA || estado == CANCELADA) return false;
    if (!fechaEstimadaEntrega.isValid()) return false;
    return QDateTime::currentDateTime() > fechaEstimadaEntrega;
}

QString OrdenTrabajo::estadoToString(Estado estado) {
    switch (estado) {
        case PENDIENTE: return "Pendiente";
        case EN_PROCESO: return "En Proceso";
        case ESPERANDO_REPUESTOS: return "Esperando Repuestos";
        case COMPLETADA: return "Completada";
        case ENTREGADA: return "Entregada";
        case CANCELADA: return "Cancelada";
        default: return "Desconocido";
    }
}

// Sobrecarga de operadores
bool OrdenTrabajo::operator==(const OrdenTrabajo &otra) const {
    return numero == otra.numero;
}

bool OrdenTrabajo::operator<(const OrdenTrabajo &otra) const {
    return fechaIngreso < otra.fechaIngreso;
}

QTextStream &operator<<(QTextStream &out, const OrdenTrabajo &ot) {
    out << ot.numero << " - " << ot.getEstadoTexto() << " - Total: $" << ot.getTotal();
    return out;
}




