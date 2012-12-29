#include "qtestcase.h"
#include <QDebug>

QTestCase::QTestCase(const QByteArray & name)
	: m_name(name)
{

}

void QTestCase::setDataTags(const QVector<QByteArray> & datatags)
{
	m_datatags = datatags;
}

void QTestCase::print()
{
	qDebug() << "name" << m_name;
	foreach(QByteArray data, m_datatags)
	{
		qDebug() << "tag" << data;
	}
}

const QByteArray &QTestCase::getName()
{
	return m_name;
}

const QVector<QByteArray> &QTestCase::getDataTags()
{
	return m_datatags;
}


QTestCase::QTestCase()
{
}

QTestCase::~QTestCase()
{
}

bool QTestCase::hasDataTags()
{
	return true;
}
