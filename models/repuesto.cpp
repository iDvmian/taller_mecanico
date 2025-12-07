#include "repuesto.h"

Repuesto::Repuesto()
    : id(0), precioCompra(0), precioVenta(0), stockActual(0), stockMinimo(5) {}

Repuesto::Repuesto(const QString &codigo, const QString &nombre, const QString &descripcion,
                   const QString &categoria, double precioCompra, double precioVenta,
                   int stockActual, int stockMinimo)
    : id(0), codigo(codigo), nombre(nombre), descripcion(descripcion),
      categoria(categoria), precioCompra(precioCompra), precioVenta(precioVenta),
      stockActual(stockActual), stockMinimo(stockMinimo) {}

// Getters
int Repuesto::getId() const { return id; }
QString Repuesto::getCodigo() const { return codigo; }
QString Repuesto::getNombre() const { return nombre; }
QString Repuesto::getDescripcion() const { return descripcion; }
QString Repuesto::getCategoria() const { return categoria; }
double Repuesto::getPrecioCompra() const { return precioCompra; }
double Repuesto::getPrecioVenta() const { return precioVenta; }
int Repuesto::getStockActual() const { return stockActual; }
int Repuesto::getStockMinimo() const { return stockMinimo; }

double Repuesto::getMargenGanancia() const {
    if (precioCompra <= 0) return 0;
    return ((precioVenta - precioCompra) / precioCompra) * 100;
}

bool Repuesto::esStockCritico() const {
    return stockActual <= stockMinimo;
}

// Setters
void Repuesto::setId(int id) { this->id = id; }
void Repuesto::setCodigo(const QString &codigo) { this->codigo = codigo; }
void Repuesto::setNombre(const QString &nombre) { this->nombre = nombre; }
void Repuesto::setDescripcion(const QString &descripcion) { this->descripcion = descripcion; }
void Repuesto::setCategoria(const QString &categoria) { this->categoria = categoria; }
void Repuesto::setPrecioCompra(double precio) { this->precioCompra = precio; }
void Repuesto::setPrecioVenta(double precio) { this->precioVenta = precio; }
void Repuesto::setStockActual(int stock) { this->stockActual = stock; }
void Repuesto::setStockMinimo(int stock) { this->stockMinimo = stock; }

// Operaciones de inventario
bool Repuesto::agregarStock(int cantidad) {
    if (cantidad < 0) return false;
    stockActual += cantidad;
    return true;
}

bool Repuesto::descontarStock(int cantidad) {
    if (cantidad < 0 || cantidad > stockActual) return false;
    stockActual -= cantidad;
    return true;
}

// Sobrecarga de operadores
bool Repuesto::operator==(const Repuesto &otro) const {
    return codigo == otro.codigo;
}

bool Repuesto::operator<(const Repuesto &otro) const {
    return nombre < otro.nombre;
}

QTextStream &operator<<(QTextStream &out, const Repuesto &r) {
    out << "[" << r.codigo << "] " << r.nombre << " - Stock: " << r.stockActual
        << " - $" << r.precioVenta;
    return out;
}




