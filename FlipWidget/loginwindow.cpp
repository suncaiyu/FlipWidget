#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include <QPainter>
#include <QMovie>
#include <QHBoxLayout>
#include <QCursor>
#include <QMenu>
#include <QDebug>
#include <QTime>
#include "accountitem.h"
#include <QPropertyAnimation>

#define TRANSLATE_WIDTH 80

LoginWindow::LoginWindow(QWidget *parent)
	: BaseWindow(parent)
	, ui(new Ui::LoginWindow)
	, m_loginState(ONLINE)
	, m_view(&m_scene)
	, m_isPressed(false)
	, m_graphicsWidget(NULL)
{
	ui->setupUi(this);
	initWindow();
	initMyTitle();
	initAccountList();
	this->loadStyleSheet(":/Resources/LoginWindow/LoginWindow.css");

	connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SIGNAL(hideWindow()));
}

LoginWindow::~LoginWindow()
{
	delete ui;
}

// 初始化标题栏;
void LoginWindow::initMyTitle()
{
	// 因为这里有控件层叠了，所以要注意控件raise()方法的调用顺序;
	m_titleBar->move(0, 0);
	m_titleBar->raise();
	m_titleBar->setBackgroundColor(0, 0, 0, true);
	m_titleBar->setButtonType(MIN_BUTTON);
	m_titleBar->setTitleWidth(this->width());
	// 这里需要设置成false，不允许通过标题栏拖动来移动窗口位置,否则会造成窗口位置错误;
	m_titleBar->setMoveParentWindowFlag(false);
	ui->pButtonArrow->raise();
}

// 初始化窗口;
void LoginWindow::initWindow()
{
	//背景GIG图;
	QLabel* pBack = new QLabel(this);
	QMovie *movie = new QMovie();
	movie->setFileName(":/Resources/LoginWindow/back.gif");
	pBack->setMovie(movie);
	movie->start();
	pBack->move(0, 0);

	//暗注释;
	ui->accountComboBox->setEditable(true);
	QLineEdit* lineEdit = ui->accountComboBox->lineEdit();
    lineEdit->setPlaceholderText(QStringLiteral("QQ"));

    ui->passwordEdit->setPlaceholderText(QStringLiteral("password"));

	// 密码框中的小键盘按钮;
	m_keyboardButton = new QPushButton();
	m_keyboardButton->setObjectName("pButtonKeyboard");
	m_keyboardButton->setFixedSize(QSize(16, 16));
	m_keyboardButton->setCursor(QCursor(Qt::PointingHandCursor));

	QHBoxLayout* passwordEditLayout = new QHBoxLayout();
	passwordEditLayout->addStretch();
	passwordEditLayout->addWidget(m_keyboardButton);
	passwordEditLayout->setSpacing(0);
	passwordEditLayout->setContentsMargins(0, 0, 8, 0);

	ui->passwordEdit->setLayout(passwordEditLayout);
	ui->passwordEdit->setTextMargins(0, 0, m_keyboardButton->width() + 12, 0);

	ui->userHead->setPixmap(QPixmap(":/Resources/LoginWindow/HeadImage.png"));
	ui->loginState->setIcon(QIcon(":/Resources/LoginWindow/LoginState/state_online.png"));
	ui->loginState->setIconSize(QSize(13, 13));

	connect(ui->loginState, SIGNAL(clicked()), this, SLOT(onLoginStateClicked()));
	connect(ui->pButtonArrow, SIGNAL(clicked()), this, SLOT(onNetWorkSet()));
}

// 初始化用户登录信息;
void LoginWindow::initAccountList()
{
	// 设置代理;
	m_Accountlist = new QListWidget(this);
	ui->accountComboBox->setModel(m_Accountlist->model());
	ui->accountComboBox->setView(m_Accountlist);

	for (int i = 0; i < 3; i++)
	{
		AccountItem *account_item = new AccountItem();
        account_item->setAccountInfo(i, QStringLiteral("%1 hao").arg(i), QString(":/Resources/LoginWindow/headImage/head_%1.png").arg(i));
		connect(account_item, SIGNAL(signalShowAccountInfo(int, QString)), this, SLOT(onShowAccountInfo(int, QString)));
		connect(account_item, SIGNAL(signalRemoveAccount(int)), this, SLOT(onRemoveAccount(int)));
		QListWidgetItem *list_item = new QListWidgetItem(m_Accountlist);
		m_Accountlist->setItemWidget(list_item, account_item);
	}
}

// 选择了新的用户登录状态;
void LoginWindow::onLoginStateClicked()
{
	m_loginStateMemu = new QMenu();
    QAction *pActionOnline = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_online.png"), QStringLiteral("wozaoxianshang"));
    QAction *pActionActive = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_Qme.png"), QStringLiteral("Qwo"));
	m_loginStateMemu->addSeparator();
    QAction *pActionAway = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_away.png"), QStringLiteral("likai"));
    QAction *pActionBusy = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_busy.png"), QStringLiteral("manglu"));
    QAction *pActionNoDisturb = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_notdisturb.png"), QStringLiteral("budarao"));
	m_loginStateMemu->addSeparator();
    QAction *pActionHide = m_loginStateMemu->addAction(QIcon(":/Resources/LoginWindow/LoginState/state_hide.png"), QStringLiteral("yinshen"));
	// 设置状态值;
	pActionOnline->setData(ONLINE);
	pActionActive->setData(ACTIVE);
	pActionAway->setData(AWAY);
	pActionBusy->setData(BUSY);
	pActionNoDisturb->setData(NOT_DISTURB);
	pActionHide->setData(HIDE);


	connect(m_loginStateMemu, SIGNAL(triggered(QAction *)), this, SLOT(onMenuClicked(QAction*)));

	QPoint pos = ui->loginState->mapToGlobal(QPoint(0, 0)) + QPoint(0, 20);
	m_loginStateMemu->exec(pos);
}

// 用户状态菜单点击;
void LoginWindow::onMenuClicked(QAction * action)
{
	ui->loginState->setIcon(action->icon());
	// 获取状态值;
	m_loginState = (LoginState)action->data().toInt();
	qDebug() << "onMenuClicked" << m_loginState;
}

//将选项文本显示在QComboBox当中
void LoginWindow::onShowAccountInfo(int index, QString accountName)
{
	ui->accountComboBox->setEditText(accountName);
	ui->accountComboBox->hidePopup();

	// 更换用户头像;
	QString fileName = QString(":/Resources/LoginWindow/headImage/head_%1.png").arg(index);
	ui->userHead->setPixmap(QPixmap(fileName).scaled(ui->userHead->width(), ui->userHead->height()));
}

void LoginWindow::onNetWorkSet()
{
	emit rotateWindow();
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果;
void LoginWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
{
	if (m_isPressed)
	{
		QPoint movePoint = event->globalPos() - m_startMovePos;
		QPoint widgetPos = this->parentWidget()->pos() + movePoint;
		m_startMovePos = event->globalPos();
		this->parentWidget()->move(widgetPos.x(), widgetPos.y());
	}
	return QWidget::mouseMoveEvent(event);
}

void LoginWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

void LoginWindow::closeEvent(QCloseEvent *event)
{
	emit closeWindow();
    return QWidget::closeEvent(event);
}

void LoginWindow::onRemoveAccount(int index)
{
	for (int row = 0; row < m_Accountlist->count(); row++)
	{
		AccountItem* itemWidget = (AccountItem*)m_Accountlist->itemWidget(m_Accountlist->item(row));
		if (itemWidget != NULL && itemWidget->getItemWidgetIndex() == index)
		{
			m_Accountlist->takeItem(row);
			itemWidget->deleteLater();
		}
	}
}
