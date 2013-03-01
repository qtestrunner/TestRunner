#include "treenode.h"

TreeNode::TreeNode()
	: m_type(ROOT)
	, m_parent(NULL)
	, m_item(NULL)
{
}

TreeNode* TreeNode::addChildNode(void *ptr) {
    NodeType type;
	TreeNode* newnode = 0;
    if ( ptr ){
        switch(m_type){
        case ROOT:
            type = TESTSUITE;
            break;
        case TESTSUITE:
            type = TESTCASE;
            break;
        case TESTCASE:
            type = DATATAG;
            break;
        case DATATAG:
            return NULL;
        }
        newnode = new TreeNode(ptr, type, this);
        m_childlist << newnode;
    }

	return newnode;
}

TreeNode::TreeNode(void* ptr, NodeType type, TreeNode* parent)
	: m_item(ptr)
	, m_parent(parent)
	, m_type(type)
{
}
