//
// Created by pda on 11/21/19.
//

#ifndef BTREE_BTREE_H
#define BTREE_BTREE_H

void printTab(int d);

struct Page {
    int t, n;
    bool leaf;
    Page **links;
    int *keys;

    //public:
    Page(int _t = 2);

    ~Page();

    void splitChild(int i);

    void insertNonFull(int k) {
        int i = n - 1;
        if (leaf) {
            while (i >= 0 && k < keys[i]) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
            n++;
        } else {
            while (i >= 0 && k < keys[i]) {
                i--;
            }
            i++;
            if (links[i]->n == 2 * t - 1) {
                splitChild(i);
                if (k > keys[i])
                    i++;
            }
            links[i]->insertNonFull(k);
        }

    }

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
    Page *root;
public:
    BTree(int _t = 2) {
        t = _t;
        //root = new Page(t);
        root = nullptr;
    }

    ~BTree() { delete root; }

    bool search(int key);

    void insert(int key);

    bool remove(int key);

    void print();
};


#endif //BTREE_BTREE_H
