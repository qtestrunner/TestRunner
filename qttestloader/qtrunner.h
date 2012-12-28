#ifndef QTRUNNER_H
#define QTRUNNER_H

#include <QObject>
#include <QProcess>
#include <QVector>

class TestCase
{
	QByteArray m_name;
	public:
	TestCase(){}
	TestCase(const QByteArray & name)
		: m_name(name)
	{
	}
};

class TestSuit
{
	QByteArray m_name;
	QVector<TestCase> m_testcases;
	public:
	TestSuit(const QByteArray & name)
		: m_name(name)
	{
	}

	void addTestCase(const TestCase & tcase)
	{
		m_testcases.push_back(tcase);
	}

};

class QtRunner: public QObject
{
	Q_OBJECT
public:
	explicit QtRunner(QObject *parent = 0);

	enum Result
	{
		ResultOk,
		ResultNotRunned,
		ResultCrushed,
		ResultFailed,
		ResultTimeOut
	};
	static Result getTestCases(const QString & file_name, QStringList & cases);
	static Result runTest(const QString & name);

};

#endif // QTRUNNER_H
