#include "dict.h"
#include <qstandarditemmodel.h>
#include <QtCore\qfile.h>
#include <QDebug>
#include <qstring.h>
#include <QBuffer>

Dict::Dict() {
    dictmodel = new QStandardItemModel(4000,2);
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

    QString colline = "";
    while (!out.atEnd()) {
        QString line = out.readLine();

        if (line.contains("<keb>")) {
            dictmodel->setItem(rowCount, 0, new QStandardItem(line));
        }
        else if (line.contains("<gloss>")) {
            colline = colline + ";" + line;
        }
        else if (line.contains("</entry>")) {
            dictmodel->setItem(rowCount, 1, new QStandardItem(colline));
            colline = "";
            rowCount++;
            if (rowCount == dictmodel->rowCount()) {
                break;
            }
        }


        
    }

}

QStandardItemModel* Dict::getModel() {
    return dictmodel;
}