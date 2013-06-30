#ifndef CERBERUS_H
#define CERBERUS_H

#include <QtGui/QMainWindow>
#include "ui_cerberus.h"

class cerberus : public QMainWindow
{
	Q_OBJECT

public:
	cerberus(QWidget *parent = 0, Qt::WFlags flags = 0);
	~cerberus();

private:
	Ui::cerberusClass ui;
};

#endif // CERBERUS_H
