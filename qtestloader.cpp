
#include <QSharedPointer>
#include <QFile>

#include "qtestloader.h"
#include "utils/utils.h"

//------------------------------------------------------------------------------
QTestLoader::QTestLoader()
{
}

//------------------------------------------------------------------------------
QTestLoader::~QTestLoader()
{
}

//------------------------------------------------------------------------------
// Filter results from #runProcess, make them printable and delete "()"
void QTestLoader::filterResults(QVector<QByteArray> & data)
{
	auto end = data.end();
	for (auto it = data.begin(); it != end; ++it)
	{
		QByteArray & arr = *it;
		for (int i = 0; i < arr.size(); ++i)
		{
			char c  = arr[i];
			if ((c < 20) || c == '\n' || c == '\r' || c == ')' || c == '(')
			{
				arr.resize(i);
				break;
			}
		}
	}
}

//------------------------------------------------------------------------------
// Scan results and data tags to testcases
void QTestLoader::addDataTags(QVector<QSharedPointer<QTestCase> > & cases, const QVector<QByteArray> & results)
{
	QVector<QByteArray> tags;
	for (auto it = cases.begin(); it != cases.end(); ++it)
	{

		const QByteArray & name = (*it)->getName();
		foreach(QByteArray line, results)
		{

			int indx = line.indexOf(name);
			if (indx != -1)
			{
				QByteArray tag = line.mid(indx + 1 +  name.size(), line.size() - indx - name.size() - 1);
				if (!tag.isEmpty())
					tags.push_back(tag);
			}
		}
		(*it)->setDataTags(tags);
	}
}

//------------------------------------------------------------------------------
//Load all information about test suit
QTestLoader::Result QTestLoader::loadTestSuit(const QString & file_name, QSharedPointer<ITestSuite> & suit)
{
	QVector<QByteArray> caselist;

	QFileInfo fileinfo(file_name);
	if (fileinfo.size() == 0)
		return ResultFailed;

	Result rez;
	if ((rez = loadCases(file_name, caselist)) != ResultOk) return rez;

	QVector<QSharedPointer<QTestCase> > cases;
	foreach(QByteArray casename, caselist)
	{
		QSharedPointer<QTestCase> caseobj(new QTestCase(casename));
		cases.push_back(caseobj);
	}

	loadDataTags(file_name, cases);

	QSharedPointer<QTestSuite> qsuit(new QTestSuite());
	qsuit->setCases(cases);

	qsuit->setName(fileinfo.baseName().toLatin1());
	suit = qsuit.staticCast<ITestSuite>();

	return ResultOk;
}

//------------------------------------------------------------------------------
//Run qtest programm with arg -datatags, and fill cases with datatags
QTestLoader::Result QTestLoader::loadDataTags(const QString &file_name, QVector<QSharedPointer<QTestCase> > & cases)
{
	QStringList args;
	args << "-datatags";
	QVector<QByteArray> results;

	if (!Utils::runProcess(file_name, args, results)) return ResultFailed;
	filterResults(results);
	addDataTags(cases, results);

	return ResultOk;
}

//------------------------------------------------------------------------------
// Run qtest and fill vector of  testcases names
QTestLoader::Result QTestLoader::loadCases(const QString &file_name, QVector<QByteArray> &casesname)
{
	QStringList args;
	args << "-functions";
	QVector<QByteArray> results;

	if (!Utils::runProcess(file_name, args, results)) return ResultFailed;
	filterResults(results);
	casesname = results;

	return ResultOk;
}
