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
	// ��ʼ����ת�Ĵ���;
	void initRotateWindow();
	// ������תЧ��;
	void paintEvent(QPaintEvent* event);

private slots:
	// ��ʼ��ת����;
	void onRotateWindow();
	// ������ת����;
	void onRotateFinished();
	// ��С������;
	void onHideWindow();

private:
	// ��ǰ�����Ƿ�������ת;
	bool m_isRoratingWindow;
	LoginWindow* m_loginWindow;
	LoginNetSetWindow* m_loginNetSetWindow;
	int m_nextPageIndex;
};

#endif // ROTATEWIDGET_H
