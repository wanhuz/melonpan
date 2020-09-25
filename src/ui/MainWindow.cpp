#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    textbox = ui.lineEdit;

}

void MainWindow::displayOCRresult(QString result)
{
    textbox->setText(result);
}
