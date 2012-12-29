#ifndef ITESTLOADER_H
#define ITESTLOADER_H

#include <QSharedPointer>

#include "interfaces/itestsuit.h"

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
	virtual Result loadTestSuit(const QString & file_name, QSharedPointer<ITestSuit> & suit) = 0;
};

#endif // ITESTLOADER_H
