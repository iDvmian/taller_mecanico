#ifndef VEHICULO_H
#define VEHICULO_H

#include <QString>
#include <QTextStream>
#include "motor.h"

// ==========================================
// Interfaz para funcionalidad eléctrica (Herencia Múltiple)
// ==========================================
class IElectrico {
public:
    virtual ~IElectrico() = default;
    virtual QString getNivelBateria() const = 0;
};

// ==========================================
// CLASE BASE ABSTRACTA - Vehiculo
// ==========================================
class Vehiculo {
protected:
    int id;
    QString patente;
    QString modelo;
    QString anio;
    Motor motor;  // COMPOSICIÓN: El vehículo "posee" un motor
    int clienteId;

public:
    Vehiculo();
    Vehiculo(const QString &patente, const QString &modelo, const QString &anio,
             const QString &nMotor, int cc);
    virtual ~Vehiculo() = default;

    // Getters
    int getId() const;
    QString getPatente() const;
    QString getModelo() const;
    QString getAnio() const;
    Motor getMotor() const;
    int getClienteId() const;

    // Setters
    void setId(int id);
    void setPatente(const QString &patente);
    void setModelo(const QString &modelo);
    void setAnio(const QString &anio);
    void setMotor(const Motor &motor);
    void setClienteId(int clienteId);

    // Método Virtual Puro (Clase Abstracta)
    virtual QString getTipo() const = 0;
    virtual QString getInfoAdicional() const = 0;

    // Para mostrar información completa
    QString getInfo() const;

    // ==========================================
    // SOBRECARGA DE OPERADORES
    // ==========================================
    
    // Operador == (comparar por patente)
    bool operator==(const Vehiculo &otro) const;
    
    // Operador != (diferente)
    bool operator!=(const Vehiculo &otro) const;
    
    // Operador < (para ordenar por año)
    bool operator<(const Vehiculo &otro) const;
    
    // Operador << (inserción en stream) - Friend function
    friend QTextStream &operator<<(QTextStream &out, const Vehiculo &v);
};

#endif // VEHICULO_H
