#include "protocolimpl.h"
//
DialogProtocolImpl::DialogProtocolImpl( QWidget * parent, Qt::WFlags f ) 
	: DialogImpl(parent, f) {
	// TODO
	setupUi(this);
	firstWidget = leName;
}

void	DialogProtocolImpl::setModel(QSqlTableModel *m) {
	prepareModel(m);
	mapper->addMapping(leName, model->fieldIndex("name"));
	mapper->addMapping(leExec, model->fieldIndex("programm"));
	mapper->addMapping(sbPort, model->fieldIndex("port"));
	mapper->addMapping(cbTerm, model->fieldIndex("term"));
	mapper->addMapping(leCmdLine, model->fieldIndex("cmdline"));
}

//
