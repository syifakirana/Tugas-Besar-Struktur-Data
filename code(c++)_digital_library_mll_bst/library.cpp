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

// Dasar MLL
void createListMLL(ListMLL &L) {
         L.first = NULL;
}

bool isEmptyMLL(ListMLL L) {
        return L.first == NULL;
}

adrMember alokasiMember(Member data) {

}

adrPinjam alokasiPinjam(string judul, string tgl) {

}

void dealokasiMember(adrMember &P) {

}

void dealokasiPinjam(adrPinjam &P) {

}

// Operasi CRUD Parent (Member)
// -- insert
void insertFirstMember(ListMLL &L, adrMember P) {

}

void insertLastMember(ListMLL &L, adrMember P) {

}

void insertAfterMember(ListMLL &L, adrMember prec, adrMember P) {

}

// -- delete
void deleteFirstMember(ListMLL &L, adrMember &P) {
        if (!isEmptyMLL(L)) {
        P = L.first;
        L.first = P->next;
        dealokasiMember(P);
    }
}

void deleteLastMember(ListMLL &L, adrMember &P) {
    
}

void deleteMemberByID(ListMLL &L, string idMember) {
    adrMember P = L.first;
    adrMember prec = NULL;

    while (P != NULL && P->info.idMember != idMember) {
        prec = P;
        P = P->next;
    }

    if (P != NULL) {
        if (prec == NULL)
            L.first = P->next;
        else
            prec->next = P->next;

        // hapus semua pinjaman
        adrPinjam C = P->firstPinjam;
        while (C != NULL) {
            adrPinjam temp = C;
            C = C->next;
            dealokasiPinjam(temp);
        }
        dealokasiMember(P);
    }
}
// -- search
adrMember searchMember(ListMLL L, string idMember) {

}

// Operasi Crud Child (Peminjaman)
void insertPinjaman(ListMLL &L, string idMember, adrPinjam C) {

}
void deletePinjaman(ListMLL &L, string idMember, string judulBuku) {

}

// CHALLENGE
bool isBookBorrowed(adrMember P, string judulBuku) {

}

void showAllData(ListMLL L) {

}

void showMostActiveMember(ListMLL L) {

}

void showLeastActiveMember(ListMLL L) {

}

void showMembersWithXLoans(ListMLL L, int x) {
}

// Cari Buku by Judul (Untuk Validasi MLL)
Node* searchJudul(Node* root, string judul) {
}
