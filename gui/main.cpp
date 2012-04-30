#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString init(argv[1]);
    w.setInitialEq(init);
    w.show();
    
    return a.exec();
}
