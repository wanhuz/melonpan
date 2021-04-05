#include "dict.h"
#include <qstandarditemmodel.h>
#include <QtCore\qfile.h>
#include <QDebug>
#include <qstring.h>
#include <QBuffer>
#include <qeventloop.h>
#include <qdir.h>

Dict::Dict() {
    QStringList meaning_list;
    QStringList kanji_list;
    QStringList reading_list;
    dictlist.append(kanji_list);
    dictlist.append(reading_list);
    dictlist.append(meaning_list);
}

/*Load file into QList*/
void Dict::load() {
    QString dictPath = QDir::currentPath();
    //dictPath = dictPath + "/res/JMdict_e";
    dictPath = "C://Users//WanHuz//Documents//Shanachan//res//JMdict_e"; //Debug Mode
    QFile dictFile(dictPath);
    if (!dictFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open dictionary file " + dictPath;
        return;
    }

    QByteArray data = dictFile.readAll();
    this->parse(&data);

}

void Dict::parse(QByteArray* data) {
    QBuffer buffer(data);
    buffer.open(QIODevice::ReadOnly);
    QTextStream out(&buffer);
    out.setCodec("UTF-8");
    int rowCount = 0;

    const QString clrTxt = "";
    QString meanings = clrTxt;
    QString kanji;
    QString readings = clrTxt;
    QString line;
    

    //This code below takes ~15s using different threads; ~40s without thread
    while (!out.atEnd()) {
        line = out.readLine(); 

        if (line.startsWith("<keb>")) {
            line.remove(0,5);
            line.remove("</keb>");
            kanji = line;
        }
        else if (line.startsWith("<gloss>")) {
            line.remove(0, 7);
            line.remove("</gloss>");
            line = line + ";";
            meanings = meanings + line;
        }
        else if (line.startsWith("<reb>")) {
            line.remove(0, 5);
            line.remove("</reb>");
            readings = readings + line + "\n";
        }
        else if (line.startsWith("</ent")) {
            //Memory allocation here is 130MB~ give or take
            readings = readings.trimmed();
            dictlist[1].append(readings.toLocal8Bit().constData());
            dictlist[0].append(kanji.toLocal8Bit().constData());
            dictlist[2].append(meanings.toLocal8Bit().constData());
            rowCount++;
            meanings = clrTxt;
            kanji = clrTxt;
            readings = clrTxt;
        }
        
    }


}

QVector<QStringList> Dict::search(QString searchString) {
    QVector<QStringList> searchResult;
    QStringList search_meaning_list;
    QStringList search_kanji_list;
    QStringList search_reading_list;
    searchResult.append(search_kanji_list);
    searchResult.append(search_reading_list);
    searchResult.append(search_meaning_list);

    for (int i = 0; i < dictlist[0].size(); i++) {
        if (dictlist[0][i].contains(searchString)) {
            searchResult[0].append(dictlist[0].at(i));
            searchResult[1].append(dictlist[1].at(i));
            searchResult[2].append(dictlist[2].at(i));
        }
    }

    return searchResult;
}

