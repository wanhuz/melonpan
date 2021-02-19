#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qstandarditemmodel.h>
#include "../dict/dict.h"
#include "../capturekey/captureEvent.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private slots:
    void alwaysOnTop(bool enabled);
    void startCapture(bool enable);

public slots:
    void search();

private:
    captureEvent* captureevent;
    Dict dict;
    QPushButton* OCRBtn;
    Ui::MainWindow ui;
    QLineEdit* textbox;
    QTableView* table;
    QStandardItemModel dictmodel;
};
