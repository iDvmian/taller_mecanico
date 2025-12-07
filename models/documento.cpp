#include "documento.h"

// ==========================================
// IMPLEMENTACIÓN DE DOCUMENTO (Clase Base)
// ==========================================
Documento::Documento()
    : id(0), clienteId(0), ordenTrabajoId(0), subtotal(0), impuesto(19), descuento(0) {
    fecha = QDateTime::currentDateTime();
}

Documento::Documento(const QString &numero, int clienteId)
    : id(0), numero(numero), clienteId(clienteId), ordenTrabajoId(0),
      subtotal(0), impuesto(19), descuento(0) {
    fecha = QDateTime::currentDateTime();
}

// Getters
int Documento::getId() const { return id; }
QString Documento::getNumero() const { return numero; }
int Documento::getClienteId() const { return clienteId; }
int Documento::getOrdenTrabajoId() const { return ordenTrabajoId; }
QDateTime Documento::getFecha() const { return fecha; }
QDateTime Documento::getFechaVencimiento() const { return fechaVencimiento; }
QVector<ItemDocumento> Documento::getItems() const { return items; }
double Documento::getSubtotal() const { return subtotal; }
double Documento::getImpuesto() const { return impuesto; }
double Documento::getDescuento() const { return descuento; }
QString Documento::getObservaciones() const { return observaciones; }

// Setters
void Documento::setId(int id) { this->id = id; }
void Documento::setNumero(const QString &numero) { this->numero = numero; }
void Documento::setClienteId(int clienteId) { this->clienteId = clienteId; }
void Documento::setOrdenTrabajoId(int otId) { this->ordenTrabajoId = otId; }
void Documento::setFecha(const QDateTime &fecha) { this->fecha = fecha; }
void Documento::setFechaVencimiento(const QDateTime &fecha) { this->fechaVencimiento = fecha; }
void Documento::setSubtotal(double subtotal) { this->subtotal = subtotal; }
void Documento::setImpuesto(double impuesto) { this->impuesto = impuesto; }
void Documento::setDescuento(double descuento) { this->descuento = descuento; }
void Documento::setObservaciones(const QString &obs) { this->observaciones = obs; }

// Gestión de items
void Documento::agregarItem(const ItemDocumento &item) {
    items.append(item);
    recalcularSubtotal();
}

void Documento::quitarItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.removeAt(index);
        recalcularSubtotal();
    }
}

void Documento::limpiarItems() {
    items.clear();
    subtotal = 0;
}

void Documento::recalcularSubtotal() {
    subtotal = 0;
    for (const auto &item : items) {
        subtotal += item.subtotal;
    }
}

// Sobrecarga de operadores
bool Documento::operator==(const Documento &otro) const {
    return numero == otro.numero;
}

bool Documento::operator<(const Documento &otro) const {
    return fecha < otro.fecha;
}

QTextStream &operator<<(QTextStream &out, const Documento &d) {
    out << d.getTipo() << " " << d.numero << " - $" << d.getTotal();
    return out;
}

// ==========================================
// IMPLEMENTACIÓN DE FACTURA
// ==========================================
Factura::Factura()
    : Documento(), estadoPago(PENDIENTE), montoPagado(0) {}

Factura::Factura(const QString &numero, int clienteId)
    : Documento(numero, clienteId), estadoPago(PENDIENTE), montoPagado(0) {
    fechaVencimiento = fecha.addDays(30);  // Vence en 30 días
}

// Getters específicos
Factura::EstadoPago Factura::getEstadoPago() const { return estadoPago; }
double Factura::getMontoPagado() const { return montoPagado; }

double Factura::getSaldoPendiente() const {
    return getTotal() - montoPagado;
}

QDateTime Factura::getFechaPago() const { return fechaPago; }
QString Factura::getMetodoPago() const { return metodoPago; }

// Setters específicos
void Factura::setEstadoPago(EstadoPago estado) { this->estadoPago = estado; }

void Factura::setEstadoPagoFromInt(int estado) {
    this->estadoPago = static_cast<EstadoPago>(estado);
}

void Factura::setMontoPagado(double monto) { this->montoPagado = monto; }
void Factura::setFechaPago(const QDateTime &fecha) { this->fechaPago = fecha; }
void Factura::setMetodoPago(const QString &metodo) { this->metodoPago = metodo; }

// Operaciones de pago
bool Factura::registrarPago(double monto, const QString &metodo) {
    if (estadoPago == ANULADA || monto <= 0) return false;
    
    montoPagado += monto;
    metodoPago = metodo;
    fechaPago = QDateTime::currentDateTime();
    
    if (montoPagado >= getTotal()) {
        estadoPago = PAGADA;
        montoPagado = getTotal();  // No sobrepagar
    } else {
        estadoPago = PARCIAL;
    }
    return true;
}

bool Factura::anular() {
    if (estadoPago == PAGADA) return false;
    estadoPago = ANULADA;
    return true;
}

// Sobreescritura de métodos virtuales
QString Factura::getTipo() const {
    return "FACTURA";
}

double Factura::getTotal() const {
    double base = subtotal - (subtotal * descuento / 100);
    return base + (base * impuesto / 100);
}

bool Factura::estaVencido() const {
    if (estadoPago == PAGADA || estadoPago == ANULADA) return false;
    return QDateTime::currentDateTime() > fechaVencimiento;
}

QString Factura::getEstado() const {
    if (estaVencido() && estadoPago != PAGADA && estadoPago != ANULADA) {
        return "Vencida";
    }
    return estadoPagoToString(estadoPago);
}

QString Factura::estadoPagoToString(EstadoPago estado) {
    switch (estado) {
        case PENDIENTE: return "Pendiente";
        case PAGADA: return "Pagada";
        case PARCIAL: return "Pago Parcial";
        case VENCIDA: return "Vencida";
        case ANULADA: return "Anulada";
        default: return "Desconocido";
    }
}

// ==========================================
// IMPLEMENTACIÓN DE PRESUPUESTO
// ==========================================
Presupuesto::Presupuesto()
    : Documento(), estadoPresupuesto(BORRADOR), diasValidez(15), facturaGeneradaId(0) {}

Presupuesto::Presupuesto(const QString &numero, int clienteId, int diasValidez)
    : Documento(numero, clienteId), estadoPresupuesto(BORRADOR),
      diasValidez(diasValidez), facturaGeneradaId(0) {
    fechaVencimiento = fecha.addDays(diasValidez);
}

// Getters específicos
Presupuesto::EstadoPresupuesto Presupuesto::getEstadoPresupuesto() const {
    return estadoPresupuesto;
}

int Presupuesto::getDiasValidez() const { return diasValidez; }
int Presupuesto::getFacturaGeneradaId() const { return facturaGeneradaId; }

int Presupuesto::getDiasRestantes() const {
    if (!fechaVencimiento.isValid()) return 0;
    int dias = QDateTime::currentDateTime().daysTo(fechaVencimiento);
    return dias > 0 ? dias : 0;
}

// Setters específicos
void Presupuesto::setEstadoPresupuesto(EstadoPresupuesto estado) {
    this->estadoPresupuesto = estado;
}

void Presupuesto::setEstadoPresupuestoFromInt(int estado) {
    this->estadoPresupuesto = static_cast<EstadoPresupuesto>(estado);
}

void Presupuesto::setDiasValidez(int dias) {
    this->diasValidez = dias;
    fechaVencimiento = fecha.addDays(dias);
}

void Presupuesto::setFacturaGeneradaId(int facturaId) {
    this->facturaGeneradaId = facturaId;
}

// Operaciones
bool Presupuesto::enviar() {
    if (estadoPresupuesto == BORRADOR) {
        estadoPresupuesto = ENVIADO;
        return true;
    }
    return false;
}

bool Presupuesto::aprobar() {
    if (estadoPresupuesto == ENVIADO) {
        estadoPresupuesto = APROBADO;
        return true;
    }
    return false;
}

bool Presupuesto::rechazar() {
    if (estadoPresupuesto == ENVIADO) {
        estadoPresupuesto = RECHAZADO;
        return true;
    }
    return false;
}

bool Presupuesto::convertirAFactura(int facturaId) {
    if (estadoPresupuesto == APROBADO) {
        estadoPresupuesto = CONVERTIDO;
        facturaGeneradaId = facturaId;
        return true;
    }
    return false;
}

// Sobreescritura de métodos virtuales
QString Presupuesto::getTipo() const {
    return "PRESUPUESTO";
}

double Presupuesto::getTotal() const {
    double base = subtotal - (subtotal * descuento / 100);
    return base + (base * impuesto / 100);
}

bool Presupuesto::estaVencido() const {
    if (estadoPresupuesto == APROBADO || estadoPresupuesto == RECHAZADO ||
        estadoPresupuesto == CONVERTIDO) return false;
    return QDateTime::currentDateTime() > fechaVencimiento;
}

QString Presupuesto::getEstado() const {
    if (estaVencido() && estadoPresupuesto != APROBADO && 
        estadoPresupuesto != RECHAZADO && estadoPresupuesto != CONVERTIDO) {
        return "Vencido";
    }
    return estadoToString(estadoPresupuesto);
}

QString Presupuesto::estadoToString(EstadoPresupuesto estado) {
    switch (estado) {
        case BORRADOR: return "Borrador";
        case ENVIADO: return "Enviado";
        case APROBADO: return "Aprobado";
        case RECHAZADO: return "Rechazado";
        case VENCIDO: return "Vencido";
        case CONVERTIDO: return "Convertido a Factura";
        default: return "Desconocido";
    }
}




