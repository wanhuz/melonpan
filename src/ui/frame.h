#pragma once
#include <qdialog.h>


class Frame : public QDialog
{
	Q_OBJECT;

public:
	Frame(QWidget* parent = Q_NULLPTR);
	enum Orientation { Vertical, Horizontal };
	void setOrientation(Orientation newOrient);
	void setBoxSize(int fontsize);
	void setFontSize(int size);
	void initBox();
	QPixmap shootScreenshot();
	
	
private:
	int y, x, curX, curY;
	Orientation currOrient;
	QPoint cursorPos;

};