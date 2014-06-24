//
//  tree.h
//  lab4

#ifndef tree_h
#define tree_h

class Tree {

public:
    
    Tree();
    Tree(const Tree &);
    Tree();
    
    bool isEmpty() const;
    void makeEmpty();
    
    Tree& operator=(const Tree &);
    bool operator==(const Tree &) const;
    bool operator!=(const Tree &) const;
    
    bool insert(NodeData*);
    bool retrieve(const NodeData&, NodeData*&) const;
    
    void printInorder(ostream&) const;
    
private:
    
    Node* root;
    int nodeCount;

    void makeEmptyHelper(MovieNode *&current);
    void copyTree(const MovieNode*, MovieNode*&);
    bool retrieveHelper(MovieNode*, const NodeData&, NodeData*&)const;
    void inorderHelper(MovieNode*, ostream&)const;
    bool equalHelper(MovieNode *, MovieNode *)const;
    
};


#endif
