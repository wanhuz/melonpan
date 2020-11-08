#pragma once
#include <qstring.h>
#include <qvector.h>

class Dict {
public:
	Dict();
	void load();
	QVector<QStringList> search(QString searchString);

private:
	void parse(QByteArray* line);
	QVector<QStringList> dictlist;

};