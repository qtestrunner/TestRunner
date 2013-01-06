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
