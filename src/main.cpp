#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QtSql>
#include "mainwindowimpl.h"
//

bool	createConnection(QSqlDatabase &db)
{
	QString s = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
	QDir d(s);
	d.mkpath(s);
	db.setDatabaseName(s + QDir::separator() + "qrdc.db");
	if (!db.open()) {
		QMessageBox::critical(0,
			QObject::tr("Opening database error"),
			QObject::tr("Unable to establish a database connection."));
		return false;
	} else {
		if (db.tables().isEmpty()) {
			bool ok = false;
			QStringList list;
			QFile file(":sql/sql/data.sql");
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
				QMessageBox::critical(0, QObject::tr("Error"), QObject::tr("fail to open data.sql to read"));
				return false;
			} else {
				list = QString(file.readAll()).split("\n");
				file.close();
			}
			if (!list.isEmpty()) {
				QSqlQuery q;
				QListIterator<QString> itr (list);  
				while (itr.hasNext()) {
					QString s = itr.next();
					if (!s.isEmpty()) {
						if (!q.exec(s)) {
							QMessageBox::critical(0,
								QObject::tr("Creating database error"),
								QObject::tr("Unable to execute query: %1").arg(s));
							return false;
						} else
							ok = true;
					}
				}
				if (ok)
					QMessageBox::information(0,
						QObject::tr("Creating database"),
						QObject::tr("Database created OK"));

			} else {
				QMessageBox::critical(0,
				QObject::tr("Creating database error"),
				QObject::tr("Unable to read sql."));
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char ** argv)
{
	QApplication app( argc, argv );
	QCoreApplication::setApplicationName("qrdc");
	QCoreApplication::setApplicationVersion("0.0.1");
	QCoreApplication::setOrganizationName("TI_Eugene");
	QCoreApplication::setOrganizationDomain("eap.su");
	// <tr>
	QTranslator appTranslator;
	QString trpath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);	// /usr/share/qt4/translations
	QString trfile = QCoreApplication::applicationName() + "_" + QLocale::system().name().left(2);
	if (not QFile::exists(trpath + QDir::separator() + trfile + ".qm"))
		trpath = app.applicationDirPath() + QDir::separator() + "i18n";
	appTranslator.load(trpath + QDir::separator() + trfile);
	app.installTranslator(&appTranslator);
	// </tr>
	// <db>
	QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
	if (!createConnection(db))
		return 1;
	// </db>
	MainWindowImpl *win = new MainWindowImpl();
	win->setModels(&db);
	win->go(); 
	app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
	int retvalue = app.exec();
	delete win;
	db.close();
	return retvalue;
}
