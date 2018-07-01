#ifndef _RBTREE_H_
#define _RBTREE_H_

#define RED   0
#define BLACK 1

class Node{
    public:
        Node* left;
        Node* right;
        Node* parent;
        int value;
        int color;

        Node();
        Node(int);
};

class RBTree{
    private:
        Node* root;
        Node* nil;
        int numberOfNodes;
        
    public:
        void leftRotation(Node*);
        void rightRotation(Node*);
        void RBTransplant(Node*, Node*);
        Node* sucessor(Node*);
        void print(Node*);
        bool insertFixUp(Node*&);
        void removeFixUp(Node*&);
        void deleteTree(Node*);

    public:
        RBTree();
        ~RBTree();

        void insert(int);
        bool remove(int);
        bool contains(int);

        void print();
        int size() const;
        bool isEmpty() const;
       
        Node *getRoot(){
            return root;
        }
};

#endif
