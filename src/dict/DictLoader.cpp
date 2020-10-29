#include <qthread.h>
#include "dict.h"
#include "DictLoader.h"

DictLoader::DictLoader() {
	dict = new Dict();
}

void DictLoader::run() {
	dict->load();
}

QStandardItemModel* DictLoader::getModel() {
	return dict->getModel();
}