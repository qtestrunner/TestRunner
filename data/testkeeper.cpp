#include <QMap>
#include <QSqlError>

#include "testkeeper.h"
#include "databasemanager.h"

#include "utils/log.h"

ECode TestKeeper::saveSuites(const QList<TestSuiteResult> &suit_results)
{
	DatabaseManager & manager = DatabaseManager::instance();
	QSqlDatabase & db = manager.db;
	QSqlQuery & qr = manager.insertSuites;

	foreach(const TestSuiteResult & suite, suit_results)
	{
		qr.bindValue(":suitename", suite.m_suitename);
		qr.bindValue(":testrunid", suite.m_id);
		qr.bindValue(":dtstart", suite.m_dt_start.toMSecsSinceEpoch());
		qr.bindValue(":dtstop", suite.m_dt_stop.toMSecsSinceEpoch());
		if (!qr.exec())
		{
			DEBUG(qr.lastError().text());
			return EDbSQlExecError;
		}
	}

	return EOk;
}

ECode TestKeeper::loadSuites(QList<TestSuiteResult> &suit_results, const SearchParams & params)
{
	DatabaseManager & manager = DatabaseManager::instance();
	return EOk;
}

ECode TestKeeper::updateSuites(QList<TestSuiteResult> &new_suit_results, const SearchParams &params)
{
	DatabaseManager & manager = DatabaseManager::instance();

	return EOk;
}
