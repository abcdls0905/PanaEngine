
#include "OpenglWindow.h"
#include <qevent.h>
#include <qapplication.h>
#include <QTimer>

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "egl/egl.h"

OpenglWindow::OpenglWindow(QWidget* parent)
	: QWidget(parent)
{
	render_time = new QTimer(this);
	render_time->setInterval(10);
	connect(render_time, SIGNAL(timeout()), this, SLOT(render_update()));
	render_time->start(10);
	m_GraphDevice.InitDevice((HWND)winId());
}

void OpenglWindow::paintEvent(QPaintEvent *e)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.0f, 0.0f, 1.0f);
	m_GraphDevice.Present();
}

void OpenglWindow::resizeEvent(QResizeEvent *e)
{
	QSize size = e->size();
	float w = size.width();
	float h = size.height();
	glViewport(0, 0, w, h);

	resize(w, h);
}

void OpenglWindow::InitializeGL()
{
}

void OpenglWindow::render_update()
{
	QEvent event(QEvent::Paint);
	QApplication::sendEvent(this, &event);
}

bool OpenglWindow::event(QEvent *e)
{
	return QWidget::event(e);
}