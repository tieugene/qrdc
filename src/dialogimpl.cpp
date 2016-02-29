#include "dialogimpl.h"
//
DialogImpl::DialogImpl( QWidget * parent, Qt::WFlags f ) 
	: QDialog(parent, f) {
	// TODO
	// 1. set focus
	firstWidget = 0;
}

void	DialogImpl::prepareModel(QSqlTableModel *m) {
	model = m;
	mapper = new QDataWidgetMapper(this);
	mapper->setModel(model);
	//mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	mapper->setItemDelegate(new QItemDelegate(this));
}

bool	DialogImpl::Edit(QModelIndex idx) {
	setWindowTitle(tr("Edit"));
	return addedit(idx);
}

bool	DialogImpl::Add(void) {
	setWindowTitle(tr("Add"));
	int row = model->rowCount();
	model->insertRow(row);
	return addedit(model->index(row, 0));
}

bool	DialogImpl::addedit(QModelIndex idx) {
	bool retvalue = false;
	mapper->setCurrentModelIndex(idx);
	if (firstWidget)
		firstWidget->setFocus();
	if (exec() == QDialog::Accepted) {
		if (!mapper->submit()) {
			QMessageBox::critical(0, tr("Edit error"), tr("Can't write changes"));
			mapper->revert();
		} else
			retvalue = true;
	} else
		mapper->revert();
	return retvalue;
}
//
