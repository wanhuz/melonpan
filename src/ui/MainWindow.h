#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "frame.h"
#include "../ocr/ocr.h"
#include <qstandarditemmodel.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void hideFrame();

public slots:
    void search();

private:
    Frame* frame;
    QPushButton* OCRBtn;
    Ui::MainWindow ui;
    QLineEdit* textbox;
    QTableView* table;
    Ocr* ocr;
    QString string;
    QStandardItemModel* dictmodel;
};
