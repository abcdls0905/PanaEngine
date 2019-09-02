#include "PanaEngine.h"

PanaEngine::PanaEngine(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

void PanaEngine::resizeEvent(QResizeEvent* event)
{
	ui.openGLWidget->resizeEvent(event);
}
