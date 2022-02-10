#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QStackedWidget>

class LoginWindow;
class LoginNetSetWindow;
class RotateWidget : public QStackedWidget
{
	Q_OBJECT

public:
	RotateWidget(QWidget *parent = NULL);
	~RotateWidget();

private:
	// 初始化旋转的窗口;
	void initRotateWindow();
	// 绘制旋转效果;
	void paintEvent(QPaintEvent* event);

private slots:
	// 开始旋转窗口;
	void onRotateWindow();
	// 窗口旋转结束;
	void onRotateFinished();
	// 最小化窗口;
	void onHideWindow();

private:
	// 当前窗口是否正在旋转;
	bool m_isRoratingWindow;
	LoginWindow* m_loginWindow;
	LoginNetSetWindow* m_loginNetSetWindow;
	int m_nextPageIndex;
};

#endif // ROTATEWIDGET_H
