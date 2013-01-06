#ifndef GTEST_TESTSUITE_H
#define GTEST_TESTSUITE_H

#include <interfaces/itestsuite.h>

/*!
 * \brief The GTest_TestSuite class
 */
class GTest_TestSuite : public ITestSuite
{
    QByteArray m_name;
    QVector<ITestCasePtr> m_cases;
public:

    /*! \brief GTest_TestSuite - Constructor */
    GTest_TestSuite();

    /*!  \brief GTest_TestSuite - Destructor */
    ~GTest_TestSuite();

    /*!
     * \brief setCases
     * \param cases - array of smart pointers to ITestCase
     */
    void setCases(const QVector<ITestCasePtr > & cases);

    /*!
     * \brief setName - method sets name of TestSuite
     * \param name -
     */
    void setName(const QByteArray &name);

    const QByteArray & getName();
    QVector<ITestCasePtr> & getCases();
};

typedef QSharedPointer<GTest_TestSuite> GT_TestSuitePtr;

#endif // GTEST_TESTSUITE_H