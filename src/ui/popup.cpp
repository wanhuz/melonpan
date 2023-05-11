#include "popup.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <qcursor.h>
#include <qsizepolicy.h>
#include "../data/entry.h"
#include <qdir.h>
#include <qfontdatabase.h>

#define MAX_ENTRY 5
#define MIN_ENTRY 0

#ifdef DEBUG_MODE
#define ABSPATHTOFONT fontPath = "..\\res\\font\\NotoSansMonoCJKjp-Regular.otf"
#else
#define ABSPATHTOFONT
#endif


popup::popup(QWidget* parent)
	: QDialog(parent)
{
	
	QBoxLayout* hlayoutbottom = new QHBoxLayout;
	QPushButton* btnPrev = new QPushButton("^");
	QPushButton* btnNext = new QPushButton("v");
	QBoxLayout* vlayout = new QVBoxLayout;

	//Init theme
	this->initTheme();
	
	//Set widget properties
	this->setWindowFlags(Qt::NoDropShadowWindowHint | Qt::FramelessWindowHint | Qt::Popup);
	this->setContentsMargins(0, 0, 0, 0);
	this->setLayout(vlayout);
	gloss->setWordWrap(true);
	gloss->setAlignment(Qt::AlignJustify);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	gloss->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->setMinimumHeight(140);

	//Set layout properties
	btnPrev->setFixedSize(25, 25);
	btnNext->setFixedSize(25, 25);
	vlayout->setContentsMargins(0, 0, 0, 0);
	vlayout->setSpacing(0);
	vlayout->addWidget(kanji);
	vlayout->addWidget(kana);
	hlayoutbottom->addStretch();
	hlayoutbottom->addWidget(btnPrev);
	hlayoutbottom->addSpacing(5);
	hlayoutbottom->addWidget(btnNext);
	hlayoutbottom->setContentsMargins(5, 5, 5, 5);
	vlayout->addWidget(gloss);
	vlayout->addLayout(hlayoutbottom);
	
	connect(btnNext, &QPushButton::clicked, this, [=]() {if (index < EntrySize-1) { index++; }});
	connect(btnPrev, &QPushButton::clicked, this, [=]() {if (index > MIN_ENTRY) { index--; }});
	connect(btnNext, SIGNAL(clicked()), this, SLOT(selectEntry()));
	connect(btnPrev, SIGNAL(clicked()), this, SLOT(selectEntry()));
}


void popup::addEntry(entry Entry) {
	if (PopupDict.size() > MAX_ENTRY) {
		printf("Entry is higher than 5. No new entry is added");
		return;
	}

	EntrySize++;
	entry newEntry = this->sanitizeEntry(Entry);
	PopupDict.append(newEntry);
}

void popup::clearEntry() {
	if (PopupDict.size() > 0) {
		PopupDict.clear();
	}

	EntrySize = 0;
	index = 0;
}

void popup::selectEntry() {
	if (PopupDict.size() < 1 || PopupDict.isEmpty()) {
		printf("No entry"); 
		return; 
	}

	kanji->setText(PopupDict[index].getKanji());
	kana->setText(PopupDict[index].getReading());
	gloss->setText(PopupDict[index].getGloss());

	this->setGeometry(x, y, 224, 200);
}

//Select the first entry before showing the widget
void popup::shows() {
	QPoint curCurPos = QCursor::pos();
	x = curCurPos.x() + 10;
	y = curCurPos.y() - (200 + 10);


	this->selectEntry();
	this->show();
}

void popup::initTheme() {
	const QString style( "QDialog {background-color: white; border: 1px solid black;}"
						 "QPushButton {border:none; background-color: #3f87f5; color: white;}" 
						 "QPushButton:hover {background-color: #3867db}"
						);

	//Initialize Font
	QString fontPath = QDir::currentPath();
	fontPath = fontPath + "//res//font//NotoSansMonoCJKjp-Regular.otf";

	ABSPATHTOFONT;

	int id = QFontDatabase::addApplicationFont(fontPath);

	if (id < 0) {
		qDebug() << "Failed to load Sans Mono JK font at " << fontPath;
	}
	else {
		QString NotoJK = QFontDatabase::applicationFontFamilies(id).at(0);
		sansMonoJK = new QFont(NotoJK, 12);

		kanji->setFont(*sansMonoJK);
		kana->setFont(*sansMonoJK);
	}

	//Set Windows property and style
	kanji->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	kana->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	kanji->setContentsMargins(11, 5, 5, 5);
	kana->setContentsMargins(11, 5, 5, 5);
	gloss->setContentsMargins(11, 11, 11, 11);

	kanji->setStyleSheet("font-size: 20px; font-weight: bold; background-color: #3867db; color: white;");
	kana->setStyleSheet("font-size: 15px; font-weight: bold; background-color: #3f87f5; color: white;");
	this->setStyleSheet(style);
}

//Clean and return one entry
entry popup::sanitizeEntry(entry Entry) {
	QString cleanKana;
	QString cleanGloss;
	QString cleanKanji;
	int kanaindex, n;

	//Only take one kana reading
	cleanKana = Entry.getReading();
	kanaindex = cleanKana.indexOf("\n");

	if (kanaindex > -1) {
		cleanKana.remove(kanaindex, cleanKana.size());
	}

	//Only take first N string of glossary
	cleanGloss = Entry.getGloss();
	n = 200;

	if (cleanGloss.size() > n) {
		cleanGloss.remove(n, cleanGloss.size());
		cleanGloss.append(" ... (more)");
	}

	//If there is no kanji entry, put kana in kanji
	cleanKanji = Entry.getKanji();

	if (cleanKanji.isEmpty()) {
		cleanKanji = cleanKana;
		cleanKana = "";
	}
	
	entry tempEntry(
		cleanKanji,
		cleanKana,
		cleanGloss,
		Entry.getFreq()
	);

	return tempEntry;


}