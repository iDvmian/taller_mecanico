#ifndef AUTO_H
#define AUTO_H

#include "vehiculo.h"

// ==========================================
// CLASE DERIVADA - Auto (HERENCIA)
// ==========================================
class Auto : public Vehiculo {
protected:
    int puertas;

public:
    // ==========================================
    // SOBRECARGA DE CONSTRUCTORES
    // ==========================================
    
    // Constructor por defecto
    Auto();
    
    // Constructor completo
    Auto(const QString &patente, const QString &modelo, const QString &anio,
         const QString &nMotor, int cc, int puertas);
    
    // SOBRECARGA: Constructor sin especificar motor (usa valores por defecto)
    Auto(const QString &patente, const QString &modelo, const QString &anio, int puertas);

    // Getters
    int getPuertas() const;

    // Setters
    void setPuertas(int puertas);

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
    
    // SOBRECARGA: Mostrar info con formato personalizado
    QString mostrarInfo(bool incluirMotor, const QString &separador) const;
};

#endif // AUTO_H
