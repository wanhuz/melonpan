#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "frame.h"
#include "../ocr/ocr.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void hideFrame();

private:
    Frame* frame;
    QPushButton* OCRBtn;
    Ui::MainWindow ui;
    QLineEdit* textbox;
    QTableView* table;
    Ocr* ocr;
};
