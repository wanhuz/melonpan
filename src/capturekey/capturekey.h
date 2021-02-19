#pragma once
//#include <qobject.h>
#include <qthread.h>

class capturekey : public QThread {
	Q_OBJECT;

public:
	capturekey();
	int setEnable();
	int disable();
	int setKey();
	

private:
	bool enable;
	int key;
	bool keyPressed(int key);
	void run() override;

signals:
	void keyStateChanged();

};