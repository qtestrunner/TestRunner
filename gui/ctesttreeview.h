#ifndef CTESTTREEVIEW_H
#define CTESTTREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItemModel>
#include <interfaces/ifile.h>
#include "ctestsuiteviewmodel.h"

class CTestTreeView : public QWidget
{
    Q_OBJECT
public:

    explicit CTestTreeView(QWidget *parent = 0);
    
    void getTestFilesList(QList<IFilePtr>& fileList);

signals:
    
public slots:
    
private:
    QTreeView* m_treeview;
    CTestSuiteViewModel* m_model;
};

#endif // CTESTTREEVIEW_H
