#include <QDebug>
#include <QSharedPointer>

#include "qtestloader.h"

const int max_str_len = 100;
QTestLoader::QTestLoader()
{
}

QTestLoader::~QTestLoader()
{
}

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

QTestLoader::Result QTestLoader::loadTestSuit(const QString & file_name, QSharedPointer<ITestSuit> & suit)
{
	QVector<QByteArray> caselist;
	Result rez;
	if ((rez = loadCases(file_name, caselist)) != ResultOk) return rez;

	QVector<QSharedPointer<QTestCase> > cases;
	foreach(QByteArray casename, caselist)
	{
		QSharedPointer<QTestCase> caseobj(new QTestCase(casename));
		cases.push_back(caseobj);
	}

	loadDataTags(file_name, cases);

	QSharedPointer<QTestSuit> qsuit(new QTestSuit());
	qsuit->setCases(cases);
	suit = qsuit.staticCast<ITestSuit>();

	return ResultOk;
}

QTestLoader::Result QTestLoader::loadDataTags(const QString &file_name, QVector<QSharedPointer<QTestCase> > & cases)
{
	QStringList args;
	args << "-datatags";
	Result rez;
	QVector<QByteArray> results;
	if ((rez = runProcess(file_name, args, results)) != ResultOk) return rez;

	filterResults(results);
	addDataTags(cases, results);

	return ResultOk;
}

QTestLoader::Result QTestLoader::runProcess(const QString &file_name, const QStringList & args, QVector<QByteArray> &results)
{
	QProcess process;
	process.setProcessChannelMode(QProcess::MergedChannels);
	process.start(file_name, args);
	bool rez = process.waitForFinished();

	if (!rez)
		return ResultTimeOut;

	int rbt = -1;
	do
	{
		char data[max_str_len];

		rbt = process.readLine(data, max_str_len);
		if (rbt > 0)
		{
			results.push_back(data);
		}
	}
	while(rbt != -1);
	return ResultOk;
}

QTestLoader::Result QTestLoader::loadCases(const QString &file_name, QVector<QByteArray> &casesname)
{
	QStringList args;
	args << "-functions";
	Result rez;
	QVector<QByteArray> results;
	if ((rez = runProcess(file_name, args, results)) != ResultOk) return rez;
	filterResults(results);

	casesname = results;
	return ResultOk;
}
