#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
using namespace std;

// ================================================================
// ================ BAGIAN BST (KATALOG BUKU) =====================
// ================================================================

struct Buku {
    string isbn;
    string judul;
    string penulis;
    int tahunTerbit;
    string tag_topik[5];
};

struct Node {
    Buku data;
    Node* left;
    Node* right;
};

// --- Primitif BST (CRUD) --
void initBST(Node*& root);
bool insertBuku(Node*& root, Buku b);
Node* searchISBN(Node* root, string isbn);
bool updateBuku(Node* root, string isbn);
bool deleteBuku(Node*& root, string isbn);

// Traversal pada BST --
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
void levelOrder(Node* root);

// -- Fitur Tambahan dan Challenge --
void searchByTag(Node* root, string tag);
int countBuku(Node* root);
int minTahun(Node* root);
int maxTahun(Node* root);
float avgTahun(Node* root);

// ===================================================================
// ================ BAGIAN MLL (Peminjaman Buku) =====================
// ===================================================================




#endif

