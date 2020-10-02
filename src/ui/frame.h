#pragma once
#include <qdialog.h>


class Frame : public QDialog
{
	Q_OBJECT;

public:
	
	Frame(QWidget* parent = Q_NULLPTR);
	~Frame();
	void setOrientation(bool orientation);
	void setBoxSize();
	void setFontSize(int size);
	const bool Vertical = true;
	const bool Horizontal = false;

	
private:
	bool orien;
	QPoint cursorPos;
	int fontsize;

};