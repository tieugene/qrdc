#include "mainwindowimpl.h"
//

void	MainWindowImpl::onActionBackup(void)
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save file"), QString(), tr("Text files (*.txt)"));
	if (!filename.isEmpty()) {
		QFile *file = new QFile(filename);
		if (file->open(QIODevice::ReadWrite | QIODevice::Text)) {
			QTextStream outf(file);
			QSqlQuery q;
			// 1. Protocols
			q.exec("SELECT * FROM p");
			while (q.next())
				outf << QString("p\t%1\t%2\t%3\t%4\t%5\t%6\n").arg(
					q.value(0).toString(),
					q.value(1).toString(),
					q.value(2).toString(),
					q.value(3).toString(),
					q.value(4).toString(),
					q.value(5).toString());
			// 2. Vars
			q.exec("SELECT * FROM v");
			while (q.next())
				outf << QString("v\t%1\t%2\t%3\n").arg(
					q.value(0).toString(),
					q.value(1).toString(),
					q.value(2).toString());
			// 3. Hosts
			q.exec("SELECT * FROM h");
			while (q.next())
				outf << QString("h\t%1\t%2\t%3\n").arg(
					q.value(0).toString(),
					q.value(1).toString(),
					q.value(2).toString());
			// 4. Connections
			q.exec("SELECT * FROM c");
			while (q.next())
				outf << QString("c\t%1\t%2\t%3\t%4\t%5\t%6\t%7\t%8\n").arg(
					q.value(0).toString(),
					q.value(1).toString(),
					q.value(2).toString(),
					q.value(3).toString(),
					q.value(4).toString(),
					q.value(5).toString(),
					q.value(7).toString(),
					q.value(8).toString());
			// the end
			file->close();
		} else
			QMessageBox::critical(0, tr("Error"), tr("Fail to open backup file to write"));
	}
}

void	MainWindowImpl::onActionRestore(void)
{
	if (QMessageBox::question(this, tr("Restore database"), tr("Your data will be replaced. Are you sure?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {
		QString filename = QFileDialog::getOpenFileName(0, tr("Load file"), QString(), tr("Text files (*.txt)"));
		if (!filename.isEmpty()) {
			QFile *file = new QFile(filename);
			if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
				QStringList list = QString(file->readAll()).split("\n");
				QStringList line;
				QSqlRecord r;
				file->close();
				if (!list.isEmpty()) {
					db->transaction();
					modelC->removeRows(0, modelC->rowCount());
					modelP->removeRows(0, modelP->rowCount());
					modelV->removeRows(0, modelV->rowCount());
					modelH->removeRows(0, modelH->rowCount());    
					QListIterator<QString> itr (list);  
					while (itr.hasNext()) {
						QString s =  itr.next();
						if (!s.isEmpty()) {
							line = s.split("\t");
							//qDebug() << line;
							if (line[0] == "h") {	// + and len == ...
								r = modelH->record();
								r.setValue("id", line[1].toLongLong());
								r.setValue("name", line[2]);
								r.setValue("val", line[3]);
								modelH->insertRecord(-1, r);
							} else if (line[0] == "v") {
								r = modelV->record();
								r.setValue("id", line[1].toLongLong());
								r.setValue("name", line[2]);
								r.setValue("val", line[3]);
								modelV->insertRecord(-1, r);
							} else if (line[0] == "p") {
								r = modelP->record();
								r.setValue("id", line[1].toLongLong());
								r.setValue("name", line[2]);
								r.setValue("programm", line[3]);
								r.setValue("port", line[4].toInt());
								r.setValue("term", line[5] == "true");
								r.setValue("cmdline", line[6]);
								modelP->insertRecord(-1, r);
							} else if (line[0] == "c") {
								r = modelC->record();
								// !!! add related fields !!!
								r.append(QSqlField("protoid", QVariant::LongLong));
								r.append(QSqlField("hostid", QVariant::LongLong));
								r.append(QSqlField("varid", QVariant::LongLong));
								//r.setValue("id", line[1].toLongLong());
								r.setValue("name", line[1]);
								r.setValue("protoid", line[2].toLongLong());
								r.setValue("hostid", line[3].toLongLong());
								r.setValue("port", line[4].toInt());
								r.setValue("varid", line[5].toLongLong());
								r.setValue("cmdline", line[6]);
								r.setValue("comments", line[7]);
								modelC->insertRecord(-1, r);
							}
						}
					}
					if (!db->commit()) {
						db->rollback();
						QMessageBox::critical(this, tr("Error"), tr("Can't commit transaction"));
					}
					file->close();
				}  else
					QMessageBox::critical(this, tr("Error"), tr("0 bytes read"));
			} else
				QMessageBox::critical(this, tr("Error"), tr("Fail to open backup file to read"));
		}
	}
}

//
