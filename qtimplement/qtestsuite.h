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
	QList<ITestCasePtr> m_cases; ///< Array of test cases
	bool m_runnable;
public:
	QTestSuite();
	~QTestSuite();

	/** Sets array of cases
	 * @param cases Array of cases
	 */
	void setCases(const QList<QTestCasePtr> &cases);

	/** Sets name of suite
	 * @param name new name of suite
	 */
	virtual	void setName(const QByteArray &name);

	//ITestSuite:
	/** Returns name os test suite */
	virtual const QByteArray & getName();


	virtual void setRunnable(bool flag);

	virtual bool isRunnable();

	/** Returns array of test ceses */
    virtual QList<ITestCasePtr>& getCases();

	void addQTestCase(QTestCasePtr testCase);

	virtual void addTestCase(ITestCasePtr testCase);//FIXME:deprecated
};

typedef QSharedPointer<QTestSuite> QTestSuitePtr;

#endif // QTESTSUIT_H
