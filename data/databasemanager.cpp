#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QStringList>

#include "utils/log.h"

DatabaseManager::DatabaseManager(QObject *parent)
	: QObject(parent)
	, m_state(StateNon)
{
}

DatabaseManager &DatabaseManager::instance()
{
	static DatabaseManager manager;
	if (manager.m_state == StateNon)
		manager.init();
	return manager;
}

void DatabaseManager::getSuitesModel(QSharedPointer<QSqlTableModel> &ptr)
{
	ptr = DatabaseManager::instance().m_suitesTable;
}

ECode DatabaseManager::init()
{
	db = QSqlDatabase::addDatabase("QSQLITE");

	db.setDatabaseName("main.sqlite");
	if (!db.open())
	{
		FATAL(db.lastError().text());
		return EDbOpenFatalError;
	}

	TRACE("database opened");
	QSet<QString> need_tables;
	need_tables << "results_suites" << "results_cases" << "results_incidents";

	TRACE(db.tables().join(","));

	if (!db.tables().toSet().contains(need_tables))
	{
		TRACE("try create");
		ECode result;
		if ((result = createTables(db)) != EOk)
		{
			DEBUG(db.lastError().text());
			return result;
		}
	}

//	insertSuites = QSqlQuery(db);
//	if (!insertSuites.prepare("insert into results_suites"
//						 "(suitename, testrunuid, dtstart, dtstop) values"
//						 "(:suitename, :testrunuid, :dtstart, :dtstop)"))
//	{
//		DEBUG(insertSuites.lastError().text());
//		return EDbOpenFatalError;
//	}

//	insertCases = QSqlQuery(db);
//	if (!insertCases.prepare("insert into results_cases"
//						"( casename, testrunuid, result, dtstop, status, suiteid, dtstart) values"
//						"( :casename, :testrunuid, :result, :dtstop, :status, :suiteid, :dtstart)"))
//	{
//		DEBUG(insertCases.lastError().text());
//		return EDbOpenFatalError;
//	}

//	inserIncidents = QSqlQuery(db);
//	if (!inserIncidents.prepare("insert into results_incidents"
//						   "( caseid, testrunuid, tagname, description, dtstart, filepath, line, dtstop, status) values "
//						   "( :caseid, :testrunuid, :tagname, :description, :dtstart, :filepath, :line, :dtstop, :status)"))
//	{
//		DEBUG(insertCases.lastError().text());
//		return EDbOpenFatalError;
//	}

	m_suitesTable = QSharedPointer<QSqlTableModel>(new QSqlTableModel(0, db));
	m_suitesTable->setTable("results_suites");
	m_suitesTable->setEditStrategy(QSqlTableModel::OnManualSubmit);

	m_casesTable = QSharedPointer<QSqlTableModel>(new QSqlTableModel(0, db));
	m_casesTable->setTable("results_cases");
	m_casesTable->setEditStrategy(QSqlTableModel::OnManualSubmit);

	m_incidentsTable = QSharedPointer<QSqlTableModel>(new QSqlTableModel(0, db));
	m_incidentsTable->setTable("results_incidents");
	m_incidentsTable->setEditStrategy(QSqlTableModel::OnManualSubmit);

	m_state = StateOk;
	return EOk;
}

ECode DatabaseManager::createTables(QSqlDatabase & db)
{
	//FIXME: need logic about what tables need to be created
	QSqlQuery qr(db);

	if (!qr.exec("create table results_suites(id INTEGER primary key, testrunuid TEXT, suitename varchar(200), dtstart INTEGER, dtstop INTEGER);"))
	{
		DEBUG(qr.lastError().text());
		return EDbSQlExecError;
	}
	TRACE("results_suites created");

	if (!qr.exec("create table results_cases(id INTEGER primary key, testrunuid TEXT, suiteid INTEGER, casename varchar(200), status INTEGER, result INTEGER, dtstart INTEGER, dtstop INTEGER);"))
	{
		DEBUG(qr.lastError().text());
		return EDbSQlExecError;
	}
	TRACE("results_cases created");

	if (!qr.exec("create table results_incidents(id INTEGER primary key, testrunuid TEXT, caseid INTEGER, tagname varchar(200), description varchar (5000), filepath varchar(1000), line INTEGER, status INTEGER, dtstart INTEGER, dtstop INTEGER);"))
	{
		DEBUG(qr.lastError().text());
		return EDbSQlExecError;
	}
	TRACE("results_incidents created");

	return EOk;
}

void DatabaseManager::getIncidentsModel(QSharedPointer<QSqlTableModel> &ptr)
{
	ptr = DatabaseManager::instance().m_incidentsTable;
}

int DatabaseManager::getMaxId(const QString & table_name)
{
	QSqlQuery maxid(db);
	if (!maxid.exec(QString("SELECT id FROM %1 order by id desc limit 1").arg(table_name)))
	{
		DEBUG(maxid.lastError());
		DEBUG(maxid.lastQuery());
		return 1;
	}
	if(!maxid.next()) return 1;
	QVariant id = maxid.value(0);
	bool ok;
	int rez = id.toInt(&ok);
	if (ok)
		return rez;
	else
		return 1;
}


void DatabaseManager::getCasesModel(QSharedPointer<QSqlTableModel> &ptr)
{
	ptr = DatabaseManager::instance().m_casesTable;
}
