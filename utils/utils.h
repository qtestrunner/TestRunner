#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QVector>
#include <QString>

namespace Utils
{
	/** Run process, with args and save results,
	 * @param file_name filename of executable
	 * @param args args to executable
	 * @param results stdout and stderr of execute, each
	 * @return Result of operation, may failed with timeout
	 */
	bool runProcess(const QString &file_name, const QStringList & args, QVector<QByteArray> &results, int timeout = 10000);
}
#endif // UTILS_H
