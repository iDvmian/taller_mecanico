#ifndef REPUESTODIALOG_H
#define REPUESTODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>

#include "../models/repuesto.h"

class RepuestoDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit *codigoEdit;
    QLineEdit *nombreEdit;
    QTextEdit *descripcionEdit;
    QComboBox *categoriaCombo;
    QDoubleSpinBox *precioCompraSpin;
    QDoubleSpinBox *precioVentaSpin;
    QSpinBox *stockActualSpin;
    QSpinBox *stockMinimoSpin;
    
    Repuesto repuesto;
    bool modoEdicion;

    void setupUI();
    void cargarDatos();

public:
    explicit RepuestoDialog(QWidget *parent = nullptr);
    RepuestoDialog(const Repuesto &repuesto, QWidget *parent = nullptr);

    Repuesto getRepuesto() const;

private slots:
    void aceptar();
    void calcularMargen();
};

#endif // REPUESTODIALOG_H



