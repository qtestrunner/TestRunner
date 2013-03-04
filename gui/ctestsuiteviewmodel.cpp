#include "ctestsuiteviewmodel.h"
#include <QDebug>

CTestSuiteViewModel::CTestSuiteViewModel(const QList<IFilePtr>& filelist, QObject *parent):
    QAbstractItemModel(parent)
{
	m_files = filelist;
    m_rootNode = new TreeNode;
	foreach(const IFilePtr & file, m_files){

		foreach(const ITestSuitePtr & testsuite, file->getTestSuites()){
			TreeNode* suiteNode = m_rootNode->addChildNode(testsuite.data());

			foreach(const ITestCasePtr & testcase, testsuite->getCases()){
				TreeNode* caseNode = suiteNode->addChildNode(testcase.data());

                if (testcase->hasDataTags()){
					foreach(const QString & datatag, testcase->getAllDataTags()){
						caseNode->addChildNode((void*)&datatag);
                    }
                }
            }
        }
    }
}

Qt::ItemFlags CTestSuiteViewModel::flags(const QModelIndex &index) const
{
	if (index == QModelIndex())
        return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex CTestSuiteViewModel::index(int row, int /*column*/, const QModelIndex &parent) const
{
	if (parent == QModelIndex())
		if (!m_rootNode->getChildList().isEmpty())
			return createIndex(row, 0,(void*) m_rootNode->getChildList().at(row));
		else
			return QModelIndex();
	else
	{
		const TreeNode* parentnode = reinterpret_cast<const TreeNode*>(parent.internalPointer());
		if (!parentnode->getChildList().isEmpty())
			return createIndex(row, 0, parentnode->getChildList().at(row));
		else
			return QModelIndex();
	}
	return QModelIndex();
}

int CTestSuiteViewModel::rowCount (const QModelIndex &parent) const
{
	if (parent == QModelIndex())
		return  m_rootNode->getChildList().count();

	return reinterpret_cast<TreeNode*>(parent.internalPointer())->getChildList().count();
}

int CTestSuiteViewModel::columnCount (const QModelIndex &parent) const {
    /// Temporary...
    return 1;
}

QVariant CTestSuiteViewModel::data (const QModelIndex &index, int role) const
{
	if (index != QModelIndex() && role == Qt::DisplayRole){
        const TreeNode* node = reinterpret_cast<const TreeNode*>(index.internalPointer());
		switch(node->getType())
		{
        case TreeNode::TESTSUITE:
			return reinterpret_cast<ITestSuite*>(node->getItem())->getName();
        case TreeNode::TESTCASE:
			return reinterpret_cast<ITestCase*>(node->getItem())->getName();
		case TreeNode::DATATAG:
			return *reinterpret_cast<const QString*>(node->getItem());
        }
    }
    return QVariant();
}

QModelIndex CTestSuiteViewModel::parent (const QModelIndex &child) const
{
	if (child != QModelIndex())
	{
        TreeNode* node = reinterpret_cast<TreeNode*>(child.internalPointer());
		if (m_rootNode == node->parent())
			return QModelIndex();
		else
			return createIndex(node->parent()->parent()->getChildList().indexOf(node->parent()),0, node->parent());
    }
    return QModelIndex();
}

