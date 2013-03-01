#include "mainfrm.h"
#include "ui_mainfrm.h"

MainFrm::MainFrm(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainFrm)
{
	ui->setupUi(this);
}

MainFrm::~MainFrm()
{
	delete ui;
}
