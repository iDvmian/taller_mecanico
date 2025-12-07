#ifndef REPUESTO_H
#define REPUESTO_H

#include <QString>
#include <QTextStream>

// ==========================================
// CLASE REPUESTO - Inventario de partes
// ==========================================
class Repuesto {
private:
    int id;
    QString codigo;
    QString nombre;
    QString descripcion;
    QString categoria;      // Motor, Frenos, Suspensión, etc.
    double precioCompra;
    double precioVenta;
    int stockActual;
    int stockMinimo;        // Para alertas de stock crítico

public:
    Repuesto();
    Repuesto(const QString &codigo, const QString &nombre, const QString &descripcion,
             const QString &categoria, double precioCompra, double precioVenta,
             int stockActual, int stockMinimo);

    // Getters
    int getId() const;
    QString getCodigo() const;
    QString getNombre() const;
    QString getDescripcion() const;
    QString getCategoria() const;
    double getPrecioCompra() const;
    double getPrecioVenta() const;
    int getStockActual() const;
    int getStockMinimo() const;
    double getMargenGanancia() const;
    bool esStockCritico() const;

    // Setters
    void setId(int id);
    void setCodigo(const QString &codigo);
    void setNombre(const QString &nombre);
    void setDescripcion(const QString &descripcion);
    void setCategoria(const QString &categoria);
    void setPrecioCompra(double precio);
    void setPrecioVenta(double precio);
    void setStockActual(int stock);
    void setStockMinimo(int stock);

    // Operaciones de inventario
    bool agregarStock(int cantidad);
    bool descontarStock(int cantidad);

    // Sobrecarga de operadores
    bool operator==(const Repuesto &otro) const;
    bool operator<(const Repuesto &otro) const;
    friend QTextStream &operator<<(QTextStream &out, const Repuesto &r);
};

#endif // REPUESTO_H




