#ifndef LoginWindow_H
#define LoginWindow_H

#include "basewindow.h"
#include <QListWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>

namespace Ui {
	class LoginWindow;
}

// ��¼״̬;
typedef enum
{
	ONLINE = 1,     //����;
	ACTIVE,         //��Ծ;
	AWAY,           //�뿪;
	BUSY,           //æµ;
	NOT_DISTURB,    //�������; 
	HIDE,           //����;
	OFFLINE         //����;
}LoginState;

class LoginWindow : public BaseWindow
{
	Q_OBJECT

public:
	LoginWindow(QWidget *parent = 0);
	~LoginWindow();

signals:
	void rotateWindow();
	void closeWindow();
	void hideWindow();

private:
	// ��ʼ��������;
	void initMyTitle();
	// ��ʼ������;
	void initWindow();
	// ��ʼ���û���¼��Ϣ;
	void initAccountList();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	

private slots:
	// ѡ�����µ��û���¼״̬;
	void onLoginStateClicked();
	// �û�״̬�˵����;
	void onMenuClicked(QAction * action);
	// ����ǰѡ��ĵ�¼�û���Ϣ��ʾ����;
	void onShowAccountInfo(int index, QString accountName);
	// �������ð�ť���;
	void onNetWorkSet();
	// �Ƴ���ǰ��¼�б���ĳһ��;
	void onRemoveAccount(int index);

private:
	Ui::LoginWindow *ui;
	// �����С���̰�ť;
	QPushButton* m_keyboardButton;
	// ��¼״̬����˵�;
	QMenu* m_loginStateMemu;
	// ��¼״ֵ̬;
	LoginState m_loginState;
	// �����б�;
	QListWidget* m_Accountlist;

	// ��ת;
	QGraphicsScene m_scene;
	QGraphicsWidget *m_graphicsWidget;
	QGraphicsView m_view;

	bool m_isPressed;
	QPoint m_startMovePos;
};

#endif // LoginWindow_H