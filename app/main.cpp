#include "MainWindow.h"

#include <QApplication>

// 主色调： 19 132 255
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    return a.exec();
}
