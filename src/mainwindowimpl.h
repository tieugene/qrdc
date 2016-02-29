#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include <QtSql>
#include "ui_mainwindow.h"
#include "connectionimpl.h"
#include "hostimpl.h"
#include "protocolimpl.h"
#include "varimpl.h"
#include "settingsimpl.h"
//

enum	LISTTYPE	{
	PROTO,
	VAR,
	HOST,
	CONNECTION
};

class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	void				setModels(QSqlDatabase *);
	void				go(void);
private slots:
	void				onActionExit(void);
	void				onActionConnections(void);
	void				onActionHosts(void);
	void				onActionVariables(void);
	void				onActionProtocols(void);
	void				onActionOpen(void);
	void				onActionAdd(void);
	void				onActionEdit(void);
	void				onActionDel(void);
	void				onActionSettings(void);
	void				onActionBackup(void);
	void				onActionRestore(void);
	void				onActionAbout(void);
	void				onActionAboutQt(void);
	void				onActionHelp(void);
	void				onTray(const QSystemTrayIcon::ActivationReason);
	void				onHideRestore(void);
private:
	LISTTYPE			currentList;
	void				setSlots(void);
	void				setIcons(void);
	void				doUpdate(void);
	void				createTrayIcon(void);
	void				hideEvent ( QHideEvent *);
	QSqlDatabase			*db;
	QSqlRelationalTableModel	*modelC;
	QSqlTableModel			*modelP, *modelV, *modelH;
	DialogConnectionImpl		*dialogC;
	DialogHostImpl			*dialogH;
	DialogProtocolImpl		*dialogP;
	DialogVarImpl			*dialogV;
	DialogSettingsImpl		*settings;
	QSystemTrayIcon			*tray;
	QMenu				*trayMenu;
	QAction				*actionHideRestore;
};
#endif
