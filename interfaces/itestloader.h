#ifndef ITESTLOADER_H
#define ITESTLOADER_H

#include <QSharedPointer>

#include "interfaces/itestsuite.h"

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

	virtual ~ITestLoader(){};

	/** Load all information about test suit
	 * @param file_name Absolute file name
	 * @param[out] suit Creates qsharedpointer with suit
	 * @return Result of operation
	 */
	virtual Result loadTestSuit(const QString & file_name, QSharedPointer<ITestSuite> & suit) = 0;
};

#endif // ITESTLOADER_H
