#ifndef CTESTSUITEVIEWMODEL_H
#define CTESTSUITEVIEWMODEL_H

#include <QAbstractItemModel>
#include <interfaces/ifile.h>
#include "treenode.h"

class CTestSuiteViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CTestSuiteViewModel (QList<IFilePtr>& filelist, QObject *parent = 0);

    int columnCount (const QModelIndex &parent = QModelIndex()) const;

    QVariant data (const QModelIndex &index, int role) const;

    QModelIndex index (int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent (const QModelIndex &child) const;

    int rowCount (const QModelIndex &parent = QModelIndex()) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    QModelIndex getRootIndex();
signals:
    
public slots:

private:
    QList<ITestSuitePtr> m_testsuites;
    TreeNode* m_rootNode;
};

#endif // CTESTSUITEVIEWMODEL_H
