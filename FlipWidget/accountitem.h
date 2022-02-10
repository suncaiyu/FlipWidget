#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QMouseEvent>

class AccountItem : public QWidget
{
	Q_OBJECT

public:
	AccountItem(QWidget *parent = NULL);

	// ���õ�¼�û���Ϣ;
	void setAccountInfo(int index, QString accountName, QString headFilePath);
	// ��ȡ��¼�û�����;
	QString getAccountName();
	// ��ȡ��ǰitemWidget��index;
	int getItemWidgetIndex();

public slots:
	// ɾ����ǰ�û�item;
	void onRemoveAccount();

private:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

Q_SIGNALS:
	// ֪ͨ��¼������ʾ��ǰ�û���Ϣ;
	void signalShowAccountInfo(int index, QString accountName);
	// ֪ͨ��¼����ɾ����ǰ�û���Ϣ;
	void signalRemoveAccount(int index);

private:
	bool m_mousePress;
	QLabel *m_accountNumber;
	QToolButton *m_deleteButton;
	QLabel *m_Icon;
	int m_index;
};

#endif // ACCOUNTITEM_H