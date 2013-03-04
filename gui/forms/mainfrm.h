#ifndef MAINFRM_H
#define MAINFRM_H

#include <QMainWindow>
#include "interfaces/ifile.h"
#include "gui/ctestsuiteviewmodel.h"

namespace Ui {
class MainFrm;
}

class MainFrm : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainFrm(QWidget *parent = 0);
	~MainFrm();
	
private slots:
	void on_tempLoadButton_clicked();

	void on_tempRunButton_clicked();

private:
	Ui::MainFrm *ui;
	QList<TestSuiteResult> m_results;//temp
	QList<IFilePtr> m_testfiles;//temp
	CTestSuiteViewModel m_suitesmodel;//temp
};

#endif // MAINFRM_H
