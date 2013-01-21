#ifndef GTEST_TESTCASE_H
#define GTEST_TESTCASE_H

#include <interfaces/itestcase.h>
#include <iostream>
#include <utils/log.h>

class GTest_TestCase : public ITestCase
{
    QByteArray m_name ;
	QList<QByteArray> m_null;
	bool m_runnable;
public:
    /*!
     *  \brief GTest_TestCase - Constructor
     *  \param name - name of created testcase
     */
    explicit GTest_TestCase (const QByteArray & name);

    void print(){
        DEBUG((QString("name=") + m_name));
    }

    const QByteArray & getName(){
        return m_name;
    }

    bool hasDataTags(){
        return false;
    }

	virtual void setRunnable(bool flag);

	virtual bool isRunnable();

	const QList<QByteArray> getDataTags(){
        Q_ASSERT_X(false, "NOT ALLOWED","ViacheslavL");
        return m_null;
    }
};

typedef QSharedPointer<GTest_TestCase> GT_TestCasePtr;

#endif // GTEST_TESTCASE_H
