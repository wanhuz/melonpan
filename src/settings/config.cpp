#include "config.h"

Config &Config::getInstance() {
	static Config instance;
	return instance;
}

void Config::load() {

}

void Config::save() {

}

void Config::setFrameSize(int fontsize) {
	if (frame == NULL) {
		printf("Frame is not initialized");
		return;
	}
	this->frame->setFontSize(fontsize);
}

void Config::setFrame(Frame* frames) {
	if (frame == NULL) {
		frame = frames;
	}
	else {
		printf("Frame already initialized");
	}
	
}

void Config::setFrameOrientation(bool orientation) {
	if (frame == NULL) {
		printf("Frame is not initialized");
		return;
	}
	this->frame->setOrientation(orientation);
}