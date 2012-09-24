#ifndef CONSUEGRA_H
#define CONSUEGRA_H

#include <QtGui/QMainWindow>
#include "ui_consuegra.h"
#include <QtGui>

class consuegra : public QMainWindow
{
	Q_OBJECT

public:
	consuegra(QWidget *parent = 0, Qt::WFlags flags = 0);
	~consuegra();

private slots:
	void import();

private:
	void connects();
	QStringList findFilesRecursively (QProgressDialog &progressDialog, QStringList &paths, QString fileTypes );
	void find(const QString &path);
	Ui::mainWindow ui;
};

#endif // CONSUEGRA_H
