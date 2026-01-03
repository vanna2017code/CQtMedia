
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("CQtMedia");
    QApplication::setOrganizationName("YourOrg");
    QApplication::setOrganizationDomain("example.org");

    MainWindow w;
    w.resize(1000, 650);
    w.show();
    return app.exec();
}
