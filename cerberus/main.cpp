#include "cerberus.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	cerberus w;
	w.show();
	return a.exec();
}
