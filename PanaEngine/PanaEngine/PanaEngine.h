#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PanaEngine.h"

class PanaEngine : public QMainWindow
{
    Q_OBJECT

public:
    PanaEngine(QWidget *parent = Q_NULLPTR);
	void resizeEvent(QResizeEvent* event);
private:
    Ui::PanaEngineClass ui;
};
