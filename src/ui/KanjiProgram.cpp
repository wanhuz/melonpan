#include "KanjiProgram.h"
#include <QtWidgets/qlineedit.h>

KanjiProgram::KanjiProgram(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    textbox = ui.lineEdit;
    
}

void KanjiProgram::displayOCRresult(QString result) {
    textbox->setText(result);
}
