#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "frame.h"
#include "../ocr/ocr.h"
#include <qstandarditemmodel.h>
#include "../dict/dict.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void hideFrame(bool enabled);
    void alwaysOnTop(bool enabled);

public slots:
    void search();

private:
    Dict dict;
    Frame* frame;
    QPushButton* OCRBtn;
    Ui::MainWindow ui;
    QLineEdit* textbox;
    QTableView* table;
    Ocr* ocr;
    QString string;
    QStandardItemModel dictmodel;
};
