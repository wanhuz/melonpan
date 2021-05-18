#include "MainWindow.h"
#include <QtWidgets/qlineedit.h>
#include <qstandarditemmodel.h>
#include <qmainwindow.h>
#include <qtextcodec.h>
#include <Windows.h>
#include "../capturekey/maincontroller.h"
#include <qaction.h>
#include <qdebug.h>
#include "../settings/config.h"
#include "../ui/SettingsWindow.h";
#include <qfontdatabase.h>
#include <qdir.h>
#include <qfile.h>
#include <qmessagebox.h>
#include "../data/entry.h"
#include "../util/util.h"
#include "../ui/popup.h"


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

    //This is not supposed to be at this class, but it is easier than refactoring everything
    MainControl = new MainController();

    QString fontPath = QDir::currentPath();
    fontPath = "C:\\Users\\WanHuz\\Documents\\Shanachan\\res\\NotoSansMonoCJKjp-Regular.otf"; //For debugging purpose
    //fontPath = fontPath + "//res//NotoSansMonoCJKjp-Regular.otf";
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
    }


    //UI customization
    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel.setHorizontalHeaderLabels(labels);
    
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OCRBtn->setCheckable(true);
    textBtn->setCheckable(true);
    table->verticalHeader()->setVisible(false);
    table->setModel(&dictmodel);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //Connect menu bar button, this is redundant, may change it later
    connect(fsSmall, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(15);
        });
    connect(fsNormal, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(30);
        });
    connect(fsLarge, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(45);
        });
    connect(fsvLarge, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameSize(60);
        });
    connect(frameVert, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameOrientation(true);
        });
    connect(frameHort, &QAction::triggered, this, [=]() {
            Config::getInstance().setFrameOrientation(false);
        });
    connect(settingsWindow, &QAction::triggered, this, [=]() {
            SettingsWindow* settings = new SettingsWindow();;
            settings->show();
        });


    //Connect buttons to respective function
    connect(MainControl, SIGNAL(OcrResult(QString)), textbox, SLOT(setText(QString)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureOCR(bool)));
    connect(OCRBtn, SIGNAL(toggled(bool)), this, SLOT(alwaysOnTop(bool)));
    connect(textBtn, SIGNAL(toggled(bool)), this, SLOT(startCaptureText(bool)));
    connect(textBtn, SIGNAL(toggled(bool)), this, SLOT(alwaysOnTop(bool)));
    connect(minBtn, &QPushButton::toggled, this, [=](const bool tempbool) {minMode = tempbool;});
    connect(textbox, SIGNAL(textChanged(QString)), this, SLOT(search()));
}

//Search from user-given string and display it either in normal mode or minimal mode, result are limited to 100 entry.
void MainWindow::search() {
    dictmodel.clear();
    QString searchText = textbox->text();
    QString stemmedText = Util::getWordStem(searchText);

    if (searchText.isEmpty()) { 
        QStringList labels;
        labels.insert(0, QString("Kanji"));
        labels.insert(1, QString("Kana"));
        labels.insert(2, QString("Meaning"));
        dictmodel.setHorizontalHeaderLabels(labels);
        return; 
    }

    QVector<entry> searchResult = MainControl->searchDict(searchText);
    if (searchResult.size() < 1) {
       //No result found
        dictmodel.clear();
    }
    else if (searchResult.size() > 0) {
        int size;

        /*Limit search result to 100 entries only. Also, improve responsiveness*/
        if (searchResult.size() > 100) {
            size = 100;
        }
        else {
            size = searchResult.size();
        }

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

        //Spawn minimalism mode if enabled
        if (minMode) {
            if(minUi == NULL) { minUi = new popup(this); }

            minUi->clearEntry();

            for (int i = 0; i < 5; i++) {
                if (i > searchResult.size()-1) break;
                minUi->addEntry(searchResult.at(i));
            }

            minUi->shows();
        }

    }

    //Refresh UI
    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel.setHorizontalHeaderLabels(labels);

}

void MainWindow::startCaptureOCR(bool enableOCR) {
    if (!enableOCR) {
        MainControl->stopCaptureKey();
    }
    else {
        MainControl->startCaptureKeyOCR();
    }
    
}

void MainWindow::startCaptureText(bool enableText){
    if (!enableText) {
        MainControl->stopCaptureKey();
    }
    else {
        MainControl->startCaptureKeyTextGeneric();
    }
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
