#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "utils/errorcodes.h"

class DatabaseManager : public QObject
{
	Q_OBJECT
public:

	static DatabaseManager & instance();
	QSqlDatabase db;
	QSqlQuery insertSuites;
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
	explicit DatabaseManager(QObject *parent = 0);

};

#endif // DATABASEMANAGER_H
