#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include "utils/errorcodes.h"

class DatabaseManager : public QObject
{
	Q_OBJECT
public:

	static DatabaseManager & instance();
signals:
	
public slots:

private:
	enum State
	{
		StateNon,
		StateOk
	};
	State m_state;

	ECode init();
	ECode createTables(QSqlDatabase & db);
	explicit DatabaseManager(QObject *parent = 0);
	
};

#endif // DATABASEMANAGER_H
