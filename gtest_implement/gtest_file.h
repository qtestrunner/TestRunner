#ifndef GTEST_FILE_H
#define GTEST_FILE_H

#include <interfaces/ifile.h>

class GTest_File : public IFile{
public:
    void setAbsFileName(const QString & absname);

    void run(QList<TestSuiteResult> & results);

    QList<ITestSuitePtr> getTestSuites();

    void setTestSuites(QList<ITestSuitePtr> testsuites);

private:
    QString m_filename;
    QList<ITestSuitePtr> m_testsuites;
};

typedef QSharedPointer<GTest_File> GTest_FilePtr;

#endif // GTEST_FILE_H
