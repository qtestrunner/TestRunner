#include <QMap>

#include "testkeeper.h"
#include "databasemanager.h"

ECode TestKeeper::saveSuites(const QList<TestSuiteResult> &suit_results)
{
	DatabaseManager & db = DatabaseManager::instance();
	return EOk;
}

ECode TestKeeper::loadSuites(QList<TestSuiteResult> &suit_results, const SearchParams & params)
{

	DatabaseManager & db = DatabaseManager::instance();
	return EOk;
}

ECode TestKeeper::updateSuites(QList<TestSuiteResult> &new_suit_results, const SearchParams &params)
{
	DatabaseManager & db = DatabaseManager::instance();
	return EOk;
}
