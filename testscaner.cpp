#include <QDir>
#include <QDebug>

#include "testscaner.h"

void TestScaner::scanFolder(const QString & folder, const QStringList & masks)
{
	QDir dir(folder);
	QStringList files = dir.entryList(masks, QDir::Executable | QDir::Files, QDir::Name);
	foreach(QString name, files)
	{
		qDebug() << name;
	}
}
