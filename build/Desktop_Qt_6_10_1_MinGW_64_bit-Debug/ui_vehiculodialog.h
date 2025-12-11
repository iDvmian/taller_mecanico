/********************************************************************************
** Form generated from reading UI file 'vehiculodialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VEHICULODIALOG_H
#define UI_VEHICULODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_VehiculoDialog
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *titleLabel;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *editPatente;
    QLabel *label1;
    QLineEdit *editModelo;
    QLabel *label2;
    QLineEdit *editAnio;
    QLabel *label3;
    QLineEdit *editSerieMotor;
    QLabel *labelCC;
    QSpinBox *spinCC;
    QLabel *labelEspecifico;
    QSpinBox *spinEspecifico;
    QCheckBox *checkCajon;
    QLabel *labelBateria;
    QSpinBox *spinBateria;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem1;
    QPushButton *btnCancelar;
    QPushButton *btnAceptar;

    void setupUi(QDialog *VehiculoDialog)
    {
        if (VehiculoDialog->objectName().isEmpty())
            VehiculoDialog->setObjectName("VehiculoDialog");
        VehiculoDialog->resize(480, 480);
        VehiculoDialog->setStyleSheet(QString::fromUtf8("\n"
"QDialog {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    color: #ea6f15;\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    padding-bottom: 10px;\n"
"}\n"
"\n"
"QLineEdit, QSpinBox {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 4px;\n"
"    padding: 6px 10px;\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus, QSpinBox:focus {\n"
"    border: 2px solid #ea6f15;\n"
"    background-color: #fffaf5;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #999999;\n"
"}\n"
"\n"
"QSpinBox::up-button, QSpinBox::down-button {\n"
"    background-color: #ea6f15;\n"
"    border: none;\n"
"    width: 20px;\n"
"}\n"
"\n"
"QSpinBox::up-button:hover, QSpinBox::down-button:hover {\n"
"    background-color: #f58025;\n"
"}\n"
"\n"
"QCheckBox {\n"
"    color: #333333;\n"
"    font-size:"
                        " 13px;\n"
"    font-weight: bold;\n"
"    spacing: 8px;\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 4px;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #ea6f15;\n"
"    border-color: #ea6f15;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #ea6f15;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 12px 24px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    min-width: 120px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #f58025;\n"
"}\n"
"\n"
"QPushButton#btnCancelar {\n"
"    background-color: #888888;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QPushButton#btnCancelar:hover {\n"
"    background-color: #999999;\n"
"}\n"
"   "));
        vboxLayout = new QVBoxLayout(VehiculoDialog);
        vboxLayout->setSpacing(14);
        vboxLayout->setContentsMargins(24, 24, 24, 24);
        vboxLayout->setObjectName("vboxLayout");
        titleLabel = new QLabel(VehiculoDialog);
        titleLabel->setObjectName("titleLabel");

        vboxLayout->addWidget(titleLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignVCenter);
        formLayout->setHorizontalSpacing(16);
        formLayout->setVerticalSpacing(10);
        label = new QLabel(VehiculoDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        editPatente = new QLineEdit(VehiculoDialog);
        editPatente->setObjectName("editPatente");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, editPatente);

        label1 = new QLabel(VehiculoDialog);
        label1->setObjectName("label1");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label1);

        editModelo = new QLineEdit(VehiculoDialog);
        editModelo->setObjectName("editModelo");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, editModelo);

        label2 = new QLabel(VehiculoDialog);
        label2->setObjectName("label2");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label2);

        editAnio = new QLineEdit(VehiculoDialog);
        editAnio->setObjectName("editAnio");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, editAnio);

        label3 = new QLabel(VehiculoDialog);
        label3->setObjectName("label3");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label3);

        editSerieMotor = new QLineEdit(VehiculoDialog);
        editSerieMotor->setObjectName("editSerieMotor");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, editSerieMotor);

        labelCC = new QLabel(VehiculoDialog);
        labelCC->setObjectName("labelCC");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelCC);

        spinCC = new QSpinBox(VehiculoDialog);
        spinCC->setObjectName("spinCC");
        spinCC->setMinimum(50);
        spinCC->setMaximum(10000);
        spinCC->setValue(1600);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, spinCC);

        labelEspecifico = new QLabel(VehiculoDialog);
        labelEspecifico->setObjectName("labelEspecifico");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, labelEspecifico);

        spinEspecifico = new QSpinBox(VehiculoDialog);
        spinEspecifico->setObjectName("spinEspecifico");
        spinEspecifico->setMinimum(2);
        spinEspecifico->setMaximum(5);
        spinEspecifico->setValue(4);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, spinEspecifico);

        checkCajon = new QCheckBox(VehiculoDialog);
        checkCajon->setObjectName("checkCajon");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, checkCajon);

        labelBateria = new QLabel(VehiculoDialog);
        labelBateria->setObjectName("labelBateria");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, labelBateria);

        spinBateria = new QSpinBox(VehiculoDialog);
        spinBateria->setObjectName("spinBateria");
        spinBateria->setMinimum(0);
        spinBateria->setMaximum(100);
        spinBateria->setValue(100);

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, spinBateria);


        vboxLayout->addLayout(formLayout);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(spacerItem);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(12);
        hboxLayout->setObjectName("hboxLayout");
        spacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem1);

        btnCancelar = new QPushButton(VehiculoDialog);
        btnCancelar->setObjectName("btnCancelar");

        hboxLayout->addWidget(btnCancelar);

        btnAceptar = new QPushButton(VehiculoDialog);
        btnAceptar->setObjectName("btnAceptar");

        hboxLayout->addWidget(btnAceptar);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(VehiculoDialog);

        QMetaObject::connectSlotsByName(VehiculoDialog);
    } // setupUi

    void retranslateUi(QDialog *VehiculoDialog)
    {
        VehiculoDialog->setWindowTitle(QCoreApplication::translate("VehiculoDialog", "Registro de Veh\303\255culo", nullptr));
        titleLabel->setText(QCoreApplication::translate("VehiculoDialog", "DATOS DEL VEH\303\215CULO", nullptr));
        label->setText(QCoreApplication::translate("VehiculoDialog", "Patente:", nullptr));
        editPatente->setPlaceholderText(QCoreApplication::translate("VehiculoDialog", "Ej: ABCD-12", nullptr));
        label1->setText(QCoreApplication::translate("VehiculoDialog", "Modelo:", nullptr));
        editModelo->setPlaceholderText(QCoreApplication::translate("VehiculoDialog", "Ej: Toyota Corolla", nullptr));
        label2->setText(QCoreApplication::translate("VehiculoDialog", "A\303\261o:", nullptr));
        editAnio->setPlaceholderText(QCoreApplication::translate("VehiculoDialog", "Ej: 2024", nullptr));
        label3->setText(QCoreApplication::translate("VehiculoDialog", "Serie Motor:", nullptr));
        editSerieMotor->setPlaceholderText(QCoreApplication::translate("VehiculoDialog", "N\303\272mero de serie del motor", nullptr));
        labelCC->setText(QCoreApplication::translate("VehiculoDialog", "Cilindrada:", nullptr));
        spinCC->setSuffix(QCoreApplication::translate("VehiculoDialog", " CC", nullptr));
        labelEspecifico->setText(QCoreApplication::translate("VehiculoDialog", "Puertas:", nullptr));
        checkCajon->setText(QCoreApplication::translate("VehiculoDialog", "Tiene caj\303\263n de carga", nullptr));
        labelBateria->setText(QCoreApplication::translate("VehiculoDialog", "Bater\303\255a:", nullptr));
        spinBateria->setSuffix(QCoreApplication::translate("VehiculoDialog", " %", nullptr));
        btnCancelar->setText(QCoreApplication::translate("VehiculoDialog", "CANCELAR", nullptr));
        btnAceptar->setText(QCoreApplication::translate("VehiculoDialog", "GUARDAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VehiculoDialog: public Ui_VehiculoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VEHICULODIALOG_H
