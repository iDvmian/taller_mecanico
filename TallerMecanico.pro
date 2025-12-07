QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = TallerMecanico
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    database/databasemanager.cpp \
    clases/motor.cpp \
    clases/vehiculo.cpp \
    clases/auto.cpp \
    clases/moto.cpp \
    clases/autohibrido.cpp \
    clases/cliente.cpp \
    clases/repuesto.cpp \
    clases/ordentrabajo.cpp \
    clases/documento.cpp \
    clases/citaagenda.cpp \
    clases/historialservicio.cpp \
    ventanas/clientedialog.cpp \
    ventanas/vehiculodialog.cpp \
    ventanas/repuestodialog.cpp \
    ventanas/ordentrabajodialog.cpp \
    ventanas/citadialog.cpp \
    ventanas/facturadialog.cpp \
    ventanas/presupuestodialog.cpp

HEADERS += \
    mainwindow.h \
    database/databasemanager.h \
    clases/motor.h \
    clases/vehiculo.h \
    clases/auto.h \
    clases/moto.h \
    clases/autohibrido.h \
    clases/cliente.h \
    clases/repuesto.h \
    clases/ordentrabajo.h \
    clases/documento.h \
    clases/citaagenda.h \
    clases/historialservicio.h \
    ventanas/clientedialog.h \
    ventanas/vehiculodialog.h \
    ventanas/repuestodialog.h \
    ventanas/ordentrabajodialog.h \
    ventanas/citadialog.h \
    ventanas/facturadialog.h \
    ventanas/presupuestodialog.h

FORMS += \
    mainwindow.ui \
    ventanas/clientedialog.ui \
    ventanas/vehiculodialog.ui

# Recursos (logo e imágenes)
RESOURCES += resources.qrc

# Icono de la aplicación (Windows)
RC_ICONS = imagenes/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




