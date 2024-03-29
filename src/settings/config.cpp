#include "config.h"

Config &Config::getInstance() {
	static Config instance;
	return instance;
}

void Config::load() {

}

void Config::save() {

}

//Change size of frame based on given font size
void Config::setFrameSize(int fontsize) {
	if (frame == NULL) {
		printf("Frame is not initialized");
		return;
	}

	this->frame->setFontSize(fontsize);
}

//Init frame
void Config::setFrame(Frame* frames) {
	if (frame == NULL) {
		frame = frames;
	}
	else {
		printf("Frame already initialized");
	}
	
}

void Config::setFrameOrientation(Frame::Orientation orientation) {
	if (frame == NULL) {
		printf("Frame is not initialized");
		return;
	}

	this->frame->setOrientation(orientation);
}