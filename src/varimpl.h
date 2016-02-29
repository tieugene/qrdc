#ifndef VARIMPL_H
#define VARIMPL_H
//
#include <QtGui>
#include <QtSql>
#include "dialogimpl.h"
#include "ui_var.h"
//
class DialogVarImpl : public DialogImpl, public Ui::DialogVar
{

public:
	DialogVarImpl(QWidget * parent = 0, Qt::WFlags f = 0);
	void	setModel(QSqlTableModel *);
};
#endif
