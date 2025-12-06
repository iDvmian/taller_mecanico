#include "moto.h"

// ==========================================
// SOBRECARGA DE CONSTRUCTORES
// ==========================================

// Constructor por defecto
Moto::Moto() : Vehiculo(), tieneCajon(false) {}

// Constructor completo
Moto::Moto(const QString &patente, const QString &modelo, const QString &anio,
           const QString &nMotor, int cc, bool cajon)
    : Vehiculo(patente, modelo, anio, nMotor, cc), tieneCajon(cajon) {}

// SOBRECARGA: Constructor sin especificar cajón (por defecto sin cajón)
Moto::Moto(const QString &patente, const QString &modelo, const QString &anio,
           const QString &nMotor, int cc)
    : Vehiculo(patente, modelo, anio, nMotor, cc), tieneCajon(false) {}

// Getters y Setters
bool Moto::getTieneCajon() const { return tieneCajon; }
void Moto::setTieneCajon(bool cajon) { this->tieneCajon = cajon; }

// ==========================================
// SOBREESCRITURA (Override) - POLIMORFISMO
// ==========================================

QString Moto::getTipo() const {
    return "MOTO";
}

QString Moto::getInfoAdicional() const {
    return QString("Cajón: %1").arg(tieneCajon ? "Sí" : "No");
}

// ==========================================
// SOBRECARGA DE MÉTODOS
// ==========================================

// Versión básica - solo info principal
QString Moto::mostrarInfo() const {
    return QString("Moto: %1 %2 (%3) - Cajón: %4")
        .arg(modelo)
        .arg(patente)
        .arg(anio)
        .arg(tieneCajon ? "Sí" : "No");
}

// SOBRECARGA: Con opción de incluir motor
QString Moto::mostrarInfo(bool incluirMotor) const {
    if (incluirMotor) {
        return QString("Moto: %1 %2 (%3) - Cajón: %4 | %5")
            .arg(modelo)
            .arg(patente)
            .arg(anio)
            .arg(tieneCajon ? "Sí" : "No")
            .arg(motor.getDetalles());
    }
    return mostrarInfo();
}
