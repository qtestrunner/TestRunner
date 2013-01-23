#include "gtest_testcase.h"

GTest_TestCase::GTest_TestCase (const QByteArray & name)
	: m_runnable(true)
{
	m_name = name;
}

void GTest_TestCase::setRunnable(bool flag)
{
	m_runnable = flag;
}

bool GTest_TestCase::isRunnable()
{
	return m_runnable;
}

void GTest_TestCase::setRunnableDataTags(const QList<QByteArray> &tags)
{

}

const QList<QByteArray> GTest_TestCase::runnableDataTags()
{
	return QList<QByteArray>();
}
