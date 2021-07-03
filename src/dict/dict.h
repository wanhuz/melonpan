#pragma once
#include <qstring.h>
#include <qvector.h>
#include <qmap.h>
#include "../data/entry.h"

class Dict {

public:
	Dict();
	void load();
	QVector<entry> search(QString searchString);
	QVector<entry> searchWithRoot(QString fSearchStr, QString sSearchStr);
	QVector<entry> sort(QVector<entry> searchedWord, QString targetString);
	QVector<entry> sortWithRoot(QVector<entry> searchedWord, QString targetString, QString rootString);

private:
	void parse(QByteArray* line);
	QVector<entry> dictlist;
	QMap<QString, int> freqMap;
};