#include <qthread.h>
#include "dict.h"
#include "DictLoader.h"

DictLoader::DictLoader() {
	
}

void DictLoader::run() {
	dict->load();
}

void DictLoader::setDict(Dict* dict) {
	this->dict = dict;
}

QStandardItemModel* DictLoader::getModel() {
	return dict->getModel();
}