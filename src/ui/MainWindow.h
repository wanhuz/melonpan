#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qstandarditemmodel.h>
#include <QSystemTrayIcon>
#include "../capturekey/maincontroller.h"
#include "../ui/popup.h"




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
    bool minMode = false;
    Ui::MainWindow ui;

    popup* minUi = NULL;
    QFont* sansMonoJK;
    MainController* MainControl;
    QPushButton* OCRBtn;
    QPushButton* textBtn;
    QPushButton* minBtn;
    QLineEdit* textbox;
    QTableView* table;
    QStandardItemModel dictmodel;
    QSystemTrayIcon* trayIcon;

    void changeEvent(QEvent* event);
    void refreshTable();
};
