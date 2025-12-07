#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include <QVector>
#include <QTextStream>
#include <memory>
#include "vehiculo.h"

// ==========================================
// CLASE CLIENTE - Con Agregación de Vehículos
// ==========================================
class Cliente {
private:
    int id;
    QString rut;
    QString nombre;
    QString apellido;
    QString telefono;
    QString direccion;

public:
    Cliente();
    Cliente(const QString &rut, const QString &nombre, const QString &apellido,
            const QString &telefono, const QString &direccion);

    // Getters
    int getId() const;
    QString getRut() const;
    QString getNombre() const;
    QString getApellido() const;
    QString getTelefono() const;
    QString getDireccion() const;
    QString getNombreCompleto() const;

    // Setters
    void setId(int id);
    void setRut(const QString &rut);
    void setNombre(const QString &nombre);
    void setApellido(const QString &apellido);
    void setTelefono(const QString &telefono);
    void setDireccion(const QString &direccion);

    // ==========================================
    // SOBRECARGA DE MÉTODOS (mismo nombre, diferentes parámetros)
    // ==========================================
    
    // Validar RUT con QString
    static bool validarRut(const QString &rut);
    
    // Validar RUT con longitud mínima personalizada
    static bool validarRut(const QString &rut, int longitudMinima);

    // Buscar cliente por nombre (sobrecarga)
    bool coincide(const QString &busqueda) const;
    
    // Buscar cliente por nombre Y apellido (sobrecarga)
    bool coincide(const QString &nombreBuscar, const QString &apellidoBuscar) const;

    // ==========================================
    // SOBRECARGA DE OPERADORES
    // ==========================================
    
    // Operador == (comparar por RUT)
    bool operator==(const Cliente &otro) const;
    
    // Operador != (diferente)
    bool operator!=(const Cliente &otro) const;
    
    // Operador < (para ordenar por apellido)
    bool operator<(const Cliente &otro) const;
    
    // Operador << (inserción en stream)
    friend QTextStream &operator<<(QTextStream &out, const Cliente &c);
};

#endif // CLIENTE_H
