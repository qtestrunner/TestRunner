#ifndef TESTKEEPER_H
#define TESTKEEPER_H

#include "testresults.h"
#include "utils/errorcodes.h"

struct SearchParams
{
	QDateTime m_startdate;
	QDateTime m_stopdate;
};

class TestKeeper
{
public:
	static ECode saveSuites(const QList<TestSuiteResultPtr> & suit_results);

	static ECode loadSuites(QList<TestSuiteResultPtr> & suit_results, const SearchParams & params);

	static ECode updateSuites(QList<TestSuiteResultPtr> & new_suit_results, const SearchParams & params);

};

#endif // TESTKEEPER_H
