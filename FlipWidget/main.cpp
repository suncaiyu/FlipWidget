#include "WindowRotation.h"
#include <QtWidgets/QApplication>
#include "rotatewidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RotateWidget w;
	w.show();
	return a.exec();
}
