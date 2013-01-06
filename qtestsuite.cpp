#include "interfaces/itestcase.h"
#include "qtestsuite.h"

//------------------------------------------------------------------------------
QTestSuite::QTestSuite()
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

//------------------------------------------------------------------------------
// Sets name of suite
void QTestSuite::setName(const QByteArray &name)
{
	m_name = name;
}

//------------------------------------------------------------------------------
// Returns array of test ceses
QVector<QSharedPointer<ITestCase> > & QTestSuite::getCases()
{
	return m_cases;
}

//------------------------------------------------------------------------------
// Sets array of cases
void QTestSuite::setCases(const QVector<QTestCasePtr> & cases)
{
	m_cases.clear();
    for(QVector<QTestCasePtr>::const_iterator  it = cases.begin();it != cases.end(); ++it)
	{
		const QSharedPointer<QTestCase> & p = *it;
		m_cases.push_back(p.staticCast<ITestCase>());
	}
}

