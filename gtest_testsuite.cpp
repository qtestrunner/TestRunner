#include "gtest_testsuite.h"

GTest_TestSuite::GTest_TestSuite ()
{
}

GTest_TestSuite::~GTest_TestSuite (){

}

QVector<ITestCasePtr>& GTest_TestSuite::getCases ()  {
    return m_cases;
}

const QByteArray& GTest_TestSuite::getName (){
	return m_name;
}

void GTest_TestSuite::setRunnable(bool flag)
{
	m_runnable = flag;
}


void GTest_TestSuite::setName (const QByteArray& name) {
    m_name = name;
}

void GTest_TestSuite::addTestCase (ITestCasePtr testCase) {
    m_cases.push_back(testCase);
}

bool GTest_TestSuite::isRunnable()
{
	return m_runnable;
}
