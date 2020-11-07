#include "dict.h"
#include <qstandarditemmodel.h>
#include <QtCore\qfile.h>
#include <QDebug>
#include <qstring.h>
#include <QBuffer>
#include <qeventloop.h>

Dict::Dict() {
 /*   dictmodel = new QStandardItemModel(185000,3);
    QStringList labels;
    labels.insert(0, QString("Kanji"));
    labels.insert(1, QString("Kana"));
    labels.insert(2, QString("Meaning"));
    dictmodel->setHorizontalHeaderLabels(labels);*/
    QStringList meaning_list;
    QStringList kanji_list;
    QStringList reading_list;
    dictlist.append(kanji_list);
    dictlist.append(reading_list);
    dictlist.append(meaning_list);
    

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


    //This code below takes ~40 seconds without threading
    while (!out.atEnd()) {
        line = out.readLine(); 

        if (line.contains("<keb>")) {
            line.remove(QRegExp("<...>|<\/...>"));
            kanji = line;
        }
        else if (line.contains("<gloss>")) {
            line.remove(QRegExp("<.....>"));
            line.replace("</gloss>", "; ");
            meanings = meanings + line;
        }
        else if (line.contains("<reb>")) {
            line.remove(QRegExp("<...>|<\/...>"));
            readings = readings + line;
        }
        else if (line.contains("</entry>")) {
            //Memory allocation here is high, but this is not why it takes long to load
            dictlist[1].append(readings);
            dictlist[0].append(kanji);
            dictlist[2].append(meanings);
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

QStringList Dict::search(QString searchString) {
    QStringList searchResult = dictlist[0].filter(searchString);
    
    return searchResult;
}