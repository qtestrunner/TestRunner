#include <QDebug>

#include "qtestcase.h"

//------------------------------------------------------------------------------
//Constructor with name parametr
QTestCase::QTestCase(const QByteArray & name)
	: m_name(name)
{

}

//------------------------------------------------------------------------------
//Sets data tags vector for this test case
void QTestCase::setDataTags(const QVector<QByteArray> & datatags)
{
	m_datatags = datatags;
}

//------------------------------------------------------------------------------
//Prints information about test case, only for debug
void QTestCase::print()
{
	qDebug() << "name" << m_name;
	foreach(QByteArray data, m_datatags)
	{
		qDebug() << "tag" << data;
	}
}

//------------------------------------------------------------------------------
//Returns test case name
const QByteArray &QTestCase::getName()
{
	return m_name;
}

//------------------------------------------------------------------------------
//Return vector of test case data tags
const QVector<QByteArray> &QTestCase::getDataTags()
{
	return m_datatags;
}

//------------------------------------------------------------------------------
QTestCase::QTestCase()
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
