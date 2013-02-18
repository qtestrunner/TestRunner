#include "ctestsuiteviewmodel.h"

CTestSuiteViewModel::CTestSuiteViewModel(QList<IFilePtr>& filelist, QObject *parent):
    QAbstractItemModel(parent)
{
//    foreach(IFilePtr file, filelist){
//        m_testsuites << file->getTestSuites();
//    }
    m_rootNode = new TreeNode;
    foreach(IFilePtr file, filelist){

        foreach(ITestSuitePtr testsuite, file->getTestSuites()){
            TreeNode* suiteNode = m_rootNode->addChildNode( (void*)testsuite.data());

            foreach(ITestCasePtr testcase, testsuite->getCases()){
                TreeNode* caseNode = suiteNode->addChildNode( (void*)testcase.data());

                if (testcase->hasDataTags()){
                    foreach(QString datatag, testcase->getAllDataTags()){
                        caseNode->addChildNode( (void*)datatag.toAscii().data());
                    }
                }
            }
        }
    }

}

Qt::ItemFlags CTestSuiteViewModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


QModelIndex CTestSuiteViewModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid()){

        return createIndex(row, column, m_rootNode->getChildList().at(row));
    }
    else {
        const TreeNode* parentnode = reinterpret_cast<const TreeNode*>(parent.internalPointer());
        return createIndex(row, column, parentnode->getChildList().at(row));
    }
}

int CTestSuiteViewModel::rowCount (const QModelIndex &parent) const {
    if (!parent.isValid()) {
        return m_rootNode->getChildList().size();
    }
    else {
        return reinterpret_cast<TreeNode*>(parent.internalPointer())->getChildList().size();
    }
}

int CTestSuiteViewModel::columnCount (const QModelIndex &parent) const {
    /// Temporary...
    return 1;
}

QVariant CTestSuiteViewModel::data (const QModelIndex &index, int role) const {
    if (index.isValid() && role == Qt::DisplayRole){
        const TreeNode* node = reinterpret_cast<const TreeNode*>(index.internalPointer());

        switch((int)node->getType()){
        case TreeNode::TESTSUITE:
            return (QString)reinterpret_cast<ITestSuite*>(node->getItem())->getName();
        case TreeNode::TESTCASE:
            return (QString)reinterpret_cast<ITestCase*>(node->getItem())->getName();
        }

    }

    return QVariant();
}

QModelIndex CTestSuiteViewModel::parent (const QModelIndex &child) const {
    if (child.isValid()){
        TreeNode* node = reinterpret_cast<TreeNode*>(child.internalPointer());
        switch(node->getType()){
        case TreeNode::TESTSUITE:
            return QModelIndex();
        case TreeNode::TESTCASE:
            return index(m_rootNode->getChildList().indexOf(node->parent()), 0);
        case TreeNode::DATATAG:
            return index(node->parent()->getChildList().indexOf(node->parent()), 0, index(m_rootNode->getChildList().indexOf(node->parent()->parent()), 0));
        default:
            Q_ASSERT_X(false, "WTF?","ViacheslavL");
        }
    }
    return QModelIndex();
}

QModelIndex CTestSuiteViewModel::getRootIndex(){
    return createIndex(-1, -1,(void*) m_rootNode);
}
