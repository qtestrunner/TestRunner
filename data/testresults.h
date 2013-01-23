#ifndef TESTRESULTS_H
#define TESTRESULTS_H

#include <QSharedPointer>
#include <QList>
#include <QString>
#include <QDateTime>
#include <qnumeric.h>

typedef qint64 TestRunId;
struct TestCaseResult
{
	TestCaseResult()
		: m_id(0) //Clang insisting
		, m_result(ResultFalse)
	{
	}

	enum Result
	{
		ResultTrue,
		ResultFalse
	};
	const QString m_casename;
	const TestRunId m_id;
	const Result m_result;
	const QDateTime m_dt_start;
	const QDateTime m_dt_stop;
};
typedef QSharedPointer<TestCaseResult> TestCaseResultPtr;

struct TestSuiteResult
{
	TestSuiteResult()
		: m_id()
	{
	}

	const TestRunId m_id;
	const QString m_suitename;
	const QList<TestCaseResultPtr> m_caseresults;
	const QDateTime m_dt_start;
	const QDateTime m_dt_stop;
};
typedef QSharedPointer<TestSuiteResult> TestSuiteResultPtr;

#endif // TESTRESULTS_H
