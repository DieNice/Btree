//
// Created by pda on 11/21/19.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

template<typename T>
struct Node {
    int t, numchilds;
    bool leaf;
    Node<T> **links;
    T *keys;

    Node(int pow = 2);

    ~Node();

    void splitChild(int i);

    void insertNonFull(T k);

    void mergeChild(int i);

    void stealLeft(int i);

    void stealRight(int i);

    int getMin(int i);

    int getMax(int i);

    bool remove(int key);

    void print(int d);

    bool search(T key);
};

template<typename typedata>
class BTree {
private:
    int power;
    Node<typedata> *root;
public:
    BTree(int p = 2);

    ~BTree();

    bool search(typedata key);

    void insert(typedata key);

    bool remove(int key);

    void print();
};


#endif //BTREE_BTREE_H
