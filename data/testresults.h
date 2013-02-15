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
		ResultFalse = 0,
		ResultTrue = 1
	};
	enum Status
	{
		StatusAccepted = 0,
		StatusSolved = 1,
		StatusRejected = 2
	};
	TestCaseResult()
		: m_status(StatusAccepted)
		, m_result(ResultTrue)
	{
	}

	QList<Incident> m_incidents;
	QString m_casename;
	TestRunId m_id;
	Result m_result;
	Status m_status;
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
typedef QSharedPointer<TestSuiteResult> TestSuiteResultPtr;

#endif // TESTRESULTS_H
