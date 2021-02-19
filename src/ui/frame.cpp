#include "frame.h"
#include <qframe.h>
#include <qlayout.h>
#include <qguiapplication.h>
#include <qwindow.h>
#include <qscreen.h>
#include <qapplication.h>
#include <qpixmap.h>
#include <qdebug.h>


Frame::Frame(QWidget* parent)
	: QDialog(parent)
{
	QFrame* border = new QFrame();
	QLayout* lay = new QVBoxLayout();

	this->setLayout(lay);
	lay->addWidget(border);
	lay->setContentsMargins(0, 0, 0, 0);
	border->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	border->setLineWidth(1);
	border->setFrameShape(QFrame::Box);
	border->setContentsMargins(1, 1, 1, 1);
	border->setStyleSheet("color:red;");
	
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	this->setContentsMargins(0, 0, 0, 0);
	this->setAttribute(Qt::WA_TranslucentBackground);
	
	this->setOrientation(1);
	this->setFontSize(12);
	this->setBoxSize();
	
}


/*Setter for orientation, 1 = vertical, 0 = horizontal */
void Frame::setOrientation(bool orienVal) {

	if (orienVal == orien) {
		return;
	}
	else {
		orien = orienVal;
	}

}

/*Setter for font size*/
void Frame::setFontSize(int size) {
	if (size > 5 && size < 30) {
		fontsize = size;
	}
}

/* Set the box size of the frame*/
void Frame::setBoxSize() {
	QPoint curCurPos;
	if (fontsize == NULL) {
		printf("Err: font size is not specified");
		return;
	}

	y = (fontsize + 20);
	x = y * 3;
	curCurPos = QCursor::pos();
	curX = curCurPos.x() - (y / 2);
	curY = curCurPos.y() - (y / 2);

	if (orien) {
		this->setGeometry(curX, curY, y, x);
	}
	else {
		this->setGeometry(curX, curY, x, y);
	}
}

QPixmap Frame::shootScreenshot() {
	QScreen* screen = QGuiApplication::primaryScreen();
	QPixmap desktopPixmap = screen->grabWindow(0, curX, curY, y, x);
	return desktopPixmap;
}

