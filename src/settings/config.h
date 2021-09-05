#pragma once
#include "../ui/frame.h"
#include <iostream>
#include <fstream>

/*
Global configuration class using Singleton Implementation.

*/

class Config
{
	
private:
	Config() {};
	Config(Config const&);              
	void operator=(Config const&); 
	Frame* frame;

public:
	static Config& getInstance();
	void setFrame(Frame*);
	void reset();
	void load();
	void save();
	void setFrameOrientation(Frame::Orientation orientation);
	void setFrameSize(int size);
};



