#ifndef GTEST_TESTCASE_H
#define GTEST_TESTCASE_H

#include <interfaces/itestcase.h>
#include <iostream>
#include <utils/log.h>

class GTest_TestCase : public ITestCase
{
    QString m_name ;
    QList<QString> m_null;
	bool m_runnable;
public:
    /*!
     *  \brief GTest_TestCase - Constructor
     *  \param name - name of created testcase
     */
    explicit GTest_TestCase (const QString & name);

    void print(){
        DEBUG((QString("name=") + m_name));
    }

    const QString & getName(){
        return m_name;
    }

    bool hasDataTags(){
        return false;   ///  Google Test has No DataTags
    }

	virtual void setRunnable(bool flag);

	virtual bool isRunnable();

    virtual void setRunnableDataTags(const QList<QString> & tags);

    const QList<QString> runnableDataTags();

    const QList<QString> getAllDataTags(){
        Q_ASSERT_X(false, "NOT ALLOWED","ViacheslavL");
        return m_null;
    }
};

typedef QSharedPointer<GTest_TestCase> GT_TestCasePtr;

#endif // GTEST_TESTCASE_H
