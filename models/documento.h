#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <QString>
#include <QDateTime>
#include <QVector>
#include <QTextStream>

// ==========================================
// Estructura para items de documento
// ==========================================
struct ItemDocumento {
    QString descripcion;
    int cantidad;
    double precioUnitario;
    double subtotal;
};

// ==========================================
// CLASE ABSTRACTA - Documento Base
// (Para Herencia: Factura y Presupuesto heredan de aquí)
// ==========================================
class Documento {
protected:
    int id;
    QString numero;
    int clienteId;
    int ordenTrabajoId;       // Puede ser 0 si no está asociada a OT
    QDateTime fecha;
    QDateTime fechaVencimiento;
    QVector<ItemDocumento> items;
    double subtotal;
    double impuesto;          // IVA u otro
    double descuento;
    QString observaciones;

public:
    Documento();
    Documento(const QString &numero, int clienteId);
    virtual ~Documento() = default;

    // Getters
    int getId() const;
    QString getNumero() const;
    int getClienteId() const;
    int getOrdenTrabajoId() const;
    QDateTime getFecha() const;
    QDateTime getFechaVencimiento() const;
    QVector<ItemDocumento> getItems() const;
    double getSubtotal() const;
    double getImpuesto() const;
    double getDescuento() const;
    QString getObservaciones() const;

    // Setters
    void setId(int id);
    void setNumero(const QString &numero);
    void setClienteId(int clienteId);
    void setOrdenTrabajoId(int otId);
    void setFecha(const QDateTime &fecha);
    void setFechaVencimiento(const QDateTime &fecha);
    void setSubtotal(double subtotal);
    void setImpuesto(double impuesto);
    void setDescuento(double descuento);
    void setObservaciones(const QString &obs);

    // Gestión de items
    void agregarItem(const ItemDocumento &item);
    void quitarItem(int index);
    void limpiarItems();
    void recalcularSubtotal();

    // ==========================================
    // MÉTODOS VIRTUALES PUROS (Clase Abstracta)
    // ==========================================
    virtual QString getTipo() const = 0;
    virtual double getTotal() const = 0;
    virtual bool estaVencido() const = 0;
    virtual QString getEstado() const = 0;

    // Sobrecarga de operadores
    bool operator==(const Documento &otro) const;
    bool operator<(const Documento &otro) const;
    friend QTextStream &operator<<(QTextStream &out, const Documento &d);
};

// ==========================================
// CLASE FACTURA - Hereda de Documento
// ==========================================
class Factura : public Documento {
public:
    enum EstadoPago {
        PENDIENTE,
        PAGADA,
        PARCIAL,
        VENCIDA,
        ANULADA
    };

private:
    EstadoPago estadoPago;
    double montoPagado;
    QDateTime fechaPago;
    QString metodoPago;       // Efectivo, Tarjeta, Transferencia

public:
    Factura();
    Factura(const QString &numero, int clienteId);

    // Getters específicos
    EstadoPago getEstadoPago() const;
    double getMontoPagado() const;
    double getSaldoPendiente() const;
    QDateTime getFechaPago() const;
    QString getMetodoPago() const;

    // Setters específicos
    void setEstadoPago(EstadoPago estado);
    void setEstadoPagoFromInt(int estado);
    void setMontoPagado(double monto);
    void setFechaPago(const QDateTime &fecha);
    void setMetodoPago(const QString &metodo);

    // Operaciones de pago
    bool registrarPago(double monto, const QString &metodo);
    bool anular();

    // ==========================================
    // SOBREESCRITURA de métodos virtuales (POLIMORFISMO)
    // ==========================================
    QString getTipo() const override;
    double getTotal() const override;
    bool estaVencido() const override;
    QString getEstado() const override;

    static QString estadoPagoToString(EstadoPago estado);
};

// ==========================================
// CLASE PRESUPUESTO - Hereda de Documento
// ==========================================
class Presupuesto : public Documento {
public:
    enum EstadoPresupuesto {
        BORRADOR,
        ENVIADO,
        APROBADO,
        RECHAZADO,
        VENCIDO,
        CONVERTIDO      // Convertido a factura
    };

private:
    EstadoPresupuesto estadoPresupuesto;
    int diasValidez;
    int facturaGeneradaId;    // ID de factura si fue convertido

public:
    Presupuesto();
    Presupuesto(const QString &numero, int clienteId, int diasValidez = 15);

    // Getters específicos
    EstadoPresupuesto getEstadoPresupuesto() const;
    int getDiasValidez() const;
    int getFacturaGeneradaId() const;
    int getDiasRestantes() const;

    // Setters específicos
    void setEstadoPresupuesto(EstadoPresupuesto estado);
    void setEstadoPresupuestoFromInt(int estado);
    void setDiasValidez(int dias);
    void setFacturaGeneradaId(int facturaId);

    // Operaciones
    bool enviar();
    bool aprobar();
    bool rechazar();
    bool convertirAFactura(int facturaId);

    // ==========================================
    // SOBREESCRITURA de métodos virtuales (POLIMORFISMO)
    // ==========================================
    QString getTipo() const override;
    double getTotal() const override;
    bool estaVencido() const override;
    QString getEstado() const override;

    static QString estadoToString(EstadoPresupuesto estado);
};

#endif // DOCUMENTO_H



