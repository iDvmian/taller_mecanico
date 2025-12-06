#include "vehiculo.h"

Vehiculo::Vehiculo() : id(0), clienteId(0) {}

Vehiculo::Vehiculo(const QString &patente, const QString &modelo, const QString &anio,
                   const QString &nMotor, int cc)
    : id(0), patente(patente), modelo(modelo), anio(anio),
      motor(nMotor, cc), clienteId(0) {}

int Vehiculo::getId() const { return id; }
QString Vehiculo::getPatente() const { return patente; }
QString Vehiculo::getModelo() const { return modelo; }
QString Vehiculo::getAnio() const { return anio; }
Motor Vehiculo::getMotor() const { return motor; }
int Vehiculo::getClienteId() const { return clienteId; }

void Vehiculo::setId(int id) { this->id = id; }
void Vehiculo::setPatente(const QString &patente) { this->patente = patente; }
void Vehiculo::setModelo(const QString &modelo) { this->modelo = modelo; }
void Vehiculo::setAnio(const QString &anio) { this->anio = anio; }
void Vehiculo::setMotor(const Motor &motor) { this->motor = motor; }
void Vehiculo::setClienteId(int clienteId) { this->clienteId = clienteId; }

QString Vehiculo::getInfo() const {
    return QString("[%1] %2 - %3 - %4")
        .arg(patente)
        .arg(modelo)
        .arg(anio)
        .arg(motor.getDetalles());
}

// ==========================================
// SOBRECARGA DE OPERADORES
// ==========================================

// Operador == : Compara dos vehículos por su patente
bool Vehiculo::operator==(const Vehiculo &otro) const {
    return this->patente == otro.patente;
}

// Operador != : Verifica si dos vehículos son diferentes
bool Vehiculo::operator!=(const Vehiculo &otro) const {
    return !(*this == otro);
}

// Operador < : Compara por año (útil para ordenar)
bool Vehiculo::operator<(const Vehiculo &otro) const {
    return this->anio < otro.anio;
}

// Operador << : Para imprimir información del vehículo
QTextStream &operator<<(QTextStream &out, const Vehiculo &v) {
    out << "[" << v.patente << "] " << v.modelo << " - " << v.anio 
        << " - " << v.motor.getDetalles();
    return out;
}
