#include "dict.h"
#include <qstandarditemmodel.h>
#include <QtCore\qfile.h>
#include <QDebug>
#include <qstring.h>
#include <QBuffer>

Dict::Dict() {
    dictmodel = new QStandardItemModel(2500,3);
    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel->setHorizontalHeaderLabels(labels);
}

/*Load file into qstandarditemmodel*/
void Dict::load() {
	QFile dictFile("../res/JMdict_e");
    if (!dictFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray data = dictFile.readAll();

    this->parse(&data);


}

void Dict::parse(QByteArray* data) {
    QBuffer buffer(data);
    buffer.open(QIODevice::ReadOnly);
    QTextStream out(&buffer);
    out.setCodec("UTF-8");
    int rowCount = 0;

    QString meanings = "";
    QString kanji;
    QString readings = "";
    QString line;

    while (!out.atEnd()) {
        line = out.readLine();

        if (line.contains("<keb>")) {
            kanji = line;
        }
        else if (line.contains("<gloss>")) {
            meanings = meanings + line;
        }
        else if (line.contains("<reb>")) {
            readings = readings + line;
        }
        else if (line.contains("</entry>")) {
            dictmodel->setItem(rowCount, 0, new QStandardItem(kanji));
            dictmodel->setItem(rowCount, 1, new QStandardItem(readings));
            dictmodel->setItem(rowCount, 2, new QStandardItem(meanings));
            rowCount++;
            meanings = "";
            kanji = "";
            readings = "";
        }
        
    }
}

QStandardItemModel* Dict::getModel() {
    return dictmodel;
}