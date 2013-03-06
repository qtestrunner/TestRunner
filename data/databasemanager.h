#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSharedPointer>

#include "utils/errorcodes.h"

class DatabaseManager : public QObject
{
	Q_OBJECT
public:

	static DatabaseManager & instance();
	QSqlDatabase db;

private:
	friend class TestKeeper;
	static void getSuitesModel(QSharedPointer<QSqlTableModel> & ptr);
	static void getCasesModel(QSharedPointer<QSqlTableModel> & ptr);
	static void getIncidentsModel(QSharedPointer<QSqlTableModel> & ptr);
	int getMaxId(const QString & table_name);

	enum State
	{
		StateNon,
		StateOk
	};

	ECode init();
	ECode createTables(QSqlDatabase & db);
	State m_state;
	QSharedPointer<QSqlTableModel> m_suitesTable;
	QSharedPointer<QSqlTableModel> m_casesTable;
	QSharedPointer<QSqlTableModel> m_incidentsTable;
	explicit DatabaseManager(QObject *parent = 0);

};

#endif // DATABASEMANAGER_H
