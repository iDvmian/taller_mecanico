#include "auto.h"

// ==========================================
// SOBRECARGA DE CONSTRUCTORES
// ==========================================

// Constructor por defecto
Auto::Auto() : Vehiculo(), puertas(4) {}

// Constructor completo
Auto::Auto(const QString &patente, const QString &modelo, const QString &anio,
           const QString &nMotor, int cc, int puertas)
    : Vehiculo(patente, modelo, anio, nMotor, cc), puertas(puertas) {}

// SOBRECARGA: Constructor simplificado (motor por defecto)
Auto::Auto(const QString &patente, const QString &modelo, const QString &anio, int puertas)
    : Vehiculo(patente, modelo, anio, "SIN-SERIE", 1600), puertas(puertas) {}

// Getters y Setters
int Auto::getPuertas() const { return puertas; }
void Auto::setPuertas(int puertas) { this->puertas = puertas; }

// ==========================================
// SOBREESCRITURA (Override) - POLIMORFISMO
// ==========================================

QString Auto::getTipo() const {
    return "AUTO";
}

QString Auto::getInfoAdicional() const {
    return QString("Puertas: %1").arg(puertas);
}

// ==========================================
// SOBRECARGA DE MÉTODOS
// ==========================================

// Versión básica - solo info principal
QString Auto::mostrarInfo() const {
    return QString("Auto: %1 %2 (%3) - %4 puertas")
        .arg(modelo)
        .arg(patente)
        .arg(anio)
        .arg(puertas);
}

// SOBRECARGA: Con opción de incluir motor
QString Auto::mostrarInfo(bool incluirMotor) const {
    if (incluirMotor) {
        return QString("Auto: %1 %2 (%3) - %4 puertas | %5")
            .arg(modelo)
            .arg(patente)
            .arg(anio)
            .arg(puertas)
            .arg(motor.getDetalles());
    }
    return mostrarInfo();
}

// SOBRECARGA: Con motor y separador personalizado
QString Auto::mostrarInfo(bool incluirMotor, const QString &separador) const {
    QString info = QString("Auto: %1%2%3%4(%5)%6%7 puertas")
        .arg(modelo)
        .arg(separador)
        .arg(patente)
        .arg(separador)
        .arg(anio)
        .arg(separador)
        .arg(puertas);
    
    if (incluirMotor) {
        info += separador + motor.getDetalles();
    }
    return info;
}
