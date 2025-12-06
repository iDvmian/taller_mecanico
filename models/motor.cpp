#include "motor.h"

Motor::Motor() : numeroSerie(""), cilindrada(0) {}

Motor::Motor(const QString &numeroSerie, int cilindrada)
    : numeroSerie(numeroSerie), cilindrada(cilindrada) {}

QString Motor::getNumeroSerie() const {
    return numeroSerie;
}

int Motor::getCilindrada() const {
    return cilindrada;
}

QString Motor::getDetalles() const {
    return QString("Motor V%1cc #%2").arg(cilindrada).arg(numeroSerie);
}

void Motor::setNumeroSerie(const QString &numeroSerie) {
    this->numeroSerie = numeroSerie;
}

void Motor::setCilindrada(int cilindrada) {
    this->cilindrada = cilindrada;
}

// ==========================================
// SOBRECARGA DE OPERADORES
// ==========================================

// Operador == : Compara dos motores por número de serie
bool Motor::operator==(const Motor &otro) const {
    return this->numeroSerie == otro.numeroSerie;
}

// Operador != : Verifica si dos motores son diferentes
bool Motor::operator!=(const Motor &otro) const {
    return !(*this == otro);
}

// Operador > : Compara por cilindrada (cuál es más potente)
bool Motor::operator>(const Motor &otro) const {
    return this->cilindrada > otro.cilindrada;
}

// Operador < : Compara por cilindrada
bool Motor::operator<(const Motor &otro) const {
    return this->cilindrada < otro.cilindrada;
}

// Operador << : Para imprimir información del motor
QTextStream &operator<<(QTextStream &out, const Motor &m) {
    out << "Motor V" << m.cilindrada << "cc #" << m.numeroSerie;
    return out;
}
