/********************************************************************************
** Form generated from reading UI file 'clientedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTEDIALOG_H
#define UI_CLIENTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ClienteDialog
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *titleLabel;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *editRut;
    QLabel *label1;
    QLineEdit *editNombre;
    QLabel *label2;
    QLineEdit *editApellido;
    QLabel *label3;
    QLineEdit *editTelefono;
    QLabel *label4;
    QLineEdit *editDireccion;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem1;
    QPushButton *btnCancelar;
    QPushButton *btnAceptar;

    void setupUi(QDialog *ClienteDialog)
    {
        if (ClienteDialog->objectName().isEmpty())
            ClienteDialog->setObjectName("ClienteDialog");
        ClienteDialog->resize(480, 380);
        ClienteDialog->setStyleSheet(QString::fromUtf8("\n"
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
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 4px;\n"
"    padding: 6px 10px;\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"    min-height: 20px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #ea6f15;\n"
"    background-color: #fffaf5;\n"
"}\n"
"\n"
"QLineEdit::placeholder {\n"
"    color: #999999;\n"
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
"QPushButton"
                        "#btnCancelar {\n"
"    background-color: #888888;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QPushButton#btnCancelar:hover {\n"
"    background-color: #999999;\n"
"}\n"
"   "));
        vboxLayout = new QVBoxLayout(ClienteDialog);
        vboxLayout->setSpacing(16);
        vboxLayout->setContentsMargins(24, 24, 24, 24);
        vboxLayout->setObjectName("vboxLayout");
        titleLabel = new QLabel(ClienteDialog);
        titleLabel->setObjectName("titleLabel");

        vboxLayout->addWidget(titleLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignVCenter);
        formLayout->setHorizontalSpacing(16);
        formLayout->setVerticalSpacing(12);
        label = new QLabel(ClienteDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        editRut = new QLineEdit(ClienteDialog);
        editRut->setObjectName("editRut");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, editRut);

        label1 = new QLabel(ClienteDialog);
        label1->setObjectName("label1");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label1);

        editNombre = new QLineEdit(ClienteDialog);
        editNombre->setObjectName("editNombre");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, editNombre);

        label2 = new QLabel(ClienteDialog);
        label2->setObjectName("label2");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label2);

        editApellido = new QLineEdit(ClienteDialog);
        editApellido->setObjectName("editApellido");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, editApellido);

        label3 = new QLabel(ClienteDialog);
        label3->setObjectName("label3");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label3);

        editTelefono = new QLineEdit(ClienteDialog);
        editTelefono->setObjectName("editTelefono");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, editTelefono);

        label4 = new QLabel(ClienteDialog);
        label4->setObjectName("label4");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label4);

        editDireccion = new QLineEdit(ClienteDialog);
        editDireccion->setObjectName("editDireccion");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, editDireccion);


        vboxLayout->addLayout(formLayout);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vboxLayout->addItem(spacerItem);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(12);
        hboxLayout->setObjectName("hboxLayout");
        spacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem1);

        btnCancelar = new QPushButton(ClienteDialog);
        btnCancelar->setObjectName("btnCancelar");

        hboxLayout->addWidget(btnCancelar);

        btnAceptar = new QPushButton(ClienteDialog);
        btnAceptar->setObjectName("btnAceptar");

        hboxLayout->addWidget(btnAceptar);


        vboxLayout->addLayout(hboxLayout);


        retranslateUi(ClienteDialog);

        QMetaObject::connectSlotsByName(ClienteDialog);
    } // setupUi

    void retranslateUi(QDialog *ClienteDialog)
    {
        ClienteDialog->setWindowTitle(QCoreApplication::translate("ClienteDialog", "Registro de Cliente", nullptr));
        titleLabel->setText(QCoreApplication::translate("ClienteDialog", "DATOS DEL CLIENTE", nullptr));
        label->setText(QCoreApplication::translate("ClienteDialog", "RUT:", nullptr));
        editRut->setPlaceholderText(QCoreApplication::translate("ClienteDialog", "Ej: 12.345.678-9", nullptr));
        label1->setText(QCoreApplication::translate("ClienteDialog", "Nombre:", nullptr));
        editNombre->setPlaceholderText(QCoreApplication::translate("ClienteDialog", "Nombre del cliente", nullptr));
        label2->setText(QCoreApplication::translate("ClienteDialog", "Apellido:", nullptr));
        editApellido->setPlaceholderText(QCoreApplication::translate("ClienteDialog", "Apellido del cliente", nullptr));
        label3->setText(QCoreApplication::translate("ClienteDialog", "Tel\303\251fono:", nullptr));
        editTelefono->setPlaceholderText(QCoreApplication::translate("ClienteDialog", "+56 9 1234 5678", nullptr));
        label4->setText(QCoreApplication::translate("ClienteDialog", "Direcci\303\263n:", nullptr));
        editDireccion->setPlaceholderText(QCoreApplication::translate("ClienteDialog", "Direcci\303\263n completa", nullptr));
        btnCancelar->setText(QCoreApplication::translate("ClienteDialog", "CANCELAR", nullptr));
        btnAceptar->setText(QCoreApplication::translate("ClienteDialog", "GUARDAR", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClienteDialog: public Ui_ClienteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTEDIALOG_H
