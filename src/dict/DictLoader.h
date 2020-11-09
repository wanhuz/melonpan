#pragma once
#include <qthread.h>
#include <qstandarditemmodel.h>
#include "dict.h"

class DictLoader : public QThread {
	Q_OBJECT;

public:
	DictLoader();
	void run() override;
	void setDict(Dict* dict);

private:
	Dict* dict;


};