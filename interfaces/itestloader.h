#ifndef ITESTLOADER_H
#define ITESTLOADER_H

#include <QSharedPointer>
#include "interfaces/ifile.h"

class ITestLoader
{
public:

	enum Result
	{
		ResultOk,
		ResultNotRunned,
		ResultCrushed,
		ResultFailed,
		ResultTimeOut
	};

	virtual ~ITestLoader(){}

	/** Load all information about test suit
	 * @param file_name Absolute file name
	 * @param[out] suit Creates qsharedpointer with suit
	 * @return Result of operation
	 */

	virtual Result loadFile(const QString & file_name, IFilePtr & file, const QStringList & environment) = 0;
};
typedef QSharedPointer<ITestLoader> ITestLoaderPtr;

#endif // ITESTLOADER_H
