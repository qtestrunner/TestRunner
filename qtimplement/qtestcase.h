#ifndef QTESTCASE_H
#define QTESTCASE_H

#include <QtCore>
#include <interfaces/itestcase.h>

class QTestCase: public ITestCase
{
    QString m_name; ///< Name of test case
    QList<QString> m_datatags;///< Vector of data tags
	bool m_runnable;
    QList<QString> m_runnabletags;
public:
	QTestCase();
	~QTestCase();

	/** Constructor with name parametr
	 * @param m_name Name of test case
	 */
    explicit QTestCase(const QString & m_name);

	/** Sets data tags vector for this test case
	 * @param datatags Vector of data tags
	 */
    void setDataTags(const QList<QString> &datatags);

	//ITestCase
	/** Prints information about test case, only for debug */
	virtual void print();

	/** Indicate if test case have data tags */
	virtual bool hasDataTags();

	virtual void setRunnable(bool flag);

	virtual bool isRunnable();

    virtual void setRunnableDataTags(const QList<QString> & tags);

    virtual const QList<QString> runnableDataTags();

	/** Returns test case name */
    virtual const QString & getName();

	/** Return vector of test case data tags */
    virtual const QList<QString> getAllDataTags();
};

typedef QSharedPointer<QTestCase> QTestCasePtr;

#endif // QTESTCASE_H
