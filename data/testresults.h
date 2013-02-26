#ifndef TESTRESULTS_H
#define TESTRESULTS_H

#include <QSharedPointer>
#include <QUuid>
#include <QList>
#include <QString>
#include <QDateTime>
#include <qnumeric.h>

typedef qint64 TestRunId;

struct Incident
{
	enum Status
	{
		StatusAccepted = 0,
		StatusRejected = 1,
		StatusNew = 2
	};

	QString m_file_path;
	QString m_description;
	QString m_tagname;
	QDateTime m_dt_start;
	QDateTime m_dt_stop;
	Status m_status;
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

	QString m_casename;
	Status m_status;
	Result m_result;
	QDateTime m_dt_start;
	QDateTime m_dt_stop;
	QList<Incident> m_incidents;
};

struct TestSuiteResult
{
	QUuid m_uid;
	QString m_suitename;
	QDateTime m_dt_start;
	QDateTime m_dt_stop;
	QList<TestCaseResult> m_caseresults;
};
typedef QSharedPointer<TestSuiteResult> TestSuiteResultPtr;

#endif // TESTRESULTS_H
