
#include "OpenglWindow.h"
#include <qevent.h>
//#include "DrawOp.h"
#include <qapplication.h>
#include <QTimer>

#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "egl/egl.h"

int usesize = 0;
EGLint		        pi32ConfigAttribs[32];//创建设备的适合的配置

bool GetConfig(int type, int &value, int& pos)
{
	for (int i = 0; i < usesize; i = i + 2)
	{
		if (pi32ConfigAttribs[i] == type)
		{
			value = pi32ConfigAttribs[i + 1];
			pos = i;
			return true;
		}
	}
	return false;
}

void SetConfig(int type, int value)
{
	int oldvalue;
	int pos = 0;
	if (GetConfig(type, oldvalue, pos))
	{
		pi32ConfigAttribs[pos] = type;
		pi32ConfigAttribs[pos + 1] = value;
	}
	else
	{
		pi32ConfigAttribs[usesize++] = type;
		pi32ConfigAttribs[usesize++] = value;
	}
	//设置结束位数据
	pi32ConfigAttribs[usesize] = EGL_NONE;
}

// 设备创建配置 
bool SelectEGLConfiguration(int nColorBPP, int nDepthBPP, int nStencilSize)
{
	SetConfig(EGL_BUFFER_SIZE, nColorBPP);
	SetConfig(EGL_DEPTH_SIZE, nDepthBPP);
	SetConfig(EGL_STENCIL_SIZE, nStencilSize);

	return true;
}

EGLDisplay eglDisplay;
EGLSurface eglSurface;
EGLConfig eglConfig;
EGLContext eglContext;
EGLNativeWindowType eglWindow;

// 错误提示
bool TestEGLError()
{
	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS)
	{
		return false;
	}
	return true;
}
void Initialize(HWND handle)
{
	HDC g_hDC = GetDC(handle);

	eglWindow = handle;
	eglDisplay = eglGetDisplay(g_hDC);
	if (eglDisplay == EGL_NO_DISPLAY)
		eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);

	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
	{
		MessageBoxA(0, "eglInitialize() failed.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	eglBindAPI(EGL_OPENGL_ES_API);//设置当前全局渲染API

	SelectEGLConfiguration(EGL_DONT_CARE, 16, 4);

	int iConfigs;

	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		MessageBoxA(0, "eglChooseConfig() failed.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);
	if (eglSurface == EGL_NO_SURFACE)
	{
		eglGetError(); // Clear error
		eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}

	if (!TestEGLError())
	{
		MessageBoxA(0, "eglCreateWindowSurface() failed.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);
	if (!TestEGLError())
	{
		MessageBoxA(0, "eglMakeCurrent() failed.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	if (!TestEGLError())
	{
		MessageBoxA(0, "eglMakeCurrent() failed.", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
}

void DrawOp()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.f, 1.0f, 0.0f, 1.0f);
	eglSwapBuffers(eglDisplay, eglSurface);
}

void Resize(float w, float h)
{
	glViewport(0, 0, w, h);
}

void MakeCurrent()
{
	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
}


OpenglWindow::OpenglWindow(QWidget* parent)
	: QWidget(parent)
{
	render_time = new QTimer(this);
	render_time->setInterval(10);
	connect(render_time, SIGNAL(timeout()), this, SLOT(render_update()));
	render_time->start(10);
	InitializeGL();
}

void OpenglWindow::paintEvent(QPaintEvent *e)
{
	DrawOp();
}

void OpenglWindow::resizeEvent(QResizeEvent *e)
{
	QSize size = e->size();
	float w = size.width();
	float h = size.height();
	Resize(w, h);
	resize(w, h);
}

void OpenglWindow::InitializeGL()
{
	Initialize((HWND)winId());
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