#include <QProcess>
#include <QDebug>

#include "utils.h"

namespace Utils
{
	const int max_str_len = 1000; ///< Max str length while reading

	//--------------------------------------------------------------------------
	// Run process, with args and save results
	bool runProcess(const QString &file_name, const QStringList & args, QVector<QByteArray> &results, int timeout)
	{
		QProcess process;
		process.setProcessChannelMode(QProcess::MergedChannels);
		process.start(file_name, args);
		if(!process.waitForFinished(timeout))
		{
			qDebug() << "run process fail:" << process.readAll();
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
