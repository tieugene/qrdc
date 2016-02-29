#ifndef PROTOCOLIMPL_H
#define PROTOCOLIMPL_H
//
#include <QtGui>
#include <QtSql>
#include "dialogimpl.h"
#include "ui_protocol.h"
//
class DialogProtocolImpl : public DialogImpl, public Ui::DialogProtocol
{
Q_OBJECT
public:
	DialogProtocolImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	void	setModel(QSqlTableModel *);
};
#endif
