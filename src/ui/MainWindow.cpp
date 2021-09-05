#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qmainwindow.h>
#include <qtextcodec.h>
#include <Windows.h>
#include <qaction.h>
#include <qdebug.h>
#include <qevent.h>
#include <qfontdatabase.h>
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
#include "../settings/config.h"
#include "../ui/SettingsWindow.h";
#include "../data/entry.h"
#include "../util/util.h"
#include "../ui/popup.h"
#include "../settings/mecabKey.h"
#include "../capturekey/maincontroller.h"



MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    OCRBtn = ui.ocrBtn;
    textBtn = ui.textBtn;
    minBtn = ui.minBtn;
    textbox = ui.textLine;
    table = ui.dictView;
    sansMonoJK = NULL;

    QAction* fsSmall = ui.fs_small;
    QAction* fsNormal = ui.fs_normal;
    QAction* fsLarge = ui.fs_large;
    QAction * fsvLarge = ui.fs_verylarge;
    QAction* frameVert = ui.actionVertical;
    QAction* frameHort = ui.actionHorizontal;
    QAction* settingsWindow = ui.Settings;

    //Mecab library need to set registry in Regedit so that the library can load dictionary globally, Exit if registry fail to set
    MeCabKey key; 
    if (!(key.init())) {
        QMessageBox err;
        err.setText("Failed to set registry key for MeCab");
        err.setIcon(QMessageBox::Critical);
        err.exec();
        exit(2);
    }

    //This is not supposed to be at this class because it breaks MVC architecture, but it is easier than refactoring everything
    MainControl = new MainController();

    QString fontPath = QDir::currentPath();
    fontPath = "C:\\Users\\WanHuz\\Documents\\Shanachan\\res\\font\\NotoSansMonoCJKjp-Regular.otf"; //For debugging purpose
    //fontPath = fontPath + "/res/font/NotoSansMonoCJKjp-Regular.otf";
    int id = QFontDatabase::addApplicationFont(fontPath);
    
    if (id < 0) {
        QMessageBox err;
        err.setText("Failed to load Sans Mono JK font at " + fontPath);
        err.setIcon(QMessageBox::Warning);
        err.exec();
    }
    else {
        QString NotoJK = QFontDatabase::applicationFontFamilies(id).at(0);
        sansMonoJK = new QFont(NotoJK, 12);
        textbox->setFont(QFont(NotoJK, 22)); //default to Calibri if failed
    }


    //UI customization
    this->refreshTable();
    
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OCRBtn->setCheckable(true);
    textBtn->setCheckable(true);
    table->verticalHeader()->setVisible(false);
    table->setModel(&dictmodel);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //Set system tray icon
    QIcon TrayIconPath = QIcon("C:\\Users\\WanHuz\\Documents\\Shanachan\\res\\ui\\melonpan.ico");
    trayIcon = new QSystemTrayIcon(TrayIconPath, this);
    QMenu* traymenu = new QMenu(this);
    QAction* exit = new QAction("Exit");
    traymenu->addAction(exit);
    trayIcon->setContextMenu(traymenu);
    trayIcon->setVisible(true);

    //Connect menu bar button, this is redundant, may change it later
    connect(fsSmall, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(10);
        });
    connect(fsNormal, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(12);
        });
    connect(fsLarge, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(24);
        });
    connect(fsvLarge, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(48);
        });
    connect(frameVert, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameOrientation(Frame::Vertical);
        });
    connect(frameHort, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameOrientation(Frame::Horizontal);
        });
    connect(settingsWindow, &QAction::triggered, this, [=]() {
            SettingsWindow* settings = new SettingsWindow();;
            settings->show();
        });


    connect(MainControl, SIGNAL(captureResult(QString)), textbox, SLOT(setText(QString)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureOCR(bool)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(alwaysOnTop(bool)));
    connect(textBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureText(bool)));
    connect(textBtn, SIGNAL(toggled(bool)), this, SLOT(alwaysOnTop(bool)));
    connect(minBtn, &QPushButton::toggled, this, [=](const bool tempbool) {minMode = tempbool;});
    connect(textbox, SIGNAL(textChanged(QString)), this, SLOT(search()));
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
    connect(exit, &QAction::triggered, this, &QApplication::quit);
}

//Search from user-given string and display it either in normal mode or minimal mode, result are limited to 100 entry.
void MainWindow::search() {
    QVector<entry> searchResult;
    QString searchText;

    dictmodel.clear();
    searchText = textbox->text();

    if (searchText.isEmpty()) { 
        this->refreshTable();
        return; 
    }

    searchResult = MainControl->searchDict(searchText);

    if (searchResult.size() < 1) {
        dictmodel.clear();
    }
    else if (searchResult.size() > 0) {
        int size;

        /*Limit search result to 100 entries only. Also improve responsiveness*/
        if (searchResult.size() > 100) { size = 100; }
        else { size = searchResult.size(); }

        for (int i = 0; i < size; i++) {
            dictmodel.setItem(i, 0, new QStandardItem(searchResult[i].getKanji().toLocal8Bit().constData()));
            dictmodel.setItem(i, 1, new QStandardItem(searchResult[i].getReading().toLocal8Bit().constData()));
            dictmodel.setItem(i, 2, new QStandardItem(searchResult[i].getGloss().toLocal8Bit().constData()));
        }

        //If font is found, set the font to Sans Mono JK
        if (sansMonoJK != NULL) {
            for (int i = 0; i < dictmodel.rowCount(); i++) {
                dictmodel.item(i, 0)->setFont(*sansMonoJK);
                dictmodel.item(i, 1)->setFont(*sansMonoJK);
            }
        }

        //Spawn minimalist UI if enabled
        if (minMode) {
            if(minUi == NULL) { 
                minUi = new popup(this); }

            minUi->clearEntry();

            for (int i = 0; i < 5; i++) {
                if (i > searchResult.size()-1) break;
                minUi->addEntry(searchResult.at(i));
            }

            minUi->shows();
        }

    }

    //Refresh UI
    this->refreshTable();
}

void MainWindow::startCaptureOCR(bool enableOCR) {
    if (!enableOCR) { 
        MainControl->stopCaptureKey(); }
    else { 
        MainControl->startCaptureKeyOCR(); }

}

void MainWindow::startCaptureText(bool enableText){
    if (!enableText) { 
        MainControl->stopCaptureKey(); }
    else { 
        MainControl->startCaptureKeyTextGeneric(); }
}

void MainWindow::alwaysOnTop(bool enabled) {
    this->showNormal();
    HWND hwnd = (HWND)this->winId();

    if (enabled) {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }
    else {
        SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    }

}

//Activate window if icon in system tray is clicked
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        show();
        this->setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
        this->activateWindow();
    }
    
}

//Minimize windows to tray
void MainWindow::changeEvent(QEvent* event) {
    if (event->type() == QEvent::WindowStateChange) {
        if (isMinimized()) {
            hide();
            event->ignore();
        }
    }

    return QMainWindow::changeEvent(event);
}

//Set label for table column
void MainWindow::refreshTable() {
    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel.setHorizontalHeaderLabels(labels);
}