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

// 登录状态;
typedef enum
{
	ONLINE = 1,     //在线;
	ACTIVE,         //活跃;
	AWAY,           //离开;
	BUSY,           //忙碌;
	NOT_DISTURB,    //请勿打扰; 
	HIDE,           //隐身;
	OFFLINE         //离线;
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
	// 初始化标题栏;
	void initMyTitle();
	// 初始化窗口;
	void initWindow();
	// 初始化用户登录信息;
	void initAccountList();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	

private slots:
	// 选择了新的用户登录状态;
	void onLoginStateClicked();
	// 用户状态菜单点击;
	void onMenuClicked(QAction * action);
	// 将当前选择的登录用户信息显示界面;
	void onShowAccountInfo(int index, QString accountName);
	// 网络设置按钮点击;
	void onNetWorkSet();
	// 移除当前登录列表中某一项;
	void onRemoveAccount(int index);

private:
	Ui::LoginWindow *ui;
	// 密码框小键盘按钮;
	QPushButton* m_keyboardButton;
	// 登录状态点击菜单;
	QMenu* m_loginStateMemu;
	// 登录状态值;
	LoginState m_loginState;
	// 下拉列表;
	QListWidget* m_Accountlist;

	// 翻转;
	QGraphicsScene m_scene;
	QGraphicsWidget *m_graphicsWidget;
	QGraphicsView m_view;

	bool m_isPressed;
	QPoint m_startMovePos;
};

#endif // LoginWindow_H