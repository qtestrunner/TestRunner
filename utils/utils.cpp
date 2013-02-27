#include <QProcess>

#include "utils.h"
#include "utils/log.h"

namespace Utils
{
	const int max_str_len = 10000; ///< Max str length while reading

	bool runProcess(const QString &file_name, const QStringList & args, QString & results, int timeout, const QStringList & environment)
	{
		QProcess process;
		if (!environment.isEmpty())
			process.setEnvironment(environment);
		process.setProcessChannelMode(QProcess::MergedChannels);
		process.start(file_name, args);
		if(!process.waitForFinished(timeout))
		{
			DEBUG(QString("run process fail:") + process.readAll());
			return false;
		}

		results = process.readAll();
		return true;

	}

	//--------------------------------------------------------------------------
	// Run process, with args and save results
	bool runProcess(const QString &file_name, const QStringList & args, QList<QString> &results, int timeout, const QStringList & environment)
	{
		QProcess process;
		if (!environment.isEmpty())
			process.setEnvironment(environment);
		process.setProcessChannelMode(QProcess::MergedChannels);
		process.start(file_name, args);
		if(!process.waitForFinished(timeout))
		{
			DEBUG(QString("run process fail:") + process.readAll());
			return false;
		}

		int rbt = -1;
		do
		{
			char data[max_str_len];

			rbt = process.readLine(data, max_str_len);
			if (rbt > 0)
			{
				results.push_back(data);
			}
		}
		while(rbt != -1);
		return true;
	}
}
