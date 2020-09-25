#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);
    void displayOCRresult(QString result);

private:
    Ui::MainWindow ui;
    QLineEdit* textbox;
};
