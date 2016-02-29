#ifndef CONNECTIONIMPL_H
#define CONNECTIONIMPL_H
//
#include <QtGui>
#include <QtSql>
#include "ui_connection.h"
//
class DialogConnectionImpl : public QDialog, public Ui::DialogConnection
{
Q_OBJECT
public:
	DialogConnectionImpl(QWidget * parent = 0, Qt::WFlags f = 0);
	bool	Edit(QModelIndex);
	bool	Add(void);
	void	setModel(QSqlRelationalTableModel *);
private:
	QSqlRelationalTableModel	*model;
	QDataWidgetMapper		*mapper;
	bool	addedit(QModelIndex);
};
#endif
