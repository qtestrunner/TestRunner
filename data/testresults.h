#ifndef TESTRESULTS_H
#define TESTRESULTS_H

#include <QSharedPointer>
#include <QList>
#include <QString>
#include <QDateTime>
#include <qnumeric.h>

typedef qint64 TestRunId;

struct Incident
{
	QString m_file_path;
	QString m_description;
	QString m_tag;
	int m_line;
};

struct TestCaseResult
{
	enum Result
	{
		ResultTrue,
		ResultFalse
	};
	QList<Incident> m_incidents;
	QString m_casename;
	TestRunId m_id;
	Result m_result;
	QDateTime m_dt_start;
	QDateTime m_dt_stop;
};

struct TestSuiteResult
{
	TestRunId m_id;
	QString m_suitename;
	QList<TestCaseResult> m_caseresults;
	QDateTime m_dt_start;
	QDateTime m_dt_stop;
};

#endif // TESTRESULTS_H
