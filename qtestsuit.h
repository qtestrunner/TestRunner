#ifndef QTESTSUIT_H
#define QTESTSUIT_H

#include <QtCore>

#include <interfaces/itestsuit.h>
#include <qtestcase.h>

class QTestSuit: public ITestSuit
{
	QByteArray m_name; ///>
	QVector<QSharedPointer<ITestCase> > m_cases; ///>
public:
	QTestSuit();
	~QTestSuit();
	void setCases(const QVector<QSharedPointer<QTestCase> > & cases);
	void setName(const QByteArray &name);

	virtual const QByteArray & getName();
	virtual QVector<QSharedPointer<ITestCase> > & getCases();

};

#endif // QTESTSUIT_H
