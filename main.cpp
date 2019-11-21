#include <iostream>
//#include <vector>

using namespace std;

void printTab(int d) {
    for (size_t i = 0; i < d; i++) {
        cout << '\t';
    }
}

struct Page {
    int t, n;
    bool leaf;
    Page **links;
    int *keys;

    //public:
    Page(int _t = 2) {
        t = _t;
        n = 0;
        leaf = true;
        links = new Page *[2 * t];
        for (size_t i = 0; i < 2 * t; i++) {
            links[i] = nullptr;
        }
        keys = new int[2 * t - 1];
    }

    ~Page() {
        for (size_t i = 0; i < 2 * t; i++) {
            if (links[i] != nullptr)
                delete links[i];
        }
        delete[] links;
        delete[] keys;
    }

    void splitChild(int i) {
        Page *z = new Page(t);
        Page *y = links[i];
        z->leaf = y->leaf;
        for (int j = 0; j < t - 1; j++) {
            z->keys[j] = y->keys[j + t];
        }
        if (!y->leaf)
            for (int j = 0; j < t; j++) {
                z->links[j] = y->links[j + t];
                y->links[j + t] = nullptr;
            }
        y->n = t - 1;
        z->n = t - 1;
        for (int j = n; j > i; j--) {
            links[j + 1] = links[j];
        }
        links[i + 1] = z;
        for (int j = n - 1; j >= i; j--) {
            keys[j + 1] = keys[j];
        }
        keys[i] = y->keys[t - 1];
        n++;
    }

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

    void mergeChild(int i) {
        Page *y = links[i];
        Page *z = links[i + 1];
        int yn = y->n;
        int zn = z->n;
        y->keys[yn] = keys[i];
        for (int j = 0; j < zn; j++) {
            y->keys[yn + j + 1] = z->keys[j];
        }
        if (!y->leaf)
            for (int j = 0; j <= zn; j++) {
                y->links[yn + 1 + j] = z->links[j];
                z->links[j] = nullptr;
            }
        y->n = yn + zn + 1;
        delete z;
        for (int j = i + 1; j < n; j++) {
            links[j] = links[j + 1];
        }
        links[n] = nullptr;
        for (int j = i; j < n - 1; j++) {
            keys[j] = keys[j + 1];
        }
        keys[n - 1] = 0;
        n--;
    }

    void stealLeft(int i) {
        Page *x = links[i];
        Page *y = links[i - 1];
        int k = keys[i - 1];
        int xn = x->n;
        int yn = y->n;

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

        x->n += 1;
        y->n -= 1;
    }

    void stealRight(int i) {
        Page *x = links[i];
        Page *y = links[i + 1];
        int k = keys[i];
        int xn = x->n;
        int yn = y->n;

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

        x->n += 1;
        y->n -= 1;
    }

    int getMin(int i) {
        Page *x = links[i];
        while (!x->leaf)
            x = x->links[0];
        return x->keys[0];
    }

    int getMax(int i) {
        Page *x = links[i];
        while (!x->leaf)
            x = x->links[x->n];
        return x->keys[x->n - 1];
    }

    bool remove(int key) {
        int i = 0;
        for (i = 0; i < n; i++) {
            if (key <= keys[i]) {
                i++;
                break;
            }
            if (i == n - 1)
                i = n;
        }
        i--;
        if (i != n && key == keys[i]) {
            if (leaf) {
                for (int j = i; j < n - 1; j++) {
                    keys[j] = keys[j + 1];
                }
                n--;
                keys[n] = 0;
                return true;
            } else {
                if (links[i]->n >= t) {
                    int nkey = getMax(i);
                    keys[i] = nkey;
                    //n--;
                    return links[i]->remove(nkey);
                } else if (links[i + 1]->n >= t) {
                    int nkey = getMin(i + 1);
                    keys[i] = nkey;
                    //n--;
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
                if (links[i]->n == t - 1) {
                    if (i > 0 && links[i - 1]->n >= t) {
                        stealLeft(i);
                    } else if (i < n && links[i + 1]->n >= t) {
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
    }

    void print(int d) {
        for (int i = n; i >= 0; i--) {
            if (i < n) {
                if (i == n - 1) {
                    printTab(d);
                    cout << "---" << endl;
                }
                printTab(d);
                cout << keys[i] << endl;
                if (i == 0) {
                    printTab(d);
                    cout << "---" << endl;
                }
            }
            if (!leaf)
                links[i]->print(d + 1);
        }
    }

    bool search(int key) {
        int i = 0;
        for (i = 0; i < n; i++) {
            if (key <= keys[i]) {
                i++;
                break;
            }
            if (i == n - 1)
                i = n;
        }
        i--;

        if (i != n && key == keys[i])
            return true;
        else if (leaf)
            return false;
        else
            return links[i]->search(key);
    }
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

bool BTree::search(int key) {
    if (root != nullptr)
        return root->search(key);
    return false;
}

void BTree::insert(int key) {
    if (root == nullptr)
        root = new Page(t);
    Page *r = root;
    if (root->n == 2 * t - 1) {
        Page *s = new Page(t);
        root = s;
        s->leaf = false;
        s->n = 0;
        s->links[0] = r;
        s->splitChild(0);
        s->insertNonFull(key);
    } else
        r->insertNonFull(key);
}

void BTree::print() {
    if (root != nullptr)
        root->print(0);
    else
        cout << "Tree is empty";
    cout << endl;
    cout << endl;
    cout << endl;
}

bool BTree::remove(int key) {
    if (root == nullptr) return false;
    bool flag = root->remove(key);

    if (root->n == 0) {
        Page *temp = root;
        root = temp->links[0];
        temp->links[0] = nullptr;
        delete temp;
    }

    return flag;
}

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