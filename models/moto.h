#ifndef MOTO_H
#define MOTO_H

#include "vehiculo.h"

// ==========================================
// CLASE DERIVADA - Moto (HERENCIA)
// ==========================================
class Moto : public Vehiculo {
private:
    bool tieneCajon;

public:
    // ==========================================
    // SOBRECARGA DE CONSTRUCTORES
    // ==========================================
    
    // Constructor por defecto
    Moto();
    
    // Constructor completo
    Moto(const QString &patente, const QString &modelo, const QString &anio,
         const QString &nMotor, int cc, bool cajon);
    
    // SOBRECARGA: Constructor sin cajón (por defecto false)
    Moto(const QString &patente, const QString &modelo, const QString &anio,
         const QString &nMotor, int cc);

    // Getters
    bool getTieneCajon() const;

    // Setters
    void setTieneCajon(bool cajon);

    // ==========================================
    // SOBREESCRITURA de métodos virtuales (POLIMORFISMO)
    // ==========================================
    QString getTipo() const override;
    QString getInfoAdicional() const override;
    
    // ==========================================
    // SOBRECARGA DE MÉTODOS
    // ==========================================
    
    // Mostrar info básica
    QString mostrarInfo() const;
    
    // SOBRECARGA: Mostrar info con detalle del motor
    QString mostrarInfo(bool incluirMotor) const;
};

#endif // MOTO_H
