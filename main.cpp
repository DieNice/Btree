#include "src/Btree.h"
#include <iostream>
//#include <vector>

using namespace std;

int main() {
    BTree tree(2);

    int n = 30;

    for (int i = 1; i < n; i++) {
        tree.insert(i);
        //tree.insert(2*i);
        //tree.insert(30-i);

    }

    tree.print();
    cout << "---------------------- DEL ------------------------------------------------------" << endl;

    for (int i = n / 2; i < n + 2; i++) {
        /*
        int k = 26;
        if (i == k)
            tree.print();
        cout << i << " " << n / 2 - i << " " << n - i << endl;
        */
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

    tree.print();
}


/*
int a = 5, b = 3, c = 1;
int *arr2 = new int[3];
arr2[0] = a;
arr2[1] = b;
arr2[2] = c;
for (size_t i = 0; i < 3; i++)
{
	cout << arr2[i] << " ";
}
cout << endl;
int** arr = new int*[3];
arr[0] = &a;
arr[1] = &b;
arr[2] = &c;
for (size_t i = 0; i < 3; i++)
{
	cout << *arr[i] << " ";
}
cout << endl;
delete[] arr2;
delete[] arr;
cout << "sas\n";
*/