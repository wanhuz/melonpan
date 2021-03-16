#include <iostream>
#include <fstream>
#include "../ui/frame.h"

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
	void setFrameOrientation(bool orientation);
	void setFrameSize(int size);
};



