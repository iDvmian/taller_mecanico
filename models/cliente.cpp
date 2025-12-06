#include "cliente.h"

Cliente::Cliente() : id(0) {}

Cliente::Cliente(const QString &rut, const QString &nombre, const QString &apellido,
                 const QString &telefono, const QString &direccion)
    : id(0), rut(rut), nombre(nombre), apellido(apellido),
      telefono(telefono), direccion(direccion) {}

int Cliente::getId() const { return id; }
QString Cliente::getRut() const { return rut; }
QString Cliente::getNombre() const { return nombre; }
QString Cliente::getApellido() const { return apellido; }
QString Cliente::getTelefono() const { return telefono; }
QString Cliente::getDireccion() const { return direccion; }

QString Cliente::getNombreCompleto() const {
    return QString("%1 %2").arg(nombre).arg(apellido);
}

void Cliente::setId(int id) { this->id = id; }
void Cliente::setRut(const QString &rut) { this->rut = rut; }
void Cliente::setNombre(const QString &nombre) { this->nombre = nombre; }
void Cliente::setApellido(const QString &apellido) { this->apellido = apellido; }
void Cliente::setTelefono(const QString &telefono) { this->telefono = telefono; }
void Cliente::setDireccion(const QString &direccion) { this->direccion = direccion; }

// ==========================================
// SOBRECARGA DE MÉTODOS
// ==========================================

// Validación básica: al menos 8 caracteres
bool Cliente::validarRut(const QString &rut) {
    return rut.length() >= 8;
}

// SOBRECARGA: Validación con longitud mínima personalizada
bool Cliente::validarRut(const QString &rut, int longitudMinima) {
    return rut.length() >= longitudMinima;
}

// Buscar por cualquier campo (nombre, apellido o RUT)
bool Cliente::coincide(const QString &busqueda) const {
    QString busquedaLower = busqueda.toLower();
    return nombre.toLower().contains(busquedaLower) ||
           apellido.toLower().contains(busquedaLower) ||
           rut.toLower().contains(busquedaLower);
}

// SOBRECARGA: Buscar por nombre Y apellido específicos
bool Cliente::coincide(const QString &nombreBuscar, const QString &apellidoBuscar) const {
    return nombre.toLower() == nombreBuscar.toLower() &&
           apellido.toLower() == apellidoBuscar.toLower();
}

// ==========================================
// SOBRECARGA DE OPERADORES
// ==========================================

// Operador == : Compara dos clientes por su RUT
bool Cliente::operator==(const Cliente &otro) const {
    return this->rut == otro.rut;
}

// Operador != : Verifica si dos clientes son diferentes
bool Cliente::operator!=(const Cliente &otro) const {
    return !(*this == otro);
}

// Operador < : Compara por apellido (útil para ordenar alfabéticamente)
bool Cliente::operator<(const Cliente &otro) const {
    if (this->apellido == otro.apellido) {
        return this->nombre < otro.nombre;
    }
    return this->apellido < otro.apellido;
}

// Operador << : Para imprimir información del cliente
QTextStream &operator<<(QTextStream &out, const Cliente &c) {
    out << c.nombre << " " << c.apellido << " (RUT: " << c.rut << ")"
        << " | Tel: " << c.telefono << " | Dir: " << c.direccion;
    return out;
}
