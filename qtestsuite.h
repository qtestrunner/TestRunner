#ifndef QTESTSUIT_H
#define QTESTSUIT_H

#include <QSharedPointer>
#include <QByteArray>

#include "interfaces/itestsuite.h"
#include "qtestcase.h"

/** Class implemet #ITestSuite for QtTestLib */
class QTestSuite: public ITestSuite
{
	QByteArray m_name; ///< Test Suite name
	QVector<QSharedPointer<ITestCase> > m_cases; ///< Array of test cases
public:
	QTestSuite();
	~QTestSuite();

	/** Sets array of cases
	 * @param cases Array of cases
	 */
	void setCases(const QVector<QSharedPointer<QTestCase> > & cases);

	/** Sets name of suite
	 * @param name new name of suite
	 */
	void setName(const QByteArray &name);

	//ITestSuite:
	/** Returns name os test suite */
	virtual const QByteArray & getName();

	/** Returns array of test ceses */
	virtual QVector<QSharedPointer<ITestCase> > & getCases();

    void addTestCase(ITestCasePtr testCase);

};

typedef QSharedPointer<QTestSuite> QTestSuitePtr;

#endif // QTESTSUIT_H
