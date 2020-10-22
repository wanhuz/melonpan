#pragma once
#include <qstring.h>
#include <qstandarditemmodel.h>

class Dict {
public:
	Dict();
	void load();
	QStandardItemModel* getModel();

private:
	void parse(QByteArray* line);
	QStandardItemModel* dictmodel;

};