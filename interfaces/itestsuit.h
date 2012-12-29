#ifndef ITESTSUIT_H
#define ITESTSUIT_H

#include <QVector>
#include <QSharedPointer>

#include <interfaces/itestcase.h>

class ITestSuit
{
public:

	virtual ~ITestSuit(){};
	virtual const QByteArray & getName() = 0;
	virtual QVector<QSharedPointer<ITestCase> > & getCases() = 0;
};
#endif // ITESTSUIT_H
