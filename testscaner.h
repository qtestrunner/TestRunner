#ifndef TESTSCANER_H
#define TESTSCANER_H

#include <QString>
#include <QList>
#include <QSharedPointer>

#include "interfaces/itestsuit.h"
class TestScaner
{
	static void scanFolder(const QString & folder, const QStringList &masks);
public:
	static void loadFolder(const QString & folder, QList<QSharedPointer<ITestSuit> > & testsuites);
};

#endif // TESTSCANER_H
