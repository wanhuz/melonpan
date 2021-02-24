#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SettingsWindow.h"

class SettingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    SettingsWindow(QWidget* parent = Q_NULLPTR);

private:
    Ui::SettingsWindow uiSettings;

};