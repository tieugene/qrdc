#include "connectionimpl.h"
//
DialogConnectionImpl::DialogConnectionImpl( QWidget * parent, Qt::WFlags f ) 
	: QDialog(parent, f) {
	// TODO
	setupUi(this);
}

void	DialogConnectionImpl::setModel(QSqlRelationalTableModel *m) {
	model = m;
	mapper = new QDataWidgetMapper(this);
	mapper->setModel(model);
	//mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	mapper->setItemDelegate(new QSqlRelationalDelegate(this));
	mapper->addMapping(leName, model->fieldIndex("name"));
	mapper->addMapping(sbPort, model->fieldIndex("port"));
	mapper->addMapping(leArgs, model->fieldIndex("cmdline"));
	mapper->addMapping(leComments, model->fieldIndex("comments"));
	// special
	QSqlTableModel *rm;
	// proto
	rm = model->relationModel(2);
	cbProtocol->setModel(rm);
	cbProtocol->setModelColumn(rm->fieldIndex("name"));
	mapper->addMapping(cbProtocol, 2);
	// host
	rm = model->relationModel(3);
	cbHost->setModel(rm);
	cbHost->setModelColumn(rm->fieldIndex("name"));
	mapper->addMapping(cbHost, 3);
	// var
	rm = model->relationModel(5);
	cbVar->setModel(rm);
	cbVar->setModelColumn(rm->fieldIndex("name"));
	mapper->addMapping(cbVar, 5);
}

bool	DialogConnectionImpl::Edit(QModelIndex idx) {
	setWindowTitle(tr("Edit"));
	return addedit(idx);
}

bool	DialogConnectionImpl::Add(void) {
	setWindowTitle(tr("Add"));
	int row = model->rowCount();
	model->insertRow(row);
	return addedit(model->index(row, 0));
}

bool	DialogConnectionImpl::addedit(QModelIndex idx) {
	bool retvalue = false;
	// update realtions
	((QSqlTableModel *) cbProtocol->model())->select();
	((QSqlTableModel *) cbHost->model())->select();
	((QSqlTableModel *) cbVar->model())->select();
	mapper->setCurrentModelIndex(idx);
	leName->setFocus();
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
