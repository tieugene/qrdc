#include "varimpl.h"
//
DialogVarImpl::DialogVarImpl( QWidget * parent, Qt::WFlags f ) 
	: DialogImpl(parent, f) {
	// TODO
	setupUi(this);
	firstWidget = leName;
}

void	DialogVarImpl::setModel(QSqlTableModel *m) {
	prepareModel(m);
	mapper->addMapping(leName, model->fieldIndex("name"));
	mapper->addMapping(leValue, model->fieldIndex("val"));
}
//
