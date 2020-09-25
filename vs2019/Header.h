#pragma once

#include <QtWidgets/QMainWindow>

class KanjiProgram : public QMainWindow
{
    Q_OBJECT

public:
    KanjiProgram(QWidget* parent = Q_NULLPTR);
    void displayOCRresult(QString result);

private:
    Ui::KanjiProgramClass ui;
    QLineEdit* textbox;
};
