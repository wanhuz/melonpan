#include "dict.h"
#include "DictLoader.h"

void DictLoader::run() {
	dict->load();
}

void DictLoader::setDict(Dict* dict) {
	this->dict = dict;
}

