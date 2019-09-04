#pragma once

#include <QWidget>
#include "win_graphdevice.h"

class OpenglWindow : public QWidget
{
	Q_OBJECT
public:
	explicit OpenglWindow(QWidget* parent);
	void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
	void resizeEvent(QResizeEvent *e) Q_DECL_OVERRIDE;
	void InitializeGL();
	bool event(QEvent *e);
private slots:
	void render_update();
private:
	QTimer *render_time;
	CGraphDevice m_GraphDevice;
};