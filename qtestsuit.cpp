#include "qtestsuit.h"

#include "interfaces/itestcase.h"

QTestSuit::QTestSuit()
{
}

QTestSuit::~QTestSuit()
{
}


const QByteArray & QTestSuit::getName()
{
	return m_name;
}

void QTestSuit::setName(const QByteArray &name)
{
	m_name = name;
}

QVector<QSharedPointer<ITestCase> > & QTestSuit::getCases()
{
	return m_cases;
}

void QTestSuit::setCases(const QVector<QSharedPointer<QTestCase> > & cases)
{
	m_cases.clear();
	for(auto it = cases.begin();it != cases.end(); ++it)
	{
		const QSharedPointer<QTestCase> & p = *it;
		m_cases.push_back(p.staticCast<ITestCase>());
	}
}

