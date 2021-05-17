#pragma once
#include <qdialog.h>
#include <qlabel.h>
#include <qfont.h>
#include <qboxlayout.h>
#include "../data/entry.h"

class popup : public QDialog
{
	Q_OBJECT;

public:
	popup(QWidget* parent = Q_NULLPTR);
	void addEntry(entry ent);
	void clearEntry();
	void shows();

private:
	int ind = 0;
	int entsize = 0;
	int x, y;
	QFont* sansMonoJK;
	QLabel* kanji = new QLabel("kanji");
	QLabel* kana = new QLabel("kana");
	QLabel* gloss = new QLabel("gloss");
	QVector<entry> topEntry;
	entry processEnt(entry ent);
	void setTheme();
	

private slots:
	void selectEntry();
};