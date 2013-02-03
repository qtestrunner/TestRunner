#include <QMap>

#include "testkeeper.h"

class TempTestDataKeeper
{
	Q_DISABLE_COPY(TempTestDataKeeper)
	TempTestDataKeeper()
	{
	}

public:
	QMap<TestRunId, TestSuiteResultPtr> db;
	TempTestDataKeeper & instance()
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
		keeper.db.insert(result->m_id, keeper);
	}

	return EOk;
}

ECode TestKeeper::loadSuites(QList<TestSuiteResultPtr> &suit_results, const SearchParams & params)
{

	TempTestDataKeeper & keeper = TempTestDataKeeper::instance();
	keeper.db.find
//suit_results
	return EOk;
}

ECode TestKeeper::updateSuites(QList<TestSuiteResultPtr> &new_suit_results, const SearchParams &params)
{
	return EOk;
}
