#include "qtestcase.h"
#include "utils/log.h"

//------------------------------------------------------------------------------
//Constructor with name parametr
QTestCase::QTestCase(const QString & name)
	: m_name(name)
	, m_runnable(true)
{
}

//------------------------------------------------------------------------------
//Sets data tags vector for this test case
void QTestCase::setDataTags(const QList<QString> & datatags)
{
	m_datatags = datatags;
	m_runnabletags = datatags;
}

//------------------------------------------------------------------------------
//Prints information about test case, only for debug
void QTestCase::print()
{
	DEBUG((QString("name=") + m_name));
	foreach(QString data, m_datatags)
	{
		DEBUG((QString("tag=") + data));
	}
}

//------------------------------------------------------------------------------
//Returns test case name
const QString &QTestCase::getName()
{
	return m_name;
}

void QTestCase::setRunnableDataTags(const QList<QString> & tags)
{
	m_runnabletags.clear();
	foreach(const QString & tag, tags)
	{
		if (m_datatags.contains(tag))
			m_runnabletags.push_back(tag);
	}
	if (m_runnabletags.isEmpty())
		m_runnable = false;
	else
		m_runnable = true;
}

const QList<QString> QTestCase::runnableDataTags()
{
	return m_runnabletags;
}

//------------------------------------------------------------------------------
//Return vector of test case data tags
const QList<QString> QTestCase::getAllDataTags()
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
