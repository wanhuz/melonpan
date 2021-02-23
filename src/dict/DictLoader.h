#pragma once
#include <qthread.h>
#include "dict.h"

class DictLoader : public QThread {
	Q_OBJECT;

public:
	void run() override;
	void setDict(Dict* dict);

private:
	Dict* dict;


};