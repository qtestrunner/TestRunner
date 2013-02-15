#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QStringList>
#include <QSqlQuery>

#include "utils/log.h"

DatabaseManager::DatabaseManager(QObject *parent)
	: QObject(parent)
	, m_state(StateNon)
{

}

DatabaseManager &DatabaseManager::instance()
{
	static DatabaseManager db;
	if (db.m_state == StateNon)
		db.init();
	return db;
}

ECode DatabaseManager::init()
{
	QSqlDatabase db(QSqlDatabase::addDatabase("QSQLITE"));
	db.setDatabaseName("main.sqlite");
	if (!db.open())
	{
		FATAL(db.lastError().text());
		return EDbOpenFatalError;
	}
	if (db.tables().isEmpty())
	{
		ECode result;
		if ((result = createTables(db)) != EOk)
		{
			DEBUG(db.lastError().text());
			return result;
		}
	}
	return EOk;
}

/*
 *typedef qint64 TestRunId;

struct Incident
{
	QString m_file_path;
	QString m_description;
	QString m_tag;
	int m_line;
};

 **/
ECode DatabaseManager::createTables(QSqlDatabase & db)
{
	//FIXME: need logic about what tables need to be created
	QSqlQuery qr;
	if (!qr.exec("create table reslts_suites(id int primary key, int testrunid, suitename varchar(100), dtstart int64, dtstop int64)"))
		return EDbSQlExecError;

	if (!qr.exec("create table results_cases(id int primary key, int testrunid, casename varchar(100), int status, int result, dtstart int64, dtstop int64)"))
		return EDbSQlExecError;


	return EOk;
}

