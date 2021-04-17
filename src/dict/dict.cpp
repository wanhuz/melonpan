#include "dict.h"
#include <qstandarditemmodel.h>
#include <QtCore\qfile.h>
#include <QDebug>
#include <qstring.h>
#include <QBuffer>
#include <qeventloop.h>
#include <qdir.h>
#include <algorithm>
#include "../data/entry.h"



Dict::Dict() {
    // Hard mapping of word frequency line in Japanese Dictionary file to number
    freqMap.insert("<re_pri>news1</re_pri>", 1);
    freqMap.insert("<re_pri>news2</re_pri>", 2);
    freqMap.insert("<re_pri>ichi1</re_pri>", 3);
    freqMap.insert("<re_pri>ichi2</re_pri>", 4);
    freqMap.insert("<re_pri>spec1</re_pri>", 5);
    freqMap.insert("<re_pri>spec2</re_pri>", 6);
    freqMap.insert("<re_pri>gai1</re_pri>", 7);
    freqMap.insert("<re_pri>gai2</re_pri>", 8);
    freqMap.insert("<ke_pri>news1</ke_pri>", 1);
    freqMap.insert("<ke_pri>news2</ke_pri>", 2);
    freqMap.insert("<ke_pri>ichi1</ke_pri>", 3);
    freqMap.insert("<ke_pri>ichi2</ke_pri>", 4);
    freqMap.insert("<ke_pri>spec1</ke_pri>", 5);
    freqMap.insert("<ke_pri>spec2</ke_pri>", 6);
    freqMap.insert("<ke_pri>gai1</ke_pri>", 7);
    freqMap.insert("<ke_pri>gai2</ke_pri>", 8);
}

/*Load file into QList*/
void Dict::load() {
    QString dictPath = QDir::currentPath();
    //dictPath = dictPath + "/res/JMdict_e"; //Deployment
    dictPath = "C://Users//WanHuz//Documents//Shanachan//res//JMdict_e"; //Debug Mode
    QFile dictFile(dictPath);
    if (!dictFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open dictionary file " + dictPath;
        return;
    }

    QByteArray data = dictFile.readAll();
    this->parse(&data);
    dictFile.close(); 
}

void Dict::parse(QByteArray* data) {
    QBuffer buffer(data);
    buffer.open(QIODevice::ReadOnly);
    QTextStream out(&buffer);
    out.setCodec("UTF-8");

    const int MAX_PRIORITY = 100;
    const QString CLRTXT = "";
    QString meanings = CLRTXT;
    QString kanji = CLRTXT;
    QString readings = CLRTXT;
    QString line = CLRTXT;
    int wordFreq = MAX_PRIORITY;
   
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
            line = line + "\n";
            meanings = meanings + line;
        }
        else if (line.startsWith("<reb>")) {
            line.remove(0, 5);
            line.remove("</reb>");
            readings = readings + line + "\n";
        }
        else if ( (line.contains("<re_pri>")) || (line.contains("<ke_pri>")) ) {
            int tempFreq = freqMap.value(line);

            //If line is not in Map, skip
            if (!tempFreq) { continue; }
            
            if (tempFreq < wordFreq) {
                wordFreq = tempFreq;
            } 

            
        }
        else if (line.startsWith("</ent")) {
            //Memory allocation here is 130MB~ give or take
            readings = readings.trimmed();
            meanings.chop(1);
            entry tempEntry = entry(kanji, readings, meanings, wordFreq);
            dictlist.append(tempEntry);

            meanings = CLRTXT;
            kanji = CLRTXT;
            readings = CLRTXT;
            wordFreq = MAX_PRIORITY;
        }
        
    }

   
}

/*Search Kanji or Kana and return result if the entry starts with target Kana or Kanji*/
QVector<entry> Dict::search(QString searchString) {
    QVector<entry> searchResult;

    for (int i = 0; i < dictlist.size(); i++) {
        if (dictlist[i].getKanji().startsWith(searchString) || dictlist[i].getReading().startsWith(searchString)) {
            entry tempEntry = entry(
                dictlist[i].getKanji(),
                dictlist[i].getReading(),
                dictlist[i].getGloss(),
                dictlist[i].getFreq()
            );
            searchResult.append(tempEntry);
        }

    }

    return searchResult;
}

/*Sort from highest word frequency to lowest word frequency. If there is an exact match to search string, place it at the highest frequency*/
QVector<entry> Dict::sort(QVector<entry> searchedWord, QString targetString) {
    int size = searchedWord.size();

    for (int i = 0; i < size; i++) {
        if ( (searchedWord[i].getKanji() == targetString) || (searchedWord[i].getReading() == targetString) ) {
            searchedWord[i].setFreq(0);
        }
    }

    std::sort(searchedWord.begin(), searchedWord.end(), []
    (entry searchedWord, entry searchedWordNext)
        { return searchedWord.getFreq() < searchedWordNext.getFreq();});

    return searchedWord;
}



