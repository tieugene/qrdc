/*
This file was automatically generated by configure script.
All the changes you made will be lost after the next run
of configure script.
*/

#ifndef _APP_INFO_WIN_H_
#define _APP_INFO_WIN_H_

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QString>



class AppInfo {
public:
	static QString name()            { return "JuffEd"; }
	static QString organization()    { return "Juff"; }
	static QString configDirPath()   { return QDir::homePath() + "/.config/" + organization().toLower(); }
	static QString configFile()      { return configDirPath() + "/" + name().toLower() + ".conf"; }
	static QString translationPath() { return appDirPath() + "/l10n"; }
	static QString version()         { return "@JUFFED_VERSION@"; }
	static QString logFile()         { return configDirPath() + "/juffed.log"; }

	static QString socketPath()      { return "/tmp/juffed"; }
	static QString appDirPath()      { return QCoreApplication::applicationDirPath(); }
};

#endif
