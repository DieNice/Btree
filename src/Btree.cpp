//
// Created by pda on 11/21/19.
//

#include "Btree.h"

#include <iostream>

using namespace std;

//********************************Node(Page)************************************
template<typename T>
Node<T>::Node(int pow) {
    t = pow;
    numchilds = 0;
    leaf = true;
    links = new Node<T> *[2 * t];
    for (size_t i = 0; i < 2 * t; i++) {
        links[i] = nullptr;
    }
    keys = new T[2 * t - 1];
}

template<typename T>
Node<T>::~Node() {
    for (size_t i = 0; i < 2 * t; i++) {
        if (links[i] != nullptr)
            delete links[i];
    }
    delete[] links;
    delete[] keys;
}

template<typename T>
void Node<T>::splitChild(int i) {
    Node<T> *z = new Node<T>(t);
    Node<T> *y = links[i];
    z->leaf = y->leaf;
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }
    if (!y->leaf)
        for (int j = 0; j < t; j++) {
            z->links[j] = y->links[j + t];
            y->links[j + t] = nullptr;
        }
    y->numchilds = t - 1;
    z->numchilds = t - 1;
    for (int j = numchilds; j > i; j--) {
        links[j + 1] = links[j];
    }
    links[i + 1] = z;
    for (int j = numchilds - 1; j >= i; j--) {
        keys[j + 1] = keys[j];
    }
    keys[i] = y->keys[t - 1];
    numchilds++;
}

template<typename T>
void Node<T>::insertNonFull(T k) {
    int i = numchilds - 1;
    if (leaf) {
        while (i >= 0 && k < keys[i]) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        numchilds++;
    } else {
        while (i >= 0 && k < keys[i]) {
            i--;
        }
        i++;
        if (links[i]->numchilds == 2 * t - 1) {
            splitChild(i);
            if (k > keys[i])
                i++;
        }
        links[i]->insertNonFull(k);
    }

}

template void Node<int>::insertNonFull(int k);

template void Node<char>::insertNonFull(char k);

template void Node<float>::insertNonFull(float k);

/*void Node::stealLeft(int i) {
    Node *x = links[i];
    Node *y = links[i - 1];
    int k = keys[i - 1];
    int xn = x->numchilds;
    int yn = y->numchilds;

    for (int j = xn; j > 0; j--) {
        x->keys[j] = x->keys[j - 1];
    }
    x->keys[0] = k;
    keys[i - 1] = y->keys[yn - 1];
    y->keys[yn - 1] = 0;

    for (int j = xn; j >= 0; j--) {
        x->links[j + 1] = x->links[j];
    }
    x->links[0] = y->links[yn];
    y->links[yn] = nullptr;

    x->numchilds += 1;
    y->numchilds -= 1;
}

void Node::stealRight(int i) {
    Node *x = links[i];
    Node *y = links[i + 1];
    int k = keys[i];
    int xn = x->numchilds;
    int yn = y->numchilds;

    x->keys[xn] = k;
    keys[i] = y->keys[0];
    for (int j = 0; j < yn - 1; j++) {
        y->keys[j] = y->keys[j + 1];
    }
    y->keys[yn - 1] = 0;

    x->links[xn + 1] = y->links[0];
    for (int j = 0; j < yn; j++) {
        y->links[j] = y->links[j + 1];
    }
    y->links[yn] = nullptr;

    x->numchilds += 1;
    y->numchilds -= 1;
}

void Node::mergeChild(int i) {
    Node *y = links[i];
    Node *z = links[i + 1];
    int yn = y->numchilds;
    int zn = z->numchilds;
    y->keys[yn] = keys[i];
    for (int j = 0; j < zn; j++) {
        y->keys[yn + j + 1] = z->keys[j];
    }
    if (!y->leaf)
        for (int j = 0; j <= zn; j++) {
            y->links[yn + 1 + j] = z->links[j];
            z->links[j] = nullptr;
        }
    y->numchilds = yn + zn + 1;
    delete z;
    for (int j = i + 1; j < numchilds; j++) {
        links[j] = links[j + 1];
    }
    links[numchilds] = nullptr;
    for (int j = i; j < numchilds - 1; j++) {
        keys[j] = keys[j + 1];
    }
    keys[numchilds - 1] = 0;
    numchilds--;
}

int Node::getMin(int i) {
    Node *x = links[i];
    while (!x->leaf)
        x = x->links[0];
    return x->keys[0];
}


int Node::getMax(int i) {
    Node *x = links[i];
    while (!x->leaf)
        x = x->links[x->numchilds];
    return x->keys[x->numchilds - 1];
}

bool Node::remove(int key) {
    int i = 0;
    for (i = 0; i < numchilds; i++) {
        if (key <= keys[i]) {
            i++;
            break;
        }
        if (i == numchilds - 1)
            i = numchilds;
    }
    i--;
    if (i != numchilds && key == keys[i]) {
        if (leaf) {
            for (int j = i; j < numchilds - 1; j++) {
                keys[j] = keys[j + 1];
            }
            numchilds--;
            keys[numchilds] = 0;
            return true;
        } else {
            if (links[i]->numchilds >= t) {
                int nkey = getMax(i);
                keys[i] = nkey;
                //numchilds--;
                return links[i]->remove(nkey);
            } else if (links[i + 1]->numchilds >= t) {
                int nkey = getMin(i + 1);
                keys[i] = nkey;
                //numchilds--;
                return links[i + 1]->remove(nkey);
            } else {
                mergeChild(i);
                return links[i]->remove(key);
            }
        }

    } else {
        if (leaf) {
            return false;
        } else {
            if (links[i]->numchilds == t - 1) {
                if (i > 0 && links[i - 1]->numchilds >= t) {
                    stealLeft(i);
                } else if (i < numchilds && links[i + 1]->numchilds >= t) {
                    stealRight(i);
                } else {
                    if (i > 0) {
                        mergeChild(i - 1);
                        i--;
                    } else {
                        mergeChild(i);
                    }
                }
            }
            return links[i]->remove(key);
        }
    }
    return false;
}*/

template<typename T>
void Node<T>::print(int d) {
    cout << "\nlvl=" << d << "=|";
    for (int i = 0; i < numchilds; i++) {
        cout << keys[i] << "|";
    }

    if (!leaf) {
        for (int i = 0; i <= numchilds; i++) {
            links[i]->print(d + 1);
        }
    }
}

template<typename T>
bool Node<T>::search(T key) {
    int i = 0;
    for (i = 0; i < numchilds; i++) {
        if (key <= keys[i]) {
            i++;
            break;
        }
        if (i == numchilds - 1)
            i = numchilds;
    }
    i--;

    if (i != numchilds && key == keys[i])
        return true;
    else if (leaf)
        return false;
    else
        return links[i]->search(key);
}

template bool Node<int>::search(int key);

template bool Node<char>::search(char key);

template bool Node<float>::search(float key);


//**************************************BTREE**********************

template<typename T>
BTree<T>::BTree(int p) {
    power = p;
    root = nullptr;
}

template BTree<float>::BTree(int p);

template BTree<char>::BTree(int p);

template BTree<int>::BTree(int p);


template<typename T>
BTree<T>::~BTree() { delete root; }

template BTree<float>::~BTree();

template BTree<char>::~BTree();

template BTree<int>::~BTree();


template<typename T>
bool BTree<T>::search(T key) {
    if (root != nullptr)
        return root->search(key);
    return false;
}

template bool BTree<int>::search(int key);

template bool BTree<float>::search(float key);

template bool BTree<char>::search(char key);

template<typename T>
void BTree<T>::insert(T key) {
    if (root == nullptr) { root = new Node<T>(power); }
    Node<T> *r = root;
    if (root->numchilds == 2 * power - 1) {
        Node<T> *s = new Node<T>(power);
        root = s;
        s->leaf = false;
        s->numchilds = 0;
        s->links[0] = r;
        s->splitChild(0);
        s->insertNonFull(key);
    } else { r->insertNonFull(key); }
}

template void BTree<float>::insert(float key);

template void BTree<char>::insert(char key);

template void BTree<int>::insert(int key);


template<typename T>
void BTree<T>::print() {
    if (root != nullptr)
        root->print(0);
    else
        cout << "BTree is empty" << endl;

}

template void BTree<float>::print();

template void BTree<char>::print();

template void BTree<int>::print();

/*

bool BTree::remove(int key) {
    if (root == nullptr) return false;
    bool flag = root->remove(key);

    if (root->numchilds == 0) {
        Node *temp = root;
        root = temp->links[0];
        temp->links[0] = nullptr;
        delete temp;
    }

    return flag;
}*/
