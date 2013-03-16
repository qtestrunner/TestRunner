#include "gtest_loader.h"
#include <interfaces/itestloader.h>
#include "gtest_testcase.h"
#include "gtest_testsuite.h"
#include <QStringList>
#include "gtest_file.h"

GTest_Loader::~GTest_Loader(){

}

ITestLoader::Result GTest_Loader::loadFile(const QString &file_name, IFilePtr &file, const QStringList &environment){

    ITestCasePtr testcase;
    QList<QString> listResult;
    QList<ITestSuitePtr> gtest_suites;
    QStringList args;
    ITestSuitePtr google_suite;

    args << "--gtest_list_tests";

    file->setAbsFileName(file_name);

    Utils::runProcess(file_name, args, listResult);
    DEBUG(QString("Gtest detected"));
    foreach(QString line, listResult){
        // if there is no spaces - than it is testsuitename
        if (line[0] != ' '){
            google_suite = ITestSuitePtr(new GTest_TestSuite);
            google_suite->setName(line.remove(QRegExp("[.]|\n"))); // remove dot and \n at the end of line
            gtest_suites.push_back(google_suite);
        }
        else{
            // this removes first two spaces
            testcase = ITestCasePtr(new GTest_TestCase(line.remove(QRegExp("\n|[ ]"))));
            google_suite->addTestCase(testcase);
        }
    }


    GTest_FilePtr gfile(new GTest_File());
    gfile->setTestSuites(gtest_suites);
    file = gfile.staticCast<IFile>();
	return ResultOk;
}
