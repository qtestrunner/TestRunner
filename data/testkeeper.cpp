#include <QMap>
#include <QSqlError>
#include <QUuid>
#include <QSqlRecord>

#include "testkeeper.h"
#include "databasemanager.h"

#include "utils/log.h"

ECode TestKeeper::saveSuites(const QList<TestSuiteResult> &suit_results)
{
	DatabaseManager & manager = DatabaseManager::instance();
	QSharedPointer<QSqlTableModel> suitesTable;
	manager.getSuitesModel(suitesTable);

	QSharedPointer<QSqlRelationalTableModel> casesTable;
	manager.getCasesModel(casesTable);

	QSharedPointer<QSqlRelationalTableModel> incidentsTable;
	manager.getIncidentsModel(incidentsTable);

	foreach(const TestSuiteResult & suite, suit_results)
	{
		QSqlRecord rd(suitesTable->record());
		QByteArray runuid = suite.m_uid.toByteArray();
		rd.setValue("suitename", suite.m_suitename);
		rd.setValue("testrunuid", runuid);
		rd.setValue("dtstart", suite.m_dt_start.toMSecsSinceEpoch());
		rd.setValue("dtstop", suite.m_dt_stop.toMSecsSinceEpoch());
		if(!suitesTable->insertRecord(-1, rd))
		{
			DEBUG(suitesTable->lastError().text());
			return EDbSQlExecError;
		}
		if(!suitesTable->submitAll())
		{
			DEBUG(suitesTable->lastError().text());
			return EDbSQlExecError;
		}

		int suiteid = suitesTable->query().lastInsertId().toInt();
		DEBUG(suiteid);
		foreach(const TestCaseResult & caseresult, suite.m_caseresults)
		{
			QSqlRecord crd(casesTable->record());
			crd.setValue("casename", caseresult.m_casename);
			crd.setValue("testrunuid", runuid);
			crd.setValue("result", caseresult.m_result);
			crd.setValue("dtstart", caseresult.m_dt_start);
			crd.setValue("dtstop", caseresult.m_dt_stop);
			crd.setValue("status", caseresult.m_status);
			crd.setValue("suiteid", suiteid);
			if(!casesTable->insertRecord(-1, crd))
			{
				DEBUG(casesTable->lastError().text());
				return EDbSQlExecError;
			}
			if(!casesTable->submitAll())
			{
				DEBUG(casesTable->lastError().text());
				return EDbSQlExecError;
			}

			int caseid = casesTable->query().lastInsertId().toInt();
			foreach(const Incident & incedent, caseresult.m_incedents)
			{
				QSqlRecord ird(casesTable->record());
				ird.setValue("caseid", caseid);
				ird.setValue("testrunuid", runuid);
				ird.setValue("tagname", incedent.m_tagname);
				ird.setValue("description", incedent.m_description);
				ird.setValue("filepath", incedent.m_file_path);
				ird.setValue("line", incedent.m_line);
				ird.setValue("status", incedent.m_status);
				ird.setValue("dtstart", incedent.m_dt_start);
				ird.setValue("dtstop", incedent.m_dt_stop);
				if(!incidentsTable->insertRecord(-1, ird))
				{
					DEBUG(incidentsTable->lastError().text());
					return EDbSQlExecError;
				}
				if(!incidentsTable->submitAll())
				{
					DEBUG(incidentsTable->lastError().text());
					return EDbSQlExecError;
				}

			}
		}
	}
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
