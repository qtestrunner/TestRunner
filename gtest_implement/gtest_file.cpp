#include "gtest_file.h"

void GTest_File::setAbsFileName(const QString & absname){
    m_filename  = absname;
}

void GTest_File::run(QList<TestSuiteResult> & results){
    Q_ASSERT_X(false, "Not Implemented Yet","ViacheslavL");
}

QList<ITestSuitePtr> GTest_File::getTestSuites(){
    return m_testsuites;
}

void GTest_File::setTestSuites(QList<ITestSuitePtr> testsuites){
    m_testsuites = testsuites;
}
