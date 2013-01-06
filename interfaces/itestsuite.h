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

    /** Sets name of test suite
     * @param name of test suite
     */
    virtual void setName(const QByteArray& name) = 0;

	/** Return vector of test cases
	 * @return vector of test cases
	 */
	virtual QVector<QSharedPointer<ITestCase> > & getCases() = 0;

    /** Adds testcase to current suite
     * @param testCase pointer to testcase
     */
    virtual void addTestCase(ITestCasePtr testCase) = 0;
};

typedef QSharedPointer<ITestSuite> ITestSuitePtr;
#endif // ITESTSUIT_H
