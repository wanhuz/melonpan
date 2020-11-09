#pragma once
#include <qdialog.h>


class Frame : public QDialog
{
	Q_OBJECT;

public:
	
	Frame(QWidget* parent = Q_NULLPTR);
	void setOrientation(bool orientation);
	void setBoxSize();
	void setFontSize(int size);
	QPixmap shootScreenshot();

	
private:
	int y, x, curX, curY;
	bool orien;
	QPoint cursorPos;
	int fontsize;

};