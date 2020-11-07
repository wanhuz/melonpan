#pragma once
#include <qstring.h>
#include <qstandarditemmodel.h>

class Dict {
public:
	Dict();
	void load();
	QStandardItemModel* getModel();
	QStringList search(QString searchString);

private:
	void parse(QByteArray* line);
	QStandardItemModel* dictmodel;
	QList <QStringList> dictlist;

};