#ifndef MOTOR_H
#define MOTOR_H

#include <QString>
#include <QTextStream>

// ==========================================
// CLASE MOTOR - Componente (Composición)
// ==========================================
class Motor {
private:
    QString numeroSerie;
    int cilindrada;

public:
    Motor();
    Motor(const QString &numeroSerie, int cilindrada);

    // Getters
    QString getNumeroSerie() const;
    int getCilindrada() const;
    QString getDetalles() const;

    // Setters
    void setNumeroSerie(const QString &numeroSerie);
    void setCilindrada(int cilindrada);

    // ==========================================
    // SOBRECARGA DE OPERADORES
    // ==========================================
    
    // Operador == (comparar por número de serie)
    bool operator==(const Motor &otro) const;
    
    // Operador != (diferente)
    bool operator!=(const Motor &otro) const;
    
    // Operador > (comparar por cilindrada - cuál es más potente)
    bool operator>(const Motor &otro) const;
    
    // Operador < (comparar por cilindrada)
    bool operator<(const Motor &otro) const;
    
    // Operador << (inserción en stream)
    friend QTextStream &operator<<(QTextStream &out, const Motor &m);
};

#endif // MOTOR_H
