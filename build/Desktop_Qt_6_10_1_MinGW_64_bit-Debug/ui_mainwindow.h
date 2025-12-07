/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *hboxLayout;
    QLabel *logoLabel;
    QVBoxLayout *vboxLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QSpacerItem *spacerItem;
    QTabWidget *tabWidget;
    QWidget *tabClientes;
    QHBoxLayout *hboxLayout1;
    QSplitter *splitter;
    QGroupBox *groupClientes;
    QVBoxLayout *vboxLayout1;
    QTableWidget *tablaClientes;
    QHBoxLayout *hboxLayout2;
    QPushButton *btnAgregarCliente;
    QPushButton *btnEditarCliente;
    QPushButton *btnHistorialCliente;
    QSpacerItem *spacerItem1;
    QPushButton *btnEliminarCliente;
    QGroupBox *groupVehiculos;
    QVBoxLayout *vboxLayout2;
    QTableWidget *tablaVehiculos;
    QHBoxLayout *hboxLayout3;
    QPushButton *btnAgregarAuto;
    QPushButton *btnAgregarMoto;
    QPushButton *btnAgregarHibrido;
    QPushButton *btnHistorialVehiculo;
    QSpacerItem *spacerItem2;
    QPushButton *btnEliminarVehiculo;
    QWidget *tabOrdenes;
    QVBoxLayout *vboxLayout3;
    QGroupBox *groupOrdenes;
    QVBoxLayout *vboxLayout4;
    QTableWidget *tablaOrdenes;
    QHBoxLayout *hboxLayout4;
    QPushButton *btnNuevaOrden;
    QPushButton *btnEditarOrden;
    QPushButton *btnCambiarEstado;
    QSpacerItem *spacerItem3;
    QWidget *tabInventario;
    QVBoxLayout *vboxLayout5;
    QGroupBox *groupInventario;
    QVBoxLayout *vboxLayout6;
    QTableWidget *tablaInventario;
    QHBoxLayout *hboxLayout5;
    QPushButton *btnNuevoRepuesto;
    QPushButton *btnEditarRepuesto;
    QPushButton *btnAjustarStock;
    QSpacerItem *spacerItem4;
    QPushButton *btnEliminarRepuesto;
    QWidget *tabAgenda;
    QHBoxLayout *hboxLayout6;
    QGroupBox *groupCalendario;
    QVBoxLayout *vboxLayout7;
    QCalendarWidget *calendario;
    QGroupBox *groupCitas;
    QVBoxLayout *vboxLayout8;
    QListWidget *listaCitas;
    QHBoxLayout *hboxLayout7;
    QPushButton *btnNuevaCita;
    QPushButton *btnEditarCita;
    QSpacerItem *spacerItem5;
    QPushButton *btnEliminarCita;
    QWidget *tabFacturacion;
    QVBoxLayout *vboxLayout9;
    QGroupBox *groupFacturas;
    QVBoxLayout *vboxLayout10;
    QTableWidget *tablaFacturas;
    QHBoxLayout *hboxLayout8;
    QPushButton *btnNuevaFactura;
    QPushButton *btnNuevoPresupuesto;
    QPushButton *btnRegistrarPago;
    QPushButton *btnVerDetalle;
    QPushButton *btnAnularFactura;
    QPushButton *btnConvertirFactura;
    QSpacerItem *spacerItem6;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 900);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"/* =============================================\n"
"   TEMA CLARO - TALLER MEC\303\201NICO\n"
"   ============================================= */\n"
"\n"
"* {\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"QMainWindow {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"\n"
"/* T\303\215TULO PRINCIPAL */\n"
"QLabel#titleLabel {\n"
"    font-size: 24px;\n"
"    font-weight: bold;\n"
"    color: #ea6f15;\n"
"    padding: 5px 0;\n"
"}\n"
"\n"
"QLabel#subtitleLabel {\n"
"    font-size: 12px;\n"
"    color: #666666;\n"
"    padding-bottom: 5px;\n"
"}\n"
"\n"
"/* =============================================\n"
"   PESTA\303\221AS\n"
"   ============================================= */\n"
"QTabWidget::pane {\n"
"    border: 1px solid #d0d0d0;\n"
"    background-color: #ffffff;\n"
"    border-radius: 6px;\n"
"    margin-top: -1px;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background-color: #e8e8e8;\n"
"    color: #555555;\n"
"    padding: 10px 22px;\n"
"    margin-right: 2px;\n"
"    border-top-left-"
                        "radius: 6px;\n"
"    border-top-right-radius: 6px;\n"
"    font-size: 13px;\n"
"    font-weight: 600;\n"
"    min-width: 90px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background-color: #ea6f15;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QTabBar::tab:hover:!selected {\n"
"    background-color: #d0d0d0;\n"
"}\n"
"\n"
"/* =============================================\n"
"   TABLAS\n"
"   ============================================= */\n"
"QTableWidget {\n"
"    background-color: #ffffff;\n"
"    alternate-background-color: #fafafa;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 6px;\n"
"    gridline-color: #e8e8e8;\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"    selection-background-color: #ea6f15;\n"
"    selection-color: #ffffff;\n"
"}\n"
"\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #e8e8e8;\n"
"}\n"
"\n"
"QTableWidget::item:selected {\n"
"    background-color: #ea6f15;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    backgrou"
                        "nd-color: #f0f0f0;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    background-color: #f8f8f8;\n"
"    color: #ea6f15;\n"
"    padding: 10px 8px;\n"
"    border: none;\n"
"    border-bottom: 2px solid #ea6f15;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"/* =============================================\n"
"   BOTONES PRINCIPALES\n"
"   ============================================= */\n"
"QPushButton {\n"
"    background-color: #ea6f15;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 10px 20px;\n"
"    font-size: 13px;\n"
"    font-weight: bold;\n"
"    min-width: 100px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #f58025;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #d56010;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: #cccccc;\n"
"    color: #888888;\n"
"}\n"
"\n"
"/* Botones de Editar */\n"
"QPushButton#btnEditarCliente,\n"
"QPushButton#btnEditarOrden,\n"
"QPushButton#btnEditarRepuesto,\n"
"QPu"
                        "shButton#btnEditarCita {\n"
"    background-color: #9a6140;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QPushButton#btnEditarCliente:hover,\n"
"QPushButton#btnEditarOrden:hover,\n"
"QPushButton#btnEditarRepuesto:hover,\n"
"QPushButton#btnEditarCita:hover {\n"
"    background-color: #b07050;\n"
"}\n"
"\n"
"/* Botones de Eliminar */\n"
"QPushButton#btnEliminarCliente,\n"
"QPushButton#btnEliminarVehiculo,\n"
"QPushButton#btnEliminarRepuesto,\n"
"QPushButton#btnEliminarCita {\n"
"    background-color: #c44444;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QPushButton#btnEliminarCliente:hover,\n"
"QPushButton#btnEliminarVehiculo:hover,\n"
"QPushButton#btnEliminarRepuesto:hover,\n"
"QPushButton#btnEliminarCita:hover {\n"
"    background-color: #d55555;\n"
"}\n"
"\n"
"/* Botones Secundarios */\n"
"QPushButton#btnHistorialCliente,\n"
"QPushButton#btnHistorialVehiculo,\n"
"QPushButton#btnCambiarEstado,\n"
"QPushButton#btnAjustarStock {\n"
"    background-color: #6c6c6c;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QPushButton#btnHistori"
                        "alCliente:hover,\n"
"QPushButton#btnHistorialVehiculo:hover,\n"
"QPushButton#btnCambiarEstado:hover,\n"
"QPushButton#btnAjustarStock:hover {\n"
"    background-color: #808080;\n"
"}\n"
"\n"
"/* Botones Verdes */\n"
"QPushButton#btnAgregarHibrido,\n"
"QPushButton#btnRegistrarPago {\n"
"    background-color: #4a9e4a;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QPushButton#btnAgregarHibrido:hover,\n"
"QPushButton#btnRegistrarPago:hover {\n"
"    background-color: #5cb85c;\n"
"}\n"
"\n"
"/* Botones Moto */\n"
"QPushButton#btnAgregarMoto {\n"
"    background-color: #ebb465;\n"
"    color: #333333;\n"
"}\n"
"\n"
"QPushButton#btnAgregarMoto:hover {\n"
"    background-color: #f5c478;\n"
"}\n"
"\n"
"/* =============================================\n"
"   GRUPOS / PANELES\n"
"   ============================================= */\n"
"QGroupBox {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 6px;\n"
"    margin-top: 16px;\n"
"    padding: 16px 12px 12px 12px;\n"
"    font-weight: bo"
                        "ld;\n"
"    color: #ea6f15;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 16px;\n"
"    padding: 0 8px;\n"
"    background-color: #ffffff;\n"
"    color: #ea6f15;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"/* =============================================\n"
"   LABELS\n"
"   ============================================= */\n"
"QLabel {\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"/* =============================================\n"
"   INPUTS\n"
"   ============================================= */\n"
"QLineEdit, QTextEdit, QSpinBox, QDoubleSpinBox, QComboBox, QDateEdit, QDateTimeEdit {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #c0c0c0;\n"
"    border-radius: 4px;\n"
"    padding: 5px 10px;\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"    min-height: 18px;\n"
"}\n"
"\n"
"QLineEdit:focus, QTextEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus, QComboBox:focus, QDateEdit:focus, QDateTimeEdit:focus {\n"
"    border: 2px solid #ea6f15;\n"
""
                        "    background-color: #fffaf5;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    border: none;\n"
"    width: 30px;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: none;\n"
"    border-left: 5px solid transparent;\n"
"    border-right: 5px solid transparent;\n"
"    border-top: 6px solid #ea6f15;\n"
"    margin-right: 10px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: #ffffff;\n"
"    color: #333333;\n"
"    selection-background-color: #ea6f15;\n"
"    selection-color: #ffffff;\n"
"    border: 1px solid #d0d0d0;\n"
"}\n"
"\n"
"/* =============================================\n"
"   SPLITTER\n"
"   ============================================= */\n"
"QSplitter::handle {\n"
"    background-color: #d0d0d0;\n"
"    width: 3px;\n"
"}\n"
"\n"
"QSplitter::handle:hover {\n"
"    background-color: #ea6f15;\n"
"}\n"
"\n"
"/* =============================================\n"
"   CALENDARIO\n"
"   ============================================= */\n"
"QCalendarWidget {\n"
"    background-color: #f"
                        "fffff;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"QCalendarWidget QToolButton {\n"
"    color: #ea6f15;\n"
"    background-color: transparent;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    padding: 6px;\n"
"}\n"
"\n"
"QCalendarWidget QToolButton:hover {\n"
"    background-color: #f0f0f0;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QCalendarWidget QMenu {\n"
"    background-color: #ffffff;\n"
"    color: #333333;\n"
"    border: 1px solid #d0d0d0;\n"
"}\n"
"\n"
"QCalendarWidget QSpinBox {\n"
"    background-color: #ffffff;\n"
"    color: #333333;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 4px;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar {\n"
"    background-color: #f8f8f8;\n"
"    padding: 6px;\n"
"}\n"
"\n"
"QCalendarWidget QAbstractItemView {\n"
"    background-color: #ffffff;\n"
"    color: #333333;\n"
"    selection-background-color: #ea6f15;\n"
"    selection-color: #ffffff;\n"
"    font-size: 12px;\n"
""
                        "}\n"
"\n"
"QCalendarWidget QAbstractItemView:disabled {\n"
"    color: #aaaaaa;\n"
"}\n"
"\n"
"/* =============================================\n"
"   LISTA DE CITAS\n"
"   ============================================= */\n"
"QListWidget {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #d0d0d0;\n"
"    border-radius: 6px;\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    padding: 10px 8px;\n"
"    border-radius: 4px;\n"
"    margin: 2px 0;\n"
"    border-left: 4px solid #ea6f15;\n"
"    background-color: #fafafa;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #ea6f15;\n"
"    color: #ffffff;\n"
"}\n"
"\n"
"QListWidget::item:hover:!selected {\n"
"    background-color: #f0f0f0;\n"
"}\n"
"\n"
"/* =============================================\n"
"   SCROLLBAR\n"
"   ============================================= */\n"
"QScrollBar:vertical {\n"
"    background-color: #f0f0f0;\n"
"    width: 10px;\n"
"    border-radiu"
                        "s: 5px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background-color: #c0c0c0;\n"
"    border-radius: 5px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background-color: #ea6f15;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    height: 0;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"    background-color: #f0f0f0;\n"
"    height: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {\n"
"    background-color: #c0c0c0;\n"
"    border-radius: 5px;\n"
"    min-width: 30px;\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal:hover {\n"
"    background-color: #ea6f15;\n"
"}\n"
"\n"
"/* =============================================\n"
"   BARRA DE ESTADO\n"
"   ============================================= */\n"
"QStatusBar {\n"
"    background-color: #f8f8f8;\n"
"    color: #666666;\n"
"    font-size: 11px;\n"
"    padding: 4px 12px;\n"
"    border-top: 2px solid #ea6f15;\n"
"}\n"
"\n"
"/* ========================="
                        "====================\n"
"   TOOLTIPS\n"
"   ============================================= */\n"
"QToolTip {\n"
"    background-color: #ea6f15;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    padding: 6px 10px;\n"
"    border-radius: 4px;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"/* =============================================\n"
"   MESSAGEBOX (Ventanas de mensaje)\n"
"   ============================================= */\n"
"QMessageBox {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"\n"
"QMessageBox QLabel {\n"
"    color: #333333;\n"
"    font-size: 13px;\n"
"}\n"
"\n"
"QMessageBox QPushButton {\n"
"    background-color: #ea6f15;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 4px;\n"
"    padding: 8px 20px;\n"
"    font-size: 12px;\n"
"    font-weight: bold;\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QMessageBox QPushButton:hover {\n"
"    background-color: #f58025;\n"
"}\n"
"\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(8);
        mainLayout->setObjectName("mainLayout");
        mainLayout->setContentsMargins(16, 12, 16, 12);
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(16);
        hboxLayout->setObjectName("hboxLayout");
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setMinimumSize(QSize(60, 60));
        logoLabel->setMaximumSize(QSize(60, 60));
        logoLabel->setScaledContents(true);

        hboxLayout->addWidget(logoLabel);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(2);
        vboxLayout->setObjectName("vboxLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        vboxLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(centralwidget);
        subtitleLabel->setObjectName("subtitleLabel");

        vboxLayout->addWidget(subtitleLabel);


        hboxLayout->addLayout(vboxLayout);

        spacerItem = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);


        mainLayout->addLayout(hboxLayout);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabClientes = new QWidget();
        tabClientes->setObjectName("tabClientes");
        hboxLayout1 = new QHBoxLayout(tabClientes);
        hboxLayout1->setSpacing(12);
        hboxLayout1->setContentsMargins(12, 12, 12, 12);
        hboxLayout1->setObjectName("hboxLayout1");
        splitter = new QSplitter(tabClientes);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        groupClientes = new QGroupBox(splitter);
        groupClientes->setObjectName("groupClientes");
        vboxLayout1 = new QVBoxLayout(groupClientes);
        vboxLayout1->setSpacing(10);
        vboxLayout1->setObjectName("vboxLayout1");
        tablaClientes = new QTableWidget(groupClientes);
        tablaClientes->setObjectName("tablaClientes");
        tablaClientes->setAlternatingRowColors(true);

        vboxLayout1->addWidget(tablaClientes);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(8);
        hboxLayout2->setObjectName("hboxLayout2");
        btnAgregarCliente = new QPushButton(groupClientes);
        btnAgregarCliente->setObjectName("btnAgregarCliente");

        hboxLayout2->addWidget(btnAgregarCliente);

        btnEditarCliente = new QPushButton(groupClientes);
        btnEditarCliente->setObjectName("btnEditarCliente");

        hboxLayout2->addWidget(btnEditarCliente);

        btnHistorialCliente = new QPushButton(groupClientes);
        btnHistorialCliente->setObjectName("btnHistorialCliente");

        hboxLayout2->addWidget(btnHistorialCliente);

        spacerItem1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout2->addItem(spacerItem1);

        btnEliminarCliente = new QPushButton(groupClientes);
        btnEliminarCliente->setObjectName("btnEliminarCliente");

        hboxLayout2->addWidget(btnEliminarCliente);


        vboxLayout1->addLayout(hboxLayout2);

        splitter->addWidget(groupClientes);
        groupVehiculos = new QGroupBox(splitter);
        groupVehiculos->setObjectName("groupVehiculos");
        vboxLayout2 = new QVBoxLayout(groupVehiculos);
        vboxLayout2->setSpacing(10);
        vboxLayout2->setObjectName("vboxLayout2");
        tablaVehiculos = new QTableWidget(groupVehiculos);
        tablaVehiculos->setObjectName("tablaVehiculos");
        tablaVehiculos->setAlternatingRowColors(true);

        vboxLayout2->addWidget(tablaVehiculos);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setSpacing(8);
        hboxLayout3->setObjectName("hboxLayout3");
        btnAgregarAuto = new QPushButton(groupVehiculos);
        btnAgregarAuto->setObjectName("btnAgregarAuto");

        hboxLayout3->addWidget(btnAgregarAuto);

        btnAgregarMoto = new QPushButton(groupVehiculos);
        btnAgregarMoto->setObjectName("btnAgregarMoto");

        hboxLayout3->addWidget(btnAgregarMoto);

        btnAgregarHibrido = new QPushButton(groupVehiculos);
        btnAgregarHibrido->setObjectName("btnAgregarHibrido");

        hboxLayout3->addWidget(btnAgregarHibrido);

        btnHistorialVehiculo = new QPushButton(groupVehiculos);
        btnHistorialVehiculo->setObjectName("btnHistorialVehiculo");

        hboxLayout3->addWidget(btnHistorialVehiculo);

        spacerItem2 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout3->addItem(spacerItem2);

        btnEliminarVehiculo = new QPushButton(groupVehiculos);
        btnEliminarVehiculo->setObjectName("btnEliminarVehiculo");

        hboxLayout3->addWidget(btnEliminarVehiculo);


        vboxLayout2->addLayout(hboxLayout3);

        splitter->addWidget(groupVehiculos);

        hboxLayout1->addWidget(splitter);

        tabWidget->addTab(tabClientes, QString());
        tabOrdenes = new QWidget();
        tabOrdenes->setObjectName("tabOrdenes");
        vboxLayout3 = new QVBoxLayout(tabOrdenes);
        vboxLayout3->setSpacing(12);
        vboxLayout3->setContentsMargins(12, 12, 12, 12);
        vboxLayout3->setObjectName("vboxLayout3");
        groupOrdenes = new QGroupBox(tabOrdenes);
        groupOrdenes->setObjectName("groupOrdenes");
        vboxLayout4 = new QVBoxLayout(groupOrdenes);
        vboxLayout4->setSpacing(10);
        vboxLayout4->setObjectName("vboxLayout4");
        tablaOrdenes = new QTableWidget(groupOrdenes);
        if (tablaOrdenes->columnCount() < 7)
            tablaOrdenes->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablaOrdenes->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablaOrdenes->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablaOrdenes->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablaOrdenes->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablaOrdenes->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tablaOrdenes->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tablaOrdenes->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tablaOrdenes->setObjectName("tablaOrdenes");
        tablaOrdenes->setAlternatingRowColors(true);

        vboxLayout4->addWidget(tablaOrdenes);

        hboxLayout4 = new QHBoxLayout();
        hboxLayout4->setSpacing(8);
        hboxLayout4->setObjectName("hboxLayout4");
        btnNuevaOrden = new QPushButton(groupOrdenes);
        btnNuevaOrden->setObjectName("btnNuevaOrden");

        hboxLayout4->addWidget(btnNuevaOrden);

        btnEditarOrden = new QPushButton(groupOrdenes);
        btnEditarOrden->setObjectName("btnEditarOrden");

        hboxLayout4->addWidget(btnEditarOrden);

        btnCambiarEstado = new QPushButton(groupOrdenes);
        btnCambiarEstado->setObjectName("btnCambiarEstado");

        hboxLayout4->addWidget(btnCambiarEstado);

        spacerItem3 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout4->addItem(spacerItem3);


        vboxLayout4->addLayout(hboxLayout4);


        vboxLayout3->addWidget(groupOrdenes);

        tabWidget->addTab(tabOrdenes, QString());
        tabInventario = new QWidget();
        tabInventario->setObjectName("tabInventario");
        vboxLayout5 = new QVBoxLayout(tabInventario);
        vboxLayout5->setSpacing(12);
        vboxLayout5->setContentsMargins(12, 12, 12, 12);
        vboxLayout5->setObjectName("vboxLayout5");
        groupInventario = new QGroupBox(tabInventario);
        groupInventario->setObjectName("groupInventario");
        vboxLayout6 = new QVBoxLayout(groupInventario);
        vboxLayout6->setSpacing(10);
        vboxLayout6->setObjectName("vboxLayout6");
        tablaInventario = new QTableWidget(groupInventario);
        if (tablaInventario->columnCount() < 6)
            tablaInventario->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tablaInventario->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tablaInventario->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tablaInventario->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tablaInventario->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tablaInventario->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tablaInventario->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        tablaInventario->setObjectName("tablaInventario");
        tablaInventario->setAlternatingRowColors(true);

        vboxLayout6->addWidget(tablaInventario);

        hboxLayout5 = new QHBoxLayout();
        hboxLayout5->setSpacing(8);
        hboxLayout5->setObjectName("hboxLayout5");
        btnNuevoRepuesto = new QPushButton(groupInventario);
        btnNuevoRepuesto->setObjectName("btnNuevoRepuesto");

        hboxLayout5->addWidget(btnNuevoRepuesto);

        btnEditarRepuesto = new QPushButton(groupInventario);
        btnEditarRepuesto->setObjectName("btnEditarRepuesto");

        hboxLayout5->addWidget(btnEditarRepuesto);

        btnAjustarStock = new QPushButton(groupInventario);
        btnAjustarStock->setObjectName("btnAjustarStock");

        hboxLayout5->addWidget(btnAjustarStock);

        spacerItem4 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout5->addItem(spacerItem4);

        btnEliminarRepuesto = new QPushButton(groupInventario);
        btnEliminarRepuesto->setObjectName("btnEliminarRepuesto");

        hboxLayout5->addWidget(btnEliminarRepuesto);


        vboxLayout6->addLayout(hboxLayout5);


        vboxLayout5->addWidget(groupInventario);

        tabWidget->addTab(tabInventario, QString());
        tabAgenda = new QWidget();
        tabAgenda->setObjectName("tabAgenda");
        hboxLayout6 = new QHBoxLayout(tabAgenda);
        hboxLayout6->setSpacing(12);
        hboxLayout6->setContentsMargins(12, 12, 12, 12);
        hboxLayout6->setObjectName("hboxLayout6");
        groupCalendario = new QGroupBox(tabAgenda);
        groupCalendario->setObjectName("groupCalendario");
        groupCalendario->setMinimumWidth(360);
        groupCalendario->setMaximumWidth(400);
        vboxLayout7 = new QVBoxLayout(groupCalendario);
        vboxLayout7->setObjectName("vboxLayout7");
        calendario = new QCalendarWidget(groupCalendario);
        calendario->setObjectName("calendario");
        calendario->setGridVisible(true);

        vboxLayout7->addWidget(calendario);


        hboxLayout6->addWidget(groupCalendario);

        groupCitas = new QGroupBox(tabAgenda);
        groupCitas->setObjectName("groupCitas");
        vboxLayout8 = new QVBoxLayout(groupCitas);
        vboxLayout8->setSpacing(10);
        vboxLayout8->setObjectName("vboxLayout8");
        listaCitas = new QListWidget(groupCitas);
        listaCitas->setObjectName("listaCitas");

        vboxLayout8->addWidget(listaCitas);

        hboxLayout7 = new QHBoxLayout();
        hboxLayout7->setSpacing(8);
        hboxLayout7->setObjectName("hboxLayout7");
        btnNuevaCita = new QPushButton(groupCitas);
        btnNuevaCita->setObjectName("btnNuevaCita");

        hboxLayout7->addWidget(btnNuevaCita);

        btnEditarCita = new QPushButton(groupCitas);
        btnEditarCita->setObjectName("btnEditarCita");

        hboxLayout7->addWidget(btnEditarCita);

        spacerItem5 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout7->addItem(spacerItem5);

        btnEliminarCita = new QPushButton(groupCitas);
        btnEliminarCita->setObjectName("btnEliminarCita");

        hboxLayout7->addWidget(btnEliminarCita);


        vboxLayout8->addLayout(hboxLayout7);


        hboxLayout6->addWidget(groupCitas);

        tabWidget->addTab(tabAgenda, QString());
        tabFacturacion = new QWidget();
        tabFacturacion->setObjectName("tabFacturacion");
        vboxLayout9 = new QVBoxLayout(tabFacturacion);
        vboxLayout9->setSpacing(12);
        vboxLayout9->setContentsMargins(12, 12, 12, 12);
        vboxLayout9->setObjectName("vboxLayout9");
        groupFacturas = new QGroupBox(tabFacturacion);
        groupFacturas->setObjectName("groupFacturas");
        vboxLayout10 = new QVBoxLayout(groupFacturas);
        vboxLayout10->setSpacing(10);
        vboxLayout10->setObjectName("vboxLayout10");
        tablaFacturas = new QTableWidget(groupFacturas);
        if (tablaFacturas->columnCount() < 5)
            tablaFacturas->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tablaFacturas->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tablaFacturas->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tablaFacturas->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tablaFacturas->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tablaFacturas->setHorizontalHeaderItem(4, __qtablewidgetitem17);
        tablaFacturas->setObjectName("tablaFacturas");
        tablaFacturas->setAlternatingRowColors(true);

        vboxLayout10->addWidget(tablaFacturas);

        hboxLayout8 = new QHBoxLayout();
        hboxLayout8->setSpacing(8);
        hboxLayout8->setObjectName("hboxLayout8");
        btnNuevaFactura = new QPushButton(groupFacturas);
        btnNuevaFactura->setObjectName("btnNuevaFactura");

        hboxLayout8->addWidget(btnNuevaFactura);

        btnNuevoPresupuesto = new QPushButton(groupFacturas);
        btnNuevoPresupuesto->setObjectName("btnNuevoPresupuesto");

        hboxLayout8->addWidget(btnNuevoPresupuesto);

        btnRegistrarPago = new QPushButton(groupFacturas);
        btnRegistrarPago->setObjectName("btnRegistrarPago");

        hboxLayout8->addWidget(btnRegistrarPago);

        btnVerDetalle = new QPushButton(groupFacturas);
        btnVerDetalle->setObjectName("btnVerDetalle");

        hboxLayout8->addWidget(btnVerDetalle);

        btnAnularFactura = new QPushButton(groupFacturas);
        btnAnularFactura->setObjectName("btnAnularFactura");

        hboxLayout8->addWidget(btnAnularFactura);

        btnConvertirFactura = new QPushButton(groupFacturas);
        btnConvertirFactura->setObjectName("btnConvertirFactura");

        hboxLayout8->addWidget(btnConvertirFactura);

        spacerItem6 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout8->addItem(spacerItem6);


        vboxLayout10->addLayout(hboxLayout8);


        vboxLayout9->addWidget(groupFacturas);

        tabWidget->addTab(tabFacturacion, QString());

        mainLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Taller Mec\303\241nico - Sistema de Gesti\303\263n", nullptr));
        logoLabel->setText(QString());
        titleLabel->setText(QCoreApplication::translate("MainWindow", "TALLER SAN JAUN", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("MainWindow", "Sistema de Gesti\303\263n Integral - Clientes, Veh\303\255culos, \303\223rdenes de Trabajo e Inventario", nullptr));
        groupClientes->setTitle(QCoreApplication::translate("MainWindow", "REGISTRO DE CLIENTES", nullptr));
        btnAgregarCliente->setText(QCoreApplication::translate("MainWindow", "+ NUEVO CLIENTE", nullptr));
        btnEditarCliente->setText(QCoreApplication::translate("MainWindow", "EDITAR", nullptr));
        btnHistorialCliente->setText(QCoreApplication::translate("MainWindow", "HISTORIAL", nullptr));
        btnEliminarCliente->setText(QCoreApplication::translate("MainWindow", "ELIMINAR", nullptr));
        groupVehiculos->setTitle(QCoreApplication::translate("MainWindow", "VEH\303\215CULOS DEL CLIENTE SELECCIONADO", nullptr));
        btnAgregarAuto->setText(QCoreApplication::translate("MainWindow", "AGREGAR AUTO", nullptr));
        btnAgregarMoto->setText(QCoreApplication::translate("MainWindow", "AGREGAR MOTO", nullptr));
        btnAgregarHibrido->setText(QCoreApplication::translate("MainWindow", "H\303\215BRIDO", nullptr));
        btnHistorialVehiculo->setText(QCoreApplication::translate("MainWindow", "HISTORIAL", nullptr));
        btnEliminarVehiculo->setText(QCoreApplication::translate("MainWindow", "ELIMINAR", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabClientes), QCoreApplication::translate("MainWindow", "CLIENTES", nullptr));
        groupOrdenes->setTitle(QCoreApplication::translate("MainWindow", "\303\223RDENES DE TRABAJO ACTIVAS", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablaOrdenes->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablaOrdenes->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "N\302\260 ORDEN", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablaOrdenes->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "CLIENTE", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablaOrdenes->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "VEH\303\215CULO", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tablaOrdenes->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "ESTADO", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tablaOrdenes->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "FECHA INGRESO", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tablaOrdenes->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "COSTO ESTIMADO", nullptr));
        btnNuevaOrden->setText(QCoreApplication::translate("MainWindow", "NUEVA ORDEN", nullptr));
        btnEditarOrden->setText(QCoreApplication::translate("MainWindow", "EDITAR ORDEN", nullptr));
        btnCambiarEstado->setText(QCoreApplication::translate("MainWindow", "CAMBIAR ESTADO", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabOrdenes), QCoreApplication::translate("MainWindow", "\303\223RDENES DE TRABAJO", nullptr));
        groupInventario->setTitle(QCoreApplication::translate("MainWindow", "INVENTARIO DE REPUESTOS Y PRODUCTOS", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tablaInventario->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tablaInventario->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "C\303\223DIGO", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tablaInventario->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "PRODUCTO", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tablaInventario->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "CATEGOR\303\215A", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tablaInventario->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "STOCK", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tablaInventario->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "PRECIO", nullptr));
        btnNuevoRepuesto->setText(QCoreApplication::translate("MainWindow", "+ AGREGAR PRODUCTO", nullptr));
        btnEditarRepuesto->setText(QCoreApplication::translate("MainWindow", "EDITAR", nullptr));
        btnAjustarStock->setText(QCoreApplication::translate("MainWindow", "AJUSTAR STOCK", nullptr));
        btnEliminarRepuesto->setText(QCoreApplication::translate("MainWindow", "ELIMINAR", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabInventario), QCoreApplication::translate("MainWindow", "INVENTARIO", nullptr));
        groupCalendario->setTitle(QCoreApplication::translate("MainWindow", "CALENDARIO DE CITAS", nullptr));
        groupCitas->setTitle(QCoreApplication::translate("MainWindow", "CITAS DEL D\303\215A SELECCIONADO", nullptr));
        btnNuevaCita->setText(QCoreApplication::translate("MainWindow", "+ NUEVA CITA", nullptr));
        btnEditarCita->setText(QCoreApplication::translate("MainWindow", "EDITAR", nullptr));
        btnEliminarCita->setText(QCoreApplication::translate("MainWindow", "CANCELAR CITA", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabAgenda), QCoreApplication::translate("MainWindow", "AGENDA", nullptr));
        groupFacturas->setTitle(QCoreApplication::translate("MainWindow", "FACTURAS Y DOCUMENTOS", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tablaFacturas->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tablaFacturas->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "N\302\260 DOCUMENTO", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tablaFacturas->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "FECHA", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tablaFacturas->horizontalHeaderItem(3);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "MONTO", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tablaFacturas->horizontalHeaderItem(4);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "ESTADO", nullptr));
        btnNuevaFactura->setText(QCoreApplication::translate("MainWindow", "+ NUEVA FACTURA", nullptr));
        btnNuevoPresupuesto->setText(QCoreApplication::translate("MainWindow", "+ PRESUPUESTO", nullptr));
        btnNuevoPresupuesto->setStyleSheet(QCoreApplication::translate("MainWindow", "background-color: #0284c7; color: #fff;", nullptr));
        btnRegistrarPago->setText(QCoreApplication::translate("MainWindow", "REGISTRAR PAGO", nullptr));
        btnVerDetalle->setText(QCoreApplication::translate("MainWindow", "VER DETALLE", nullptr));
        btnAnularFactura->setText(QCoreApplication::translate("MainWindow", "ANULAR FACTURA", nullptr));
        btnConvertirFactura->setText(QCoreApplication::translate("MainWindow", "CONVERTIR A FACTURA", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabFacturacion), QCoreApplication::translate("MainWindow", "FACTURACI\303\223N", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
