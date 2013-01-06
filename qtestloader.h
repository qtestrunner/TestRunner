#ifndef QTRUNNER_H
#define QTRUNNER_H

#include <QObject>
#include <QProcess>
#include <QVector>

#include "interfaces/itestloader.h"
#include "qtestsuite.h"
#include "qtestcase.h"

/** Class implement #ITestLoader for QtTestLib */
class QTestLoader: public ITestLoader
{
public:
	QTestLoader();
	~QTestLoader();

	// ITestLoader
	// Load all information about test suit
    virtual Result loadTestSuite(const QString & file_name, QSharedPointer<ITestSuite> & suit);
protected:

	/** Run qtest and fill vector of  testcases names
	 * @param file_name Absolute file name of test suite
	 * @param[out] casesname
	 * @return Result of operation
	 */
	Result loadCases(const QString & file_name, QVector<QByteArray> &casesname);

	/** Run qtest programm with arg -datatags, and fill cases with datatags
	 * @param file_name filename of executable
	 * @param[out] cases fill
	 * @return Result of operation
	 */
	Result loadDataTags(const QString & file_name, QVector<QSharedPointer<QTestCase> > & cases);

	/** Filter results from #runProcess, make them printable and delete "()"
	 * @param data Run results from #runProcess
	 */
	void filterResults(QVector<QByteArray> & data);

	/** Scan results and data tags to testcases
	 * @param cases Conteiner of #QTestCase (s)
	 * @param results results from runing qtest with -datatags(and filtered with #filterResults)
	 */
	void addDataTags(QVector<QSharedPointer<QTestCase> > & cases, const QVector<QByteArray> & results);
};

#endif // QTRUNNER_H
