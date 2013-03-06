#include "ctestsuiteviewmodel.h"
#include <QDebug>
#include <QStringList>

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
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
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
	if (role == Qt::CheckStateRole)
	{
		TreeNode* node = reinterpret_cast<TreeNode*>(index.internalPointer());
		switch(node->getType())
		{
		case TreeNode::TESTSUITE:
			if (reinterpret_cast<ITestSuite*>(node->getItem())->isRunnable())
				return Qt::Checked; else return Qt::Unchecked;
		case TreeNode::TESTCASE:
			if (reinterpret_cast<ITestCase*>(node->getItem())->isRunnable())
				return Qt::Checked; else return Qt::Unchecked;
		case TreeNode::DATATAG:
			ITestCase * caseItem = reinterpret_cast<ITestCase*>(node->parent()->getItem());
			QString tag = *reinterpret_cast<const QString*>(node->getItem());
			if (caseItem->runnableDataTags().contains(tag))
				return Qt::Checked; else return Qt::Unchecked;
		}
	}
	else if (index != QModelIndex() && role == Qt::DisplayRole){
        const TreeNode* node = reinterpret_cast<const TreeNode*>(index.internalPointer());
		switch(node->getType())
		{
        case TreeNode::TESTSUITE:
			return reinterpret_cast<ITestSuite*>(node->getItem())->getName();
        case TreeNode::TESTCASE:
			return reinterpret_cast<ITestCase*>(node->getItem())->getName();
		case TreeNode::DATATAG:
			return *reinterpret_cast<const QString*>(node->getItem());
		default:
			Q_ASSERT(false);
			return QVariant();
        }
    }
	return QVariant();
}

bool CTestSuiteViewModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (index != QModelIndex() && role == Qt::CheckStateRole)
	{
		bool runnable;
		if (value == Qt::Checked)
			runnable = true; else runnable = false;
		TreeNode* node = reinterpret_cast<TreeNode*>(index.internalPointer());
		switch(node->getType())
		{
		case TreeNode::TESTSUITE:
			reinterpret_cast<ITestSuite*>(node->getItem())->setRunnable(runnable);
			break;
		case TreeNode::TESTCASE:
			reinterpret_cast<ITestCase*>(node->getItem())->setRunnable(runnable);
			break;
		case TreeNode::DATATAG:
			ITestCase * caseItem = reinterpret_cast<ITestCase*>(node->parent()->getItem());
			QString tag = *reinterpret_cast<const QString*>(node->getItem());
			QStringList tags(caseItem->runnableDataTags());
			if (runnable)
				tags << tag;
			else
				tags.removeOne(tag);
			caseItem->setRunnableDataTags(tags);

			QModelIndex pindex = parent(index);
			emit dataChanged(pindex, pindex);

			break;
		}
		emit dataChanged(index, index);
		return true;
	}
	return false;
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

