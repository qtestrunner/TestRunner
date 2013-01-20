#ifndef QTESTCASE_H
#define QTESTCASE_H

#include <QtCore>
#include <interfaces/itestcase.h>

class QTestCase: public ITestCase
{
	QByteArray m_name; ///< Name of test case
	QVector<QByteArray> m_datatags;///< Vector of data tags
	bool m_runnable;
public:
	QTestCase();
	~QTestCase();

	/** Constructor with name parametr
	 * @param m_name Name of test case
	 */
	explicit QTestCase(const QByteArray & m_name);

	/** Sets data tags vector for this test case
	 * @param datatags Vector of data tags
	 */
	void setDataTags(const QVector<QByteArray> & datatags);

	//ITestCase
	/** Prints information about test case, only for debug */
	virtual void print();

	/** Indicate if test case have data tags */
	virtual bool hasDataTags();

	virtual void setRunnable(bool flag);

	virtual bool isRunnable();

	/** Returns test case name */
	virtual const QByteArray & getName();

	/** Return vector of test case data tags */
	virtual const QVector<QByteArray> & getDataTags();
};

typedef QSharedPointer<QTestCase> QTestCasePtr;

#endif // QTESTCASE_H
