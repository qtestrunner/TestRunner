#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QSharedPointer>

#include "utils/errorcodes.h"

class DatabaseManager : public QObject
{
	Q_OBJECT
public:

	static DatabaseManager & instance();
	QSqlDatabase db;

	static void getSuitesModel(QSharedPointer<QSqlTableModel> & ptr);
	static void getCasesModel(QSharedPointer<QSqlRelationalTableModel> & ptr);
	static void getIncidentsModel(QSharedPointer<QSqlRelationalTableModel> & ptr);

	QSqlQuery insertSuites;
	QSqlQuery insertCases;
	QSqlQuery inserIncidents;

signals:
	
public slots:

private:
	enum State
	{
		StateNon,
		StateOk
	};

	ECode init();
	ECode createTables(QSqlDatabase & db);
	State m_state;
	QSharedPointer<QSqlTableModel> m_suitesTable;
	QSharedPointer<QSqlRelationalTableModel> m_casesTable;
	QSharedPointer<QSqlRelationalTableModel> m_incidentsTable;
	explicit DatabaseManager(QObject *parent = 0);

};

#endif // DATABASEMANAGER_H
