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

    d = 3.14;
    for (int i = 1; i < n; i++) {
        tree.remove(d);
        d = d + 1;
    }

    tree.print();
}