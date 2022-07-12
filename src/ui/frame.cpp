#include "frame.h"
#include <qframe.h>
#include <qlayout.h>
#include <qguiapplication.h>
#include <qscreen.h>
#include <qpixmap.h>


Frame::Frame(QWidget* parent)
	: QDialog(parent)
{
	QFrame* border = new QFrame();
	QLayout* lay = new QVBoxLayout();

	border->setWindowFlag(Qt::Tool);
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

	//Set default size and orientation
	this->setOrientation(Horizontal);
	this->setFontSize(12);
}


/*Setter for orientation, 1 = vertical, 0 = horizontal */
void Frame::setOrientation(Orientation newOrient) {
	if (newOrient == currOrient) { return; }
	else { currOrient = newOrient; }

}

/*Set font size. Changing font size changes the frame box size*/
void Frame::setFontSize(int size) {
	if (size > 5 && size < 100) {
		this->setBoxSize(size);
	}
}

/* Set the box size of the frame*/
void Frame::setBoxSize(int fontsize) {
	x = (fontsize + 20);
	y = x * 4; //Multiple to 4 character
}

// Set the box position so that it spawn around the mouse cursor
void Frame::initBox() {
	QPoint cursorPos;
	
	cursorPos = QCursor::pos();
	curX = cursorPos.x() - (x / 2);
	curY = cursorPos.y() - (x / 2);

	if (currOrient == Horizontal) {
		this->setGeometry(curX, curY, x, y);
	}
	else if (currOrient == Vertical) {
		this->setGeometry(curX, curY, y, x);
	}
}

QPixmap Frame::shootScreenshot() {
	QScreen* screen = QGuiApplication::primaryScreen();
	QPixmap desktopPixmap = screen->grabWindow(0, curX, curY, x, y);

	return desktopPixmap;
}

