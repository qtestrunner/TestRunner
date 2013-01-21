
#include <QSharedPointer>
#include <QFile>

#include "qtestloader.h"
#include "qtestfile.h"
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
void QTestLoader::filterResults(QList<QByteArray> & data)
{
	QList<QByteArray>::iterator end = data.end();
	for (QList<QByteArray>::iterator it = data.begin(); it != end; ++it)
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
void QTestLoader::addDataTags(QList<QTestCasePtr> & cases, const QList<QByteArray> & results)
{
	QList<QByteArray> tags;
	for (QList<QTestCasePtr>::iterator it = cases.begin(); it != cases.end(); ++it)
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
//QTestLoader::Result QTestLoader::loadTestSuite(const QString & file_name, ITestSuitePtr & suit)
//{
//	QVector<QByteArray> caselist;

//	QFileInfo fileinfo(file_name);
//	if (fileinfo.size() == 0)
//		return ResultFailed;

//	Result rez;
//	if ((rez = loadCases(file_name, caselist)) != ResultOk) return rez;

//	QVector<QSharedPointer<QTestCase> > cases;
//	foreach(QByteArray casename, caselist)
//	{
//		QSharedPointer<QTestCase> caseobj(new QTestCase(casename));
//		cases.push_back(caseobj);
//	}

//	loadDataTags(file_name, cases);

//	QSharedPointer<QTestSuite> qsuit(new QTestSuite());
//	qsuit->setCases(cases);

//	qsuit->setName(fileinfo.baseName().toLatin1());
//	suit = qsuit.staticCast<ITestSuite>();

//	return ResultOk;
//}

ITestLoader::Result QTestLoader::loadFile(const QString &file_name, IFilePtr &file_ptr)
{
	QList<QByteArray> caselist;

	QFileInfo fileinfo(file_name);
	if (fileinfo.size() == 0)
		return ResultFailed;

	Result rez;
	if ((rez = loadCases(file_name, caselist)) != ResultOk) return rez;

	QList<QTestCasePtr> cases;
	foreach(QByteArray casename, caselist)
	{
		QTestCasePtr caseobj(new QTestCase(casename));
		cases.push_back(caseobj);
	}

	loadDataTags(file_name, cases);

	QTestSuitePtr qsuit(new QTestSuite());
	qsuit->setCases(cases);

	qsuit->setName(fileinfo.baseName().toLatin1());

	QTestFilePtr file(new QTestFile());
	file->setQTestSuite(qsuit);
	file_ptr = file.staticCast<IFile>();

	return ResultOk;

}

//------------------------------------------------------------------------------
//Run qtest programm with arg -datatags, and fill cases with datatags
QTestLoader::Result QTestLoader::loadDataTags(const QString &file_name, QList<QTestCasePtr> & cases)
{
	QStringList args;
	args << "-datatags";
	QList<QByteArray> results;

	if (!Utils::runProcess(file_name, args, results)) return ResultFailed;
	filterResults(results);
	addDataTags(cases, results);

	return ResultOk;
}

//------------------------------------------------------------------------------
// Run qtest and fill vector of  testcases names
QTestLoader::Result QTestLoader::loadCases(const QString &file_name, QList<QByteArray> &casesname)
{
	QStringList args;
	args << "-functions";
	QList<QByteArray> results;

	if (!Utils::runProcess(file_name, args, results)) return ResultFailed;
	filterResults(results);
	casesname = results;

	return ResultOk;
}
