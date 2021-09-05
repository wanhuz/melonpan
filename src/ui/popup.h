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
	int index = 0;
	int EntrySize = 0;
	int x, y;
	QFont* sansMonoJK;
	QLabel* kanji = new QLabel("kanji");
	QLabel* kana = new QLabel("kana");
	QLabel* gloss = new QLabel("gloss");
	QVector<entry> PopupDict;

	entry sanitizeEntry(entry ent);
	void initTheme();
	

private slots:
	void selectEntry();
};