#ifndef ITESTSUIT_H
#define ITESTSUIT_H

#include <QVector>
#include <QSharedPointer>

#include <interfaces/itestcase.h>

class ITestSuite
{
public:

	virtual ~ITestSuite(){};

	/** Return name of test suite
	 * @return name of test suite
	 */
	virtual const QByteArray & getName() = 0;

	/** Return vector of test cases
	 * @return vector of test cases
	 */
	virtual QVector<QSharedPointer<ITestCase> > & getCases() = 0;
};
#endif // ITESTSUIT_H
