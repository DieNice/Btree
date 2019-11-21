#include "src/Btree.h"
#include <iostream>
//#include <vector>

using namespace std;

int main() {
    BTree tree(2);

    int n = 30;

    for (int i = 1; i < n; i++) {
        tree.insert(i);
    }

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