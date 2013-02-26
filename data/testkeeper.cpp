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

	QSharedPointer<QSqlTableModel> casesTable;
	manager.getCasesModel(casesTable);

	QSharedPointer<QSqlTableModel> incidentsTable;
	manager.getIncidentsModel(incidentsTable);


	int suiteid = manager.getMaxId("results_suites") + 1;
	int caseid = manager.getMaxId("results_cases") + 1;
	manager.db.transaction();

	foreach(const TestSuiteResult & suite, suit_results)
	{
		QSqlRecord rd(suitesTable->record());
		QString runuid = suite.m_uid.toString();
		rd.setValue("id", suiteid);
		rd.setValue("suitename", suite.m_suitename);
		rd.setValue("testrunuid", runuid);
		rd.setValue("dtstart", suite.m_dt_start.toMSecsSinceEpoch());
		rd.setValue("dtstop", suite.m_dt_stop.toMSecsSinceEpoch());
		if(!suitesTable->insertRecord(-1, rd))
		{
			DEBUG(suitesTable->lastError().text());
			return EDbSQlExecError;
		}

		foreach(const TestCaseResult & caseresult, suite.m_caseresults)
		{
			QSqlRecord crd(casesTable->record());
			crd.setValue("id", caseid);
			crd.setValue("casename", caseresult.m_casename);
			crd.setValue("testrunuid", runuid);
			crd.setValue("result", caseresult.m_result);
			crd.setValue("dtstart", caseresult.m_dt_start.toMSecsSinceEpoch());
			crd.setValue("dtstop", caseresult.m_dt_stop.toMSecsSinceEpoch());
			crd.setValue("status", caseresult.m_status);
			crd.setValue("suiteid", suiteid);
			if(!casesTable->insertRecord(-1, crd))
			{
				DEBUG(casesTable->lastError().text());
				return EDbSQlExecError;
			}

			foreach(const Incident & incedent, caseresult.m_incidents)
			{
				QSqlRecord ird(incidentsTable->record());
				ird.setValue("caseid", caseid);
				ird.setValue("testrunuid", runuid);
				ird.setValue("tagname", incedent.m_tagname);
				ird.setValue("description", incedent.m_description);
				ird.setValue("filepath", incedent.m_file_path);
				ird.setValue("line", incedent.m_line);
				ird.setValue("status", incedent.m_status);
				ird.setValue("dtstart", incedent.m_dt_start.toMSecsSinceEpoch());
				ird.setValue("dtstop", incedent.m_dt_stop.toMSecsSinceEpoch());
				if(!incidentsTable->insertRecord(-1, ird))
				{
					DEBUG(incidentsTable->lastError().text());
					return EDbSQlExecError;
				}

			}
			++caseid;
		}
		++suiteid;
	}

	if(!suitesTable->submitAll())
	{
		DEBUG(suitesTable->lastError().text());
		return EDbSQlExecError;
	}
	if(!casesTable->submitAll())
	{
		DEBUG(casesTable->lastError().text());
		return EDbSQlExecError;
	}
	if(!incidentsTable->submitAll())
	{
		DEBUG(incidentsTable->lastError().text());
		return EDbSQlExecError;
	}
	manager.db.commit();
	return EOk;
}

ECode TestKeeper::loadSuites(QList<TestSuiteResult> &suit_results, const SearchParams & params)
{
	DatabaseManager & manager = DatabaseManager::instance();
	QSharedPointer<QSqlTableModel> suitesTable;
	manager.getSuitesModel(suitesTable);

	QSharedPointer<QSqlTableModel> casesTable;
	manager.getCasesModel(casesTable);

	QSharedPointer<QSqlTableModel> incidentsTable;
	manager.getIncidentsModel(incidentsTable);

	QString filter;
	if (!params.runuid.isNull())
		filter.append(QString("testrunuid = '%1' and").arg(params.runuid.toString()));

	if (!params.m_startdate.isNull())
	{
		QString datef("(dtstart >= %1) and (dtstop <= %2) and");
		filter.append(datef.arg(params.m_startdate.toMSecsSinceEpoch()));
		if (!params.m_stopdate.isNull())
			filter.append(datef.arg(params.m_stopdate.toMSecsSinceEpoch()));
		else
			filter.append(datef.arg(QDateTime::currentMSecsSinceEpoch()));
	}

	if (!filter.isEmpty())
	{
		filter = filter.left(filter.size() - 4);//cuting and
	}

	suitesTable->setFilter(filter);

	if (!suitesTable->select())
	{
		DEBUG(suitesTable->lastError().text());
		return EDbSQlExecError;
	}

	for(int i = 0; i < suitesTable->rowCount(); i++)
	{
		TestSuiteResult suiteResult;
		const QSqlRecord & row = suitesTable->record(i);

		suiteResult.m_suitename = row.value(suitesTable->fieldIndex("suitename")).toString();
		suiteResult.m_uid = QUuid(row.value(suitesTable->fieldIndex("testrunuid")).toString());
		suiteResult.m_dt_start = QDateTime::fromMSecsSinceEpoch(row.value(suitesTable->fieldIndex("dtstart")).toLongLong());
		suiteResult.m_dt_stop = QDateTime::fromMSecsSinceEpoch(row.value(suitesTable->fieldIndex("dtstop")).toLongLong());


		casesTable->setFilter(QString("suiteid = %1").arg(row.value(0).toInt()));
		if (!casesTable->select())
		{
			DEBUG(casesTable->lastError().text());
			return EDbSQlExecError;
		}
		for(int i = 0; i < casesTable->rowCount(); i++)
		{
			TestCaseResult caseResult;
			const QSqlRecord & row = casesTable->record(i);
			caseResult.m_casename = row.value(casesTable->fieldIndex("casename")).toString();
			caseResult.m_result = TestCaseResult::Result(row.value(casesTable->fieldIndex("result")).toInt());
			caseResult.m_status = TestCaseResult::Status(row.value(casesTable->fieldIndex("result")).toInt());
			caseResult.m_dt_start = QDateTime::fromMSecsSinceEpoch(row.value(casesTable->fieldIndex("dtstart")).toLongLong());
			caseResult.m_dt_stop = QDateTime::fromMSecsSinceEpoch(row.value(casesTable->fieldIndex("dtstop")).toLongLong());

			incidentsTable->setFilter(QString("caseid = %1").arg(row.value(0).toString()));
			if (!incidentsTable->select())
			{
				DEBUG(incidentsTable->lastError().text());
				return EDbSQlExecError;
			}
			for(int i = 0; i < incidentsTable->rowCount(); i++)
			{
				Incident inc;
				const QSqlRecord & row = incidentsTable->record(i);
				inc.m_tagname = row.value(incidentsTable->fieldIndex("tagname")).toString();
				inc.m_description = row.value(incidentsTable->fieldIndex("description")).toString();
				inc.m_file_path = row.value(incidentsTable->fieldIndex("filepath")).toString();
				inc.m_line = row.value(incidentsTable->fieldIndex("line")).toInt();
				inc.m_status = Incident::Status(row.value(incidentsTable->fieldIndex("status")).toInt());
				inc.m_dt_start = QDateTime::fromMSecsSinceEpoch(row.value(casesTable->fieldIndex("dtstart")).toLongLong());
				inc.m_dt_stop = QDateTime::fromMSecsSinceEpoch(row.value(casesTable->fieldIndex("dtstop")).toLongLong());
				caseResult.m_incidents.push_back(inc);
			}
			suiteResult.m_caseresults.push_back(caseResult);
		}
		suit_results.push_back(suiteResult);
	}

	return EOk;
}

ECode TestKeeper::updateSuites(const QList<TestSuiteResult> &new_suit_results)
{
	//FIXME: Rewrite to simple sql statments
	//FIXME: implement only after gui
//	DatabaseManager & manager = DatabaseManager::instance();
//	QSharedPointer<QSqlTableModel> suitesTable;
//	manager.getSuitesModel(suitesTable);

//	QSharedPointer<QSqlTableModel> casesTable;
//	manager.getCasesModel(casesTable);

//	QSharedPointer<QSqlTableModel> incidentsTable;
//	manager.getIncidentsModel(incidentsTable);

//	QSqlRecord sr = suitesTable->record();
//	QSqlRecord cr = casesTable->record();
//	QSqlRecord ir = incidentsTable->record();

//	foreach (TestSuiteResult suite, new_suit_results)
//	{
//		suitesTable->setFilter(QString("testrunuid = '%1'").arg(params.runuid.toString()));
//		if (!suitesTable->select())
//		{
//			DEBUG(suitesTable->lastError().text());
//			return EDbSQlExecError;
//		}

//		sr.setValue("suitename", suite.m_suitename);
//		rd.setValue("testrunuid", runuid);
//		rd.setValue("dtstart", suite.m_dt_start.toMSecsSinceEpoch());
//		rd.setValue("dtstop", suite.m_dt_stop.toMSecsSinceEpoch());
//		suitesTable->setRecord(0, )
//		setRecord(0,)
//		->setRecord(0, )

//	}

	return EOk;
}
