#include "src/Btree.h"

using namespace std;

int main() {
    BTree<int> tree(2);

    int n = 11;
    float d = 3.14;
    char h = 'a';
    for (int i = 1; i < n; i++) {
        tree.add(n-i);
        d = i % 5;
        h++;

    }
    tree.print();

    tree.del(10);

    cout << "\n--------" << endl;
    tree.print();
}