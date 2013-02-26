#ifndef TREENODE_H
#define TREENODE_H

#include <QList>

class TreeNode
{

public:
    typedef enum { ROOT, TESTSUITE, TESTCASE, DATATAG } NodeType;

    /// Default Constructor - creates new Tree Node with a single root element
    TreeNode();

    /*!
     * \brief addChildNode - adds child Node to current Node
     * \param ptr - pointer to linkled element
     * \return element if new element was created, otherwise - NULL
     */
    TreeNode* addChildNode( void* ptr);

    /*!
     * \brief getType - gets type of current node
     * \return type of data, that is linked to current Node
     */
    NodeType getType() const { return m_type; }

    /*!
     * \brief getItem
     * \return pointer to linked item
     */
    void* getItem() const { return m_item; }

    /*!
     * \brief parent
     * \return parent item, if no parent - returns NULL
     */
    TreeNode* parent () { return m_parent; }

    QList<TreeNode*> getChildList() const  { return m_childlist; }

protected:
    /*!
     * \brief TreeNode - Constructor creates a new element of specified type
     * \param ptr - pointer to linked element
     * \param type - type of new node
     */
    TreeNode( void* ptr, NodeType type, TreeNode* parent);

private:
    /// Pointer to the linked element
    void* m_item;

    /// Pointer to the parent element
    TreeNode* m_parent;

    /// List of child elements
    QList<TreeNode*> m_childlist;

    /// Type of current element
    NodeType m_type;
};

#endif // TREENODE_H
