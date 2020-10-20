#include <QtWidgets/QApplication>
#include "ui/MainWindow.h"
#include "dict/dict.h"



int main(int argc, char *argv[])
{
    //Dict dict;
    //dict.load();
    QApplication a(argc, argv);
    MainWindow m;
    m.show();
    return a.exec();
}
