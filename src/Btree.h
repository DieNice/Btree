//
// Created by pda on 11/21/19.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

void printTab(int d);

struct Node {
    int t, n;
    bool leaf;
    Node **links;
    int *keys;

    Node(int _t = 2);

    ~Node();

    void splitChild(int i);

    void insertNonFull(int k);

    void mergeChild(int i);

    void stealLeft(int i);

    void stealRight(int i);

    int getMin(int i);

    int getMax(int i);

    bool remove(int key);

    void print(int d);

    bool search(int key);
};


class BTree {
    int t;
    Node *root;
public:
    BTree(int _t = 2);

    ~BTree();

    bool search(int key);

    void insert(int key);

    bool remove(int key);

    void print();
};


#endif //BTREE_BTREE_H
