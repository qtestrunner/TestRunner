#ifndef TESTKEEPER_H
#define TESTKEEPER_H

#include <qnumeric.h>
#include "testresults.h"
#include "utils/errorcodes.h"


struct SearchParams
{
	QUuid runuid;
	QDateTime m_startdate;
	QDateTime m_stopdate;
	TestCaseResult::Status stauts;
};

class TestKeeper
{
public:
	static ECode saveSuites(const QList<TestSuiteResult> & suit_results);

	static ECode loadSuites(QList<TestSuiteResult> & suit_results, const SearchParams & params);

	static ECode updateSuites(QList<TestSuiteResult> & new_suit_results, const SearchParams & params);

};

#endif // TESTKEEPER_H
