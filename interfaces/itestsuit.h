#ifndef ITESTSUIT_H
#define ITESTSUIT_H

#include <QVector>
#include <QSharedPointer>

#include <interfaces/itestcase.h>

class ITestSuite
{
public:

	virtual ~ITestSuite(){};
	virtual const QByteArray & getName() = 0;
	/**
	 * @return
	 */
	virtual QVector<QSharedPointer<ITestCase> > & getCases() = 0;
};
#endif // ITESTSUIT_H
