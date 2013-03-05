#include <QCoreApplication>
#include "mainfrm.h"
#include "ui_mainfrm.h"

#include "utils/log.h"
#include "testscaner.h"
#include "data/testkeeper.h"
//#include "data/testresults.h"

MainFrm::MainFrm(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainFrm)
{
	ui->setupUi(this);
	QStringList args(QCoreApplication::arguments());
	if (args.count() < 3)
	{
		LOG("first argument path, second - mask\n");
		return;
	}

	ui->fileMaskEdit->setText(args.at(2));
	ui->folderEdit->setText(args.at(1));

}

MainFrm::~MainFrm()
{
	delete ui;
}

void MainFrm::on_tempLoadButton_clicked()
{
	QStringList masks;
	masks << ui->fileMaskEdit->text();
	TestScaner::loadFolder(ui->folderEdit->text(), masks, m_testfiles);
	QSharedPointer<CTestSuiteViewModel> model(new CTestSuiteViewModel(m_testfiles, this));
	ui->suitesView->setModel(model.data());
	m_suitesmodel.swap(model);
}

void MainFrm::on_tempRunButton_clicked()
{
	foreach(IFilePtr file, m_testfiles)
		file->run(m_results);

	TestKeeper::saveSuites(m_results);
}

