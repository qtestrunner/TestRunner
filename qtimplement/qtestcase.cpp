#include "qtestcase.h"
#include "utils/log.h"

//------------------------------------------------------------------------------
//Constructor with name parametr
QTestCase::QTestCase(const QByteArray & name)
	: m_name(name)
	, m_runnable(true)
{
}

//------------------------------------------------------------------------------
//Sets data tags vector for this test case
void QTestCase::setDataTags(const QList<QByteArray> & datatags)
{
	m_datatags = datatags;
}

//------------------------------------------------------------------------------
//Prints information about test case, only for debug
void QTestCase::print()
{
	DEBUG((QString("name=") + m_name));
	foreach(QByteArray data, m_datatags)
	{
		DEBUG((QString("tag=") + data));
	}
}

//------------------------------------------------------------------------------
//Returns test case name
const QByteArray &QTestCase::getName()
{
	return m_name;
}

void QTestCase::setRunnableDataTags(const QList<QByteArray> & tags)
{
	m_runnabletags.clear();
	foreach(const QByteArray & tag, tags)
	{
		if (m_datatags.contains(tag))
			m_runnabletags.push_back(tag);

	}
}

const QList<QByteArray> QTestCase::runnableDataTags()
{
	if (m_runnabletags.isEmpty())
		return m_datatags;
	else
		return m_runnabletags;
}

//------------------------------------------------------------------------------
//Return vector of test case data tags
const QList<QByteArray> QTestCase::getAllDataTags()
{
	return m_datatags;
}

//------------------------------------------------------------------------------
QTestCase::QTestCase()
	: m_runnable(true)
{
}

//------------------------------------------------------------------------------
QTestCase::~QTestCase()
{
}

//------------------------------------------------------------------------------
//Indicate if test case have data tags
bool QTestCase::hasDataTags()
{
	return !m_datatags.isEmpty();
}

void QTestCase::setRunnable(bool flag)
{
	m_runnable = flag;
}

bool QTestCase::isRunnable()
{
	return m_runnable;
}
