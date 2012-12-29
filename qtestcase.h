#ifndef QTESTCASE_H
#define QTESTCASE_H

#include <QtCore>
#include <interfaces/itestcase.h>

class QTestCase: public ITestCase
{
	QByteArray m_name;
	QVector<QByteArray> m_datatags;
public:
	QTestCase();
	~QTestCase();

	explicit QTestCase(const QByteArray & m_name);
	void setDataTags(const QVector<QByteArray> & datatags);

	virtual void print();
	virtual bool hasDataTags();
	virtual const QByteArray & getName();
	virtual const QVector<QByteArray> & getDataTags();
};

#endif // QTESTCASE_H
