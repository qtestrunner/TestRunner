#include <QMap>

#include "testkeeper.h"

class TempTestDataKeeper//TEMP object only for debug
{
	Q_DISABLE_COPY(TempTestDataKeeper)
	TempTestDataKeeper()
	{
	}

public:
	QMap<TestRunId, TestSuiteResultPtr> db;
	static TempTestDataKeeper & instance()
	{
		static TempTestDataKeeper t;
		return t;
	}
};


ECode TestKeeper::saveSuites(const QList<TestSuiteResultPtr> &suit_results)
{
	TempTestDataKeeper & keeper = TempTestDataKeeper::instance();
	foreach(const TestSuiteResultPtr & result, suit_results)
	{
		keeper.db.insert(result->m_id, result);
	}

	return EOk;
}

ECode TestKeeper::loadSuites(QList<TestSuiteResultPtr> &suit_results, const SearchParams & params)
{

	TempTestDataKeeper & keeper = TempTestDataKeeper::instance();


	return EOk;
}

ECode TestKeeper::updateSuites(QList<TestSuiteResultPtr> &new_suit_results, const SearchParams &params)
{
	return EOk;
}
