#include "src/Btree.h"
#include <iostream>
//#include <vector>

using namespace std;

int main() {
    BTree<float> tree(2);

    int n = 9;
    float d = 3.14;
    for (int i = 1; i < n; i++) {
        tree.insert(d);
        cout << tree.search(d);
        d = d + 1;

    }
    cout << tree.search(d + 1);
    tree.print();
/*    cout << "---------------------- DEL ------------------------------------------------------" << endl;

    for (int i = n / 2; i < n + 2; i++) {
        *//*
        int k = 26;
        if (i == k)
            tree.print();
        cout << i << " " << numchilds / 2 - i << " " << numchilds - i << endl;
        *//*
        tree.remove(i);
        tree.remove(n - i);
        tree.remove(n / 2 - i);

    }
    tree.print();
    cout << "---------------------- ADD ------------------------------------------------------" << endl;
    for (int i = 1; i < n; i++) {
        tree.insert(i);
        //tree.insert(2*i);
        //tree.insert(30-i);

    }

    tree.print();*/
}