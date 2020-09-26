#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qstring.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    textbox = ui.lineEdit;
    table = ui.tableView;
    dockw = ui.dockWidget;
    QStandardItemModel* model = new QStandardItemModel(14,2);

    
    for (int row = 0; row < model->rowCount(); ++row) {
        for (int column = 0; column < model->columnCount(); ++column) {
            QStandardItem* item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
            model->setItem(row, column, item);
        }
    }
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->resizeDocks({dockw}, { 300 }, Qt::Vertical);
    
    


}

void MainWindow::displayOCRresult(QString result)
{
    textbox->setText(result);
}
