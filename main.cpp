#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Configurar información de la aplicación
    app.setApplicationName("Sistema Taller Mecánico");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Taller POO");

    // Crear y mostrar ventana principal
    MainWindow window;
    window.show();

    return app.exec();
}







