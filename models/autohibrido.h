#ifndef AUTOHIBRIDO_H
#define AUTOHIBRIDO_H

#include "auto.h"
#include "vehiculo.h"  // Para IElectrico

// ==========================================
// CLASE CON HERENCIA MÚLTIPLE - AutoHibrido
// Hereda de: Auto (Vehiculo) + IElectrico (interfaz)
// ==========================================
class AutoHibrido : public Auto, public IElectrico {
private:
    int porcentajeBateria;

public:
    // ==========================================
    // SOBRECARGA DE CONSTRUCTORES
    // ==========================================
    
    // Constructor por defecto
    AutoHibrido();
    
    // Constructor completo
    AutoHibrido(const QString &patente, const QString &modelo, const QString &anio,
                const QString &nMotor, int cc, int puertas, int bateria);
    
    // SOBRECARGA: Constructor con batería al 100% por defecto
    AutoHibrido(const QString &patente, const QString &modelo, const QString &anio,
                const QString &nMotor, int cc, int puertas);

    // ==========================================
    // Implementación de IElectrico (HERENCIA MÚLTIPLE)
    // ==========================================
    QString getNivelBateria() const override;

    // Getters
    int getPorcentajeBateria() const;

    // Setters
    void setPorcentajeBateria(int porcentaje);

    // ==========================================
    // SOBREESCRITURA de métodos virtuales
    // ==========================================
    QString getTipo() const override;
    QString getInfoAdicional() const override;
    
    // ==========================================
    // SOBRECARGA DE MÉTODOS
    // ==========================================
    
    // Cargar batería al 100%
    void cargarBateria();
    
    // SOBRECARGA: Cargar batería a un porcentaje específico
    void cargarBateria(int porcentaje);
    
    // SOBRECARGA: Cargar batería con tiempo de carga
    void cargarBateria(int porcentaje, int minutosCarga);
};

#endif // AUTOHIBRIDO_H
