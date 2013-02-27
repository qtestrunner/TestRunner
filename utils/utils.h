#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QVector>
#include <QString>
#include <QStringList>

namespace Utils
{
	/** Run process, with args and save results,
	 * @param file_name filename of executable
	 * @param args args to executable
	 * @param[out] results stdout and stderr of execute, each
	 * @param timeout process time out
	 * @return Result of operation, may failed with timeout
	 */
	bool runProcess(const QString &file_name, const QStringList & args, QList<QString> &results, int timeout = 10000,  const QStringList &environment = QStringList() );

	bool runProcess(const QString &file_name, const QStringList & args, QString & results, int timeout = 10000,  const QStringList &environment = QStringList());
}
#endif // UTILS_H
