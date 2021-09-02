#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qstandarditemmodel.h>
#include "../capturekey/maincontroller.h"
#include "../ui/popup.h"
#include <QSystemTrayIcon>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR);

private slots:
    void alwaysOnTop(bool enabled);
    void startCaptureOCR(bool enable);
    void startCaptureText(bool enable);

public slots:
    void search();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    popup* minUi = NULL;
    QFont* sansMonoJK;
    MainController* MainControl;

    QPushButton* OCRBtn;
    QPushButton* textBtn;
    QPushButton* minBtn;

    Ui::MainWindow ui;

    QLineEdit* textbox;
    QTableView* table;
    QStandardItemModel dictmodel;

    bool minMode = false;

    QSystemTrayIcon* trayIcon;
    void changeEvent(QEvent* event);
};
