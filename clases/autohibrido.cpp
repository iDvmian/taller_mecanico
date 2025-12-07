#include "autohibrido.h"

// ==========================================
// SOBRECARGA DE CONSTRUCTORES
// ==========================================

// Constructor por defecto
AutoHibrido::AutoHibrido() : Auto(), porcentajeBateria(100) {}

// Constructor completo
AutoHibrido::AutoHibrido(const QString &patente, const QString &modelo, const QString &anio,
                         const QString &nMotor, int cc, int puertas, int bateria)
    : Auto(patente, modelo, anio, nMotor, cc, puertas), porcentajeBateria(bateria) {}

// SOBRECARGA: Constructor con batería al 100% por defecto
AutoHibrido::AutoHibrido(const QString &patente, const QString &modelo, const QString &anio,
                         const QString &nMotor, int cc, int puertas)
    : Auto(patente, modelo, anio, nMotor, cc, puertas), porcentajeBateria(100) {}

// ==========================================
// Implementación de IElectrico (HERENCIA MÚLTIPLE)
// ==========================================
QString AutoHibrido::getNivelBateria() const {
    return QString("%1%").arg(porcentajeBateria);
}

// Getters y Setters
int AutoHibrido::getPorcentajeBateria() const { return porcentajeBateria; }
void AutoHibrido::setPorcentajeBateria(int porcentaje) { 
    // Validar rango 0-100
    if (porcentaje < 0) porcentaje = 0;
    if (porcentaje > 100) porcentaje = 100;
    this->porcentajeBateria = porcentaje; 
}

// ==========================================
// SOBREESCRITURA (Override) - POLIMORFISMO
// ==========================================

QString AutoHibrido::getTipo() const {
    return "HIBRIDO";
}

QString AutoHibrido::getInfoAdicional() const {
    return QString("Puertas: %1 | Batería: %2%").arg(puertas).arg(porcentajeBateria);
}

// ==========================================
// SOBRECARGA DE MÉTODOS
// ==========================================

// Cargar batería al 100%
void AutoHibrido::cargarBateria() {
    porcentajeBateria = 100;
}

// SOBRECARGA: Cargar batería a un porcentaje específico
void AutoHibrido::cargarBateria(int porcentaje) {
    if (porcentaje < 0) porcentaje = 0;
    if (porcentaje > 100) porcentaje = 100;
    porcentajeBateria = porcentaje;
}

// SOBRECARGA: Cargar batería con tiempo de carga (simulación)
void AutoHibrido::cargarBateria(int porcentaje, int minutosCarga) {
    // Simula que la carga depende del tiempo
    // Por cada 10 minutos se carga un 10% adicional (máximo el porcentaje indicado)
    int cargaReal = (minutosCarga / 10) * 10;
    if (cargaReal > porcentaje) cargaReal = porcentaje;
    
    porcentajeBateria += cargaReal;
    if (porcentajeBateria > 100) porcentajeBateria = 100;
}
