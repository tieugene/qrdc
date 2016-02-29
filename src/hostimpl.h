#ifndef HOSTIMPL_H
#define HOSTIMPL_H
//
#include <QtGui>
#include <QtSql>
#include "dialogimpl.h"
#include "ui_host.h"
//
class DialogHostImpl : public DialogImpl, public Ui::DialogHost
{
Q_OBJECT
public:
	DialogHostImpl(QWidget * parent = 0, Qt::WFlags f = 0);
	void	setModel(QSqlTableModel *);
};
#endif
