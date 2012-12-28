#include "qtrunner.h"

#include <QDebug>

QtRunner::QtRunner(QObject *parent) :
	QObject(parent)
{
}

void filterCases(char * data, int size)
{
	for (int i = 0; i < size; ++i)
	{
		char c = data[i];
		if ((c < 20) || c == '\n' || c == '\r' || c == ')' || c == '(')
			data[i] = 0;
	}
}

QtRunner::Result QtRunner::getTestCases(const QString & file_name, QStringList & cases)
{
	QStringList args;
	args << "-functions";
	QProcess process;
	process.setProcessChannelMode(QProcess::MergedChannels);
	process.start(file_name, args);
	bool rez = process.waitForFinished();

	if (!rez)
		return ResultTimeOut;

	qint64 msize = 100;
	int rbt = -1;
	do
	{
		char data[100];

		rbt = process.readLine(data, msize);
		if (rbt > 0)
		{
			filterCases(data, msize);
			cases << data;
		}
	}
	while(rbt != -1);

	return ResultOk;
}

QtRunner::Result QtRunner::runTest(const QString &name)
{
	QStringList args;
	args << "-functions";
	QProcess process;
	process.setProcessChannelMode(QProcess::MergedChannels);
	process.start(name, args);
	bool rez = process.waitForFinished();

	QByteArray buffer = process.readAll();

	qDebug() << "!" << buffer;
	if (!rez)
		return ResultTimeOut;

	return ResultOk;
}
