#pragma once
#include <qstring.h>

class Dict {
public:
	Dict();
	void load();
	QStandardItemModel* getModel();

private:
	void parse(QString string);
	QStandardItemModel* dictmodel;

};