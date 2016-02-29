#include "settingsimpl.h"
// cbMinOnOpen, cbUseTray, cbStartHidden, cbMinToTray
DialogSettingsImpl::DialogSettingsImpl( QWidget * parent, Qt::WFlags f ) 
	: QDialog(parent, f) {
	// TODO
	setupUi(this);
	setfile = new QSettings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
	terminal	= setfile->value("term").toString();
	minOnOpen	= setfile->value("minonopen").toBool();
	useTray		= setfile->value("usetray").toBool();
	startHidden	= setfile->value("starthidden").toBool();
	minToTray	= setfile->value("mintotray").toBool();
}

bool	DialogSettingsImpl::Go(void) {
	bool retvalue = false;
	// 1. set
	leTerm->setText(terminal);
	cbMinOnOpen->setChecked(minOnOpen);
	cbUseTray->setChecked(useTray);
	cbStartHidden->setChecked(startHidden);
	cbMinToTray->setChecked(minToTray);
	// 2. get
	if (exec() == QDialog::Accepted) {
		// 2.1. get values
		terminal	= leTerm->text();
		minOnOpen	= cbMinOnOpen->isChecked();
		useTray		= cbUseTray->isChecked();
		startHidden	= cbStartHidden->isChecked();
		minToTray	= cbMinToTray->isChecked();
		// 2.2. save them
		setfile->setValue("term", terminal);
		setfile->setValue("minonopen", minOnOpen);
		setfile->setValue("usetray", useTray);
		setfile->setValue("starthidden", startHidden);
		setfile->setValue("mintotray", minToTray);
		retvalue = true;
	}
	return retvalue;
}

//
