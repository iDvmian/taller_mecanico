#include "citaagenda.h"

CitaAgenda::CitaAgenda()
    : id(0), clienteId(0), vehiculoId(0), ordenTrabajoId(0),
      tipo(REVISION), estado(PROGRAMADA), duracionEstimadaMin(60),
      recordatorioEnviado(false) {
    colorCalendario = colorPorTipo(tipo);
}

CitaAgenda::CitaAgenda(int clienteId, int vehiculoId, const QString &titulo,
                       TipoCita tipo, const QDateTime &inicio, int duracionMin)
    : id(0), clienteId(clienteId), vehiculoId(vehiculoId), ordenTrabajoId(0),
      titulo(titulo), tipo(tipo), estado(PROGRAMADA),
      fechaHoraInicio(inicio), duracionEstimadaMin(duracionMin),
      recordatorioEnviado(false) {
    fechaHoraFin = inicio.addSecs(duracionMin * 60);
    colorCalendario = colorPorTipo(tipo);
}

// Getters
int CitaAgenda::getId() const { return id; }
int CitaAgenda::getClienteId() const { return clienteId; }
int CitaAgenda::getVehiculoId() const { return vehiculoId; }
int CitaAgenda::getOrdenTrabajoId() const { return ordenTrabajoId; }
QString CitaAgenda::getTitulo() const { return titulo; }
QString CitaAgenda::getDescripcion() const { return descripcion; }
CitaAgenda::TipoCita CitaAgenda::getTipo() const { return tipo; }
QString CitaAgenda::getTipoTexto() const { return tipoToString(tipo); }
CitaAgenda::EstadoCita CitaAgenda::getEstado() const { return estado; }
QString CitaAgenda::getEstadoTexto() const { return estadoToString(estado); }
QDateTime CitaAgenda::getFechaHoraInicio() const { return fechaHoraInicio; }
QDateTime CitaAgenda::getFechaHoraFin() const { return fechaHoraFin; }
int CitaAgenda::getDuracionEstimadaMin() const { return duracionEstimadaMin; }
QString CitaAgenda::getColorCalendario() const { return colorCalendario; }
bool CitaAgenda::getRecordatorioEnviado() const { return recordatorioEnviado; }
QString CitaAgenda::getNotas() const { return notas; }

// Setters
void CitaAgenda::setId(int id) { this->id = id; }
void CitaAgenda::setClienteId(int clienteId) { this->clienteId = clienteId; }
void CitaAgenda::setVehiculoId(int vehiculoId) { this->vehiculoId = vehiculoId; }
void CitaAgenda::setOrdenTrabajoId(int otId) { this->ordenTrabajoId = otId; }
void CitaAgenda::setTitulo(const QString &titulo) { this->titulo = titulo; }
void CitaAgenda::setDescripcion(const QString &descripcion) { this->descripcion = descripcion; }

void CitaAgenda::setTipo(TipoCita tipo) {
    this->tipo = tipo;
    colorCalendario = colorPorTipo(tipo);
}

void CitaAgenda::setTipoFromInt(int tipo) {
    this->tipo = static_cast<TipoCita>(tipo);
    colorCalendario = colorPorTipo(this->tipo);
}

void CitaAgenda::setEstado(EstadoCita estado) { this->estado = estado; }

void CitaAgenda::setEstadoFromInt(int estado) {
    this->estado = static_cast<EstadoCita>(estado);
}

void CitaAgenda::setFechaHoraInicio(const QDateTime &fecha) {
    this->fechaHoraInicio = fecha;
    fechaHoraFin = fecha.addSecs(duracionEstimadaMin * 60);
}

void CitaAgenda::setFechaHoraFin(const QDateTime &fecha) { this->fechaHoraFin = fecha; }

void CitaAgenda::setDuracionEstimadaMin(int minutos) {
    this->duracionEstimadaMin = minutos;
    if (fechaHoraInicio.isValid()) {
        fechaHoraFin = fechaHoraInicio.addSecs(minutos * 60);
    }
}

void CitaAgenda::setColorCalendario(const QString &color) { this->colorCalendario = color; }
void CitaAgenda::setRecordatorioEnviado(bool enviado) { this->recordatorioEnviado = enviado; }
void CitaAgenda::setNotas(const QString &notas) { this->notas = notas; }

// Operaciones
bool CitaAgenda::confirmar() {
    if (estado == PROGRAMADA) {
        estado = CONFIRMADA;
        return true;
    }
    return false;
}

bool CitaAgenda::iniciar() {
    if (estado == PROGRAMADA || estado == CONFIRMADA) {
        estado = EN_CURSO;
        return true;
    }
    return false;
}

bool CitaAgenda::completar() {
    if (estado == EN_CURSO) {
        estado = COMPLETADA;
        return true;
    }
    return false;
}

bool CitaAgenda::marcarNoAsistio() {
    if (estado == PROGRAMADA || estado == CONFIRMADA) {
        estado = NO_ASISTIO;
        return true;
    }
    return false;
}

bool CitaAgenda::cancelar() {
    if (estado != COMPLETADA && estado != CANCELADA) {
        estado = CANCELADA;
        return true;
    }
    return false;
}

bool CitaAgenda::reprogramar(const QDateTime &nuevaFecha) {
    if (estado != COMPLETADA && estado != CANCELADA) {
        fechaHoraInicio = nuevaFecha;
        fechaHoraFin = nuevaFecha.addSecs(duracionEstimadaMin * 60);
        estado = REPROGRAMADA;
        return true;
    }
    return false;
}

// Utilidades
bool CitaAgenda::esHoy() const {
    return fechaHoraInicio.date() == QDate::currentDate();
}

bool CitaAgenda::esFutura() const {
    return fechaHoraInicio > QDateTime::currentDateTime();
}

bool CitaAgenda::estaPasada() const {
    return fechaHoraFin < QDateTime::currentDateTime();
}

bool CitaAgenda::seSuperpone(const CitaAgenda &otra) const {
    // Verifica si hay superposición de horarios
    return !(fechaHoraFin <= otra.fechaHoraInicio || fechaHoraInicio >= otra.fechaHoraFin);
}

int CitaAgenda::minutosHastaInicio() const {
    if (!fechaHoraInicio.isValid()) return -1;
    qint64 secs = QDateTime::currentDateTime().secsTo(fechaHoraInicio);
    return secs / 60;
}

// Colores según tipo
QString CitaAgenda::colorPorTipo(TipoCita tipo) {
    switch (tipo) {
        case REVISION: return "#3498db";      // Azul
        case MANTENCION: return "#2ecc71";    // Verde
        case REPARACION: return "#e74c3c";    // Rojo
        case DIAGNOSTICO: return "#f39c12";   // Naranja
        case ENTREGA: return "#9b59b6";       // Púrpura
        case OTRO: return "#95a5a6";          // Gris
        default: return "#34495e";
    }
}

QString CitaAgenda::tipoToString(TipoCita tipo) {
    switch (tipo) {
        case REVISION: return "Revisión";
        case MANTENCION: return "Mantención";
        case REPARACION: return "Reparación";
        case DIAGNOSTICO: return "Diagnóstico";
        case ENTREGA: return "Entrega";
        case OTRO: return "Otro";
        default: return "Desconocido";
    }
}

QString CitaAgenda::estadoToString(EstadoCita estado) {
    switch (estado) {
        case PROGRAMADA: return "Programada";
        case CONFIRMADA: return "Confirmada";
        case EN_CURSO: return "En Curso";
        case COMPLETADA: return "Completada";
        case NO_ASISTIO: return "No Asistió";
        case CANCELADA: return "Cancelada";
        case REPROGRAMADA: return "Reprogramada";
        default: return "Desconocido";
    }
}

// Sobrecarga de operadores
bool CitaAgenda::operator==(const CitaAgenda &otra) const {
    return id == otra.id;
}

bool CitaAgenda::operator<(const CitaAgenda &otra) const {
    return fechaHoraInicio < otra.fechaHoraInicio;
}

QTextStream &operator<<(QTextStream &out, const CitaAgenda &c) {
    out << c.fechaHoraInicio.toString("dd/MM/yyyy hh:mm") << " - " << c.titulo
        << " [" << c.getEstadoTexto() << "]";
    return out;
}




