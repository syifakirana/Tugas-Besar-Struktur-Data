#include "library.h"

// ===========================================================
// ================ IMPLEMENTASI FUNGSI BST ==================
// ===========================================================

void initBST(Node*& root) {
    root = NULL;
}

Node* newNode(Buku b) {
    Node* p = new Node;
    p->data = b;
    p->left = p->right = NULL;
    return p;
}

bool insertBuku(Node*& root, Buku b) {
    if (root == NULL) {
        root = newNode(b);
        return true;
    }
    if (b.isbn == root->data.isbn) return false;
    if (b.isbn < root->data.isbn)
        return insertBuku(root->left, b);
    else
        return insertBuku(root->right, b);
}

Node* searchISBN(Node* root, string isbn) {
    if (root == NULL || root->data.isbn == isbn)
        return root;
    if (isbn < root->data.isbn)
        return searchISBN(root->left, isbn);
    return searchISBN(root->right, isbn);
}

bool updateBuku(Node* root, string isbn) {
    Node* p = searchISBN(root, isbn);
    if (!p) return false;

    cout << "Judul baru   : ";
    getline(cin, p->data.judul);
    cout << "Penulis baru : ";
    getline(cin, p->data.penulis);
    cout << "Tahun terbit : ";
    cin >> p->data.tahunTerbit;
    cin.ignore();

    cout << "Masukkan 5 tag topik:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Tag ke-" << i + 1 << ": ";
        getline(cin, p->data.tag_topik[i]);
    }
    return true;
}

Node* minNode(Node* root) {
    while (root->left) root = root->left;
    return root;
}

bool deleteBuku(Node*& root, string isbn) {
    if (!root) return false;

    if (isbn < root->data.isbn)
        return deleteBuku(root->left, isbn);
    else if (isbn > root->data.isbn)
        return deleteBuku(root->right, isbn);
    else {
        if (!root->left && !root->right) {
            delete root;
            root = NULL;
        } else if (!root->left) {
            Node* t = root;
            root = root->right;
            delete t;
        } else if (!root->right) {
            Node* t = root;
            root = root->left;
            delete t;
        } else {
            Node* t = minNode(root->right);
            root->data = t->data;
            deleteBuku(root->right, t->data.isbn);
        }
        return true;
    }
}

void print(Node* p) {
    cout << p->data.isbn << " | " << p->data.judul << endl;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        print(root);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        print(root);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        print(root);
    }
}

void levelOrder(Node* root) {
    if (!root) return;
    Node* q[100];
    int f = 0, r = 0;
    q[r++] = root;

    while (f < r) {
        Node* p = q[f++];
        print(p);
        if (p->left) q[r++] = p->left;
        if (p->right) q[r++] = p->right;
    }
}

void searchByTag(Node* root, string tag) {
    if (!root) return;
    searchByTag(root->left, tag);

    for (int i = 0; i < 5; i++) {
        if (root->data.tag_topik[i] == tag) {
            print(root);
            break;
        }
    }
    searchByTag(root->right, tag);
}

int countBuku(Node* root) {
    if (!root) return 0;
    return 1 + countBuku(root->left) + countBuku(root->right);
}

int minTahun(Node* root) {
    if (!root) return 9999;
    int m = root->data.tahunTerbit;
    int l = minTahun(root->left);
    int r = minTahun(root->right);
    if (l < m) m = l;
    if (r < m) m = r;
    return m;
}

int maxTahun(Node* root) {
    if (!root) return 0;
    int m = root->data.tahunTerbit;
    int l = maxTahun(root->left);
    int r = maxTahun(root->right);
    if (l > m) m = l;
    if (r > m) m = r;
    return m;
}

void sumDanCount(Node* root, int &sum, int &cnt) {
    if (root != NULL) {
        sum += root->data.tahunTerbit;
        cnt++;
        sumDanCount(root->left, sum, cnt);
        sumDanCount(root->right, sum, cnt);
    }
}

float avgTahun(Node* root) {
    if (root == NULL) return 0;

    int sum = 0, cnt = 0;
    sumDanCount(root, sum, cnt);

    return (float) sum / cnt;
}

// ===================================================================
// ================= IMPLEMENTASI FUNGSI MLL =========================
// ===================================================================
