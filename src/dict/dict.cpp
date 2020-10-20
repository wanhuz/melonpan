#include "dict.h"
#include <QtGui\qstandarditemmodel.h>
#include <QtCore\qfile.h>
#include <QDebug>
#include <qstring.h>

Dict::Dict() {
	QStandardItemModel* dictmodel = new QStandardItemModel();
	
}

/*Load file into qstandarditemmodel*/
void Dict::load() {
	QFile dictFile("../res/JMdict_e");
    if (!dictFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!dictFile.atEnd()) {
        QByteArray line = dictFile.readLine();
        
        parse(line);
    }
}

void Dict::parse(QString string) {
    if (string.contains("<keb>")) {
        string = string.toUtf8();
        qDebug() << string;
    }
}