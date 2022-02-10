#include "loginnetsetwindow.h"
#include <QPainter>
#include <QMovie>
#include <QMouseEvent>

LoginNetSetWindow::LoginNetSetWindow(QWidget *parent)
	: BaseWindow(parent)
{
	ui.setupUi(this);
	initWindow();
	initMyTitle();
	connect(m_titleBar, SIGNAL(signalButtonMinClicked()), this, SIGNAL(hideWindow()));
}

LoginNetSetWindow::~LoginNetSetWindow()
{

}

void LoginNetSetWindow::initMyTitle()
{
	m_titleBar->move(0, 0);
	m_titleBar->raise();
	m_titleBar->setBackgroundColor(0, 0, 0, true);
	m_titleBar->setButtonType(MIN_BUTTON);
	m_titleBar->setTitleWidth(this->width());
	// ������Ҫ���ó�false��������ͨ���������϶����ƶ�����λ��,�������ɴ���λ�ô���;
	m_titleBar->setMoveParentWindowFlag(false);
}

void LoginNetSetWindow::initWindow()
{
	//����GIGͼ;
	QLabel* pBack = new QLabel(this);
	QMovie *movie = new QMovie();
	movie->setFileName(":/Resources/NetSetWindow/headBack.gif");
	pBack->setMovie(movie);
	movie->start();
	pBack->move(0, 0);

	connect(ui.pButtonOk, SIGNAL(clicked()), this, SIGNAL(rotateWindow()));
	connect(ui.pButtonCancel, SIGNAL(clicked()), this, SIGNAL(rotateWindow()));
	
    ui.comboBoxNetType->addItem(QStringLiteral("dont use proxy"));
    ui.comboBoxServerType->addItem(QStringLiteral("dont use higher choose"));
}

void LoginNetSetWindow::paintEvent(QPaintEvent *event)
{
	// ���Ʊ���ͼ;
	QPainter painter(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(pathBack, QBrush(QColor(235, 242, 249)));
	
	QPainterPath pathBottom;
	pathBottom.setFillRule(Qt::WindingFill);
	pathBottom.addRoundedRect(QRect(0, 300, this->width(), this->height() - 300), 3, 3);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(pathBottom, QBrush(QColor(205, 226, 242)));

	painter.setPen(QPen(QColor(160 , 175 , 189)));
	painter.drawRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
}

// ����ͨ��mousePressEvent��mouseMoveEvent��mouseReleaseEvent�����¼�ʵ��������϶��������ƶ����ڵ�Ч��;
void LoginNetSetWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isPressed = true;
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void LoginNetSetWindow::mouseMoveEvent(QMouseEvent *event)
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

void LoginNetSetWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

void LoginNetSetWindow::closeEvent(QCloseEvent *event)
{
	emit closeWindow();
    return QWidget::closeEvent(event);
}
