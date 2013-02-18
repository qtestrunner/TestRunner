#include "ctesttreeview.h"

CTestTreeView::CTestTreeView(QWidget *parent) :
    QWidget(parent)
{
    m_treeview = new QTreeView(this);
    this->setFixedSize(400, 400);

}

void CTestTreeView::getTestFilesList(QList<IFilePtr> &filelist)
{
    m_model = new CTestSuiteViewModel(filelist);
    m_treeview->setModel(m_model);
    m_treeview->setRootIndex(m_model->getRootIndex());
    this->show();
}
