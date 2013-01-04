#ifndef ITESTCASE_H
#define ITESTCASE_H

#include <QByteArray>
#include <QVector>

class ITestCase
{
public:
	virtual ~ITestCase(){};

	/** Prints information about test case, only for debug
	 */
	virtual void print() = 0;

	/**Returns test case name
	 * @return Test case name
	 */
	virtual const QByteArray & getName() = 0;

	/** Indicate if test case have data tags
	 * @return
	 */
	virtual bool hasDataTags() = 0;

	/** Return vector of test case data tags
	 * @return vector of data tags
	 */
	virtual const QVector<QByteArray> & getDataTags() = 0;
};

#endif // ITESTCASE_H
