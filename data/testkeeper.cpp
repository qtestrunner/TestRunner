#include <QMap>
#include <QSqlError>
#include <QUuid>

#include "testkeeper.h"
#include "databasemanager.h"

#include "utils/log.h"

ECode TestKeeper::saveSuites(const QList<TestSuiteResult> &suit_results)
{
	DatabaseManager & manager = DatabaseManager::instance();
	QSqlDatabase & db = manager.db;
	QUuid runuid;

	manager.

	db.transaction();
	QSqlQuery qr;

	foreach(const TestSuiteResult & suite, suit_results)
	{
		qr = manager.insertSuites;
		qr.bindValue(":suitename", suite.m_suitename);
		runuid = suite.m_uid;
		qr.bindValue(":testrunuid", runuid.toByteArray());
		qr.bindValue(":dtstart", suite.m_dt_start.toMSecsSinceEpoch());
		qr.bindValue(":dtstop", suite.m_dt_stop.toMSecsSinceEpoch());
		if (!qr.exec())
		{
			DEBUG(qr.lastError().text());
			return EDbSQlExecError;
		}
		QVariant suite_id = qr.lastInsertId();

		foreach(const TestCaseResult & caseresult, suite.m_caseresults)
		{
			qr = manager.insertCases;
			qr.bindValue(":casename", caseresult.m_casename);
			qr.bindValue(":testrunid", runuid.toByteArray());
			qr.bindValue(":result", caseresult.m_result);
			qr.bindValue(":dtstop", caseresult.m_dt_stop);
			qr.bindValue(":status", caseresult.m_status);
			qr.bindValue(":suiteid", suite_id);
			qr.bindValue(":dtstart", caseresult.m_dt_start);
			if (!qr.exec())
			{
				DEBUG(qr.lastError().text());
				return EDbSQlExecError;
			}
			QVariant caseid =  qr.lastInsertId();
			foreach(const Incident & incedent, caseresult.m_incedents)
			{
				qr = manager.inserIncidents;
				qr.bindValue(":caseid", caseid);
				qr.bindValue(":testrunid", runuid.toByteArray());
				qr.bindValue(":tagname", incedent.m_tagname);
				qr.bindValue(":description", incedent.m_description);
				qr.bindValue(":filepath", incedent.m_file_path);
				qr.bindValue(":line", incedent.m_line);
				qr.bindValue(":dtstart", incedent.m_dt_start);
				qr.bindValue(":dtstop", incedent.m_dt_stop);
				qr.bindValue(":status", incedent.m_status);
				if (!qr.exec())
				{
					DEBUG(qr.lastError().text());
					return EDbSQlExecError;
				}
			}
		}
	}
	db.commit();
	return EOk;
}

ECode TestKeeper::loadSuites(QList<TestSuiteResult> &suit_results, const SearchParams & params)
{
//	DatabaseManager & manager = DatabaseManager::instance();
//	if (params.runId != QUuid())
//	{
//		QString qrsql("select * from")
//		 qr(manager.db);

//		{

//		}
//	}

	return EOk;
}

ECode TestKeeper::updateSuites(QList<TestSuiteResult> &new_suit_results, const SearchParams &params)
{
	DatabaseManager & manager = DatabaseManager::instance();

	return EOk;
}
