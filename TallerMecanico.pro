QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = TallerMecanico
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    database/databasemanager.cpp \
    models/motor.cpp \
    models/vehiculo.cpp \
    models/auto.cpp \
    models/moto.cpp \
    models/autohibrido.cpp \
    models/cliente.cpp \
    models/repuesto.cpp \
    models/ordentrabajo.cpp \
    models/documento.cpp \
    models/citaagenda.cpp \
    models/historialservicio.cpp \
    dialogs/clientedialog.cpp \
    dialogs/vehiculodialog.cpp \
    dialogs/repuestodialog.cpp \
    dialogs/ordentrabajodialog.cpp \
    dialogs/citadialog.cpp \
    dialogs/facturadialog.cpp \
    dialogs/presupuestodialog.cpp

HEADERS += \
    mainwindow.h \
    database/databasemanager.h \
    models/motor.h \
    models/vehiculo.h \
    models/auto.h \
    models/moto.h \
    models/autohibrido.h \
    models/cliente.h \
    models/repuesto.h \
    models/ordentrabajo.h \
    models/documento.h \
    models/citaagenda.h \
    models/historialservicio.h \
    dialogs/clientedialog.h \
    dialogs/vehiculodialog.h \
    dialogs/repuestodialog.h \
    dialogs/ordentrabajodialog.h \
    dialogs/citadialog.h \
    dialogs/facturadialog.h \
    dialogs/presupuestodialog.h

FORMS += \
    mainwindow.ui \
    dialogs/clientedialog.ui \
    dialogs/vehiculodialog.ui

# Recursos (logo e imágenes)
RESOURCES += resources.qrc

# Icono de la aplicación (Windows)
RC_ICONS = images/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




