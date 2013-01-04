#ifndef TESTSCANER_H
#define TESTSCANER_H

#include <QString>
#include <QList>
#include <QSharedPointer>

#include "interfaces/itestsuit.h"

/** Static class that loads all tests suits in some folder */
class TestScaner
{
	enum TestType ///< Supported test types
	{
		TestTypeQtTestLib,
		TestTypeGoogleTest,
		TestTypeUnKnown
	};

	/** Check testsuit type
	 * @param file Absolut path to testsuit
	 * @return Test type or unknown
	 */
	static TestType getTestType(const QString & file);
public:
	/** Loads all testsuites in folder to vector of ITestSuite
	 * @param folder absolut path to folder
	 * @param masks masks of testsuits files
	 * @param[out] testsuites Vector of testsuites
	 */
	static void loadFolder(const QString & folder, const QStringList &masks, QList<QSharedPointer<ITestSuite> > & testsuites);
};

#endif // TESTSCANER_H
