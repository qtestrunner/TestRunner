#include "gtest_testsuite.h"

GTest_TestSuite::GTest_TestSuite ()
{
}

GTest_TestSuite::~GTest_TestSuite (){

}

QList<ITestCasePtr>& GTest_TestSuite::getCases()  {
    return m_cases;
}

const QString& GTest_TestSuite::getName (){
	return m_name;
}

void GTest_TestSuite::setRunnable(bool flag)
{
	m_runnable = flag;
}


void GTest_TestSuite::setName (const QString& name) {
    m_name = name;
}

void GTest_TestSuite::addTestCase (ITestCasePtr testCase) {
    m_cases.push_back(testCase);
}

bool GTest_TestSuite::isRunnable()
{
	return m_runnable;
}
