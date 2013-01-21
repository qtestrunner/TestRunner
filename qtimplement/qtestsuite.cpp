#include "interfaces/itestcase.h"
#include "qtestsuite.h"

//------------------------------------------------------------------------------
QTestSuite::QTestSuite()
	: m_runnable(true)
{
}

//------------------------------------------------------------------------------
QTestSuite::~QTestSuite()
{
}

//------------------------------------------------------------------------------
// Returns name os test suite
const QByteArray & QTestSuite::getName()
{
	return m_name;
}

void QTestSuite::setRunnable(bool flag)
{
	m_runnable = flag;
}

bool QTestSuite::isRunnable()
{
	return m_runnable;
}

//------------------------------------------------------------------------------
// Sets name of suite
void QTestSuite::setName(const QByteArray &name)
{
	m_name = name;
}

//------------------------------------------------------------------------------
// Returns array of test ceses
QList<ITestCasePtr> QTestSuite::getCases()
{
	return m_cases;
}

void QTestSuite::addQTestCase(QTestCasePtr testCase)
{
	m_cases.push_back(testCase.staticCast<ITestCase>());
}

//------------------------------------------------------------------------------
// Sets array of cases
void QTestSuite::setCases(const QList<QTestCasePtr> & cases)
{
	m_cases.clear();
	for(QList<QTestCasePtr>::const_iterator  it = cases.begin();it != cases.end(); ++it)
	{
		const QTestCasePtr & p = *it;
		m_cases.push_back(p.staticCast<ITestCase>());
	}
}

void QTestSuite::addTestCase (ITestCasePtr testCase)
{
	Q_ASSERT(false);//FIXME:for delete
}

