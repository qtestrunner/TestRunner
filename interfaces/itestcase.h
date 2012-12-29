#ifndef ITESTCASE_H
#define ITESTCASE_H

#include <QByteArray>
#include <QVector>

class ITestCase
{
public:
	virtual ~ITestCase(){};

	virtual void print() = 0;
	virtual const QByteArray & getName() = 0;
	virtual bool hasDataTags() = 0;
	virtual const QVector<QByteArray> & getDataTags() = 0;
};

#endif // ITESTCASE_H
