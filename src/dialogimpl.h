#ifndef DIALOGIMPL_H
#define DIALOGIMPL_H
//
#include <QtGui>
#include <QtSql>
//
class DialogImpl : public QDialog
{
Q_OBJECT
public:
	DialogImpl(QWidget * parent = 0, Qt::WFlags f = 0);
	bool	Edit(QModelIndex);
	bool	Add(void);
protected:
	QWidget			*firstWidget;
	QSqlTableModel		*model;
	QDataWidgetMapper	*mapper;
	void	prepareModel(QSqlTableModel *);
	bool	addedit(QModelIndex);
};
#endif
